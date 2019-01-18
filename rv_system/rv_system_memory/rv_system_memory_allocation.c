
/* ============================ rv_system_memory_allocation.c ===================================== //

    rv_system_memory_allocation.c

    allocates memory in a thread safe manner
    memory is locked yields
        memory_lock which allocates memory, internally uses
            memory_frames's which are allocated from system calls, contains
                memory_allocations which are created when lib user requests memory
                memory_allocation structs are inline between actual memory being allocated
                memory_frame structs are inline before allocations in the page
                memory and memory_lock are created in static memory provided by the lib user (on the stack usually)

// ============================ rv_system_memory_allocation.c ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_memory_SLASH_rv_system_memory_allocation_DOT_c
    #define rv_system_SLASH_rv_system_memory_SLASH_rv_system_memory_allocation_DOT_c

/* ------------------- included headers --------------------------------------- */

    //headers
        #include "rv_system_memory.h"
        #include "rv_system_memory_lock.h"
        #include "rv_system_memory_frame.h"
        #include "rv_system_memory_allocation.h"
        #if !defined( rv_system_memory_allocation_print_enabled ) && defined ( rv_system_memory_allocation_print_errors )
            #undef rv_system_memory_allocation_print_errors
        #endif
        #if !defined( rv_system_memory_allocation_print_enabled ) && defined ( rv_system_memory_allocation_print_all )
            #undef rv_system_memory_allocation_print_all
        #endif
        #if !defined( rv_system_memory_allocation_print_errors ) && defined ( rv_system_memory_allocation_print_all )
            #define rv_system_memory_allocation_print_errors
        #endif
        #ifdef rv_system_memory_allocation_print_enabled
            #include <stdio.h>
            #include <stdlib.h>
        #endif
    //object
        #include "../rv_system_object/rv_system_object_base.h"

/* -------- structures containing easy function pointers --------------------- */

    //contains struct methods
        struct rv_system_memory_allocation_ptr_s rv_system_memory_allocation =
        {
            /*.create_static=*/ rv_system_memory_allocation_create_static,
            /*.destroy_static=*/ rv_system_memory_allocation_destroy_static,
            /*.get_components=*/ rv_system_memory_allocation_get_components,
            /*.validate=*/ rv_system_memory_allocation_validate,
            /*.split=*/ rv_system_memory_allocation_split,
            /*.allocate=*/ rv_system_memory_allocation_allocate,
            /*.release=*/ rv_system_memory_allocation_release,
            /*.compute_size=*/ rv_system_memory_allocation_compute_size,
            /*.print=*/ rv_system_memory_allocation_print,
            /*.get_stats=*/ rv_system_memory_allocation_get_stats
        };

/* ------------------- static function stubs --------------------------------- */

    //rv_system_memory_create_allocation_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_memory_allocation_create_static
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        )
        {
            struct rv_system_memory_allocation_s *f;
        //test size
            if( sz < sizeof( struct rv_system_memory_allocation_s ) * 2 )
                return 0;
        //init
            t->is_used = 0;
            t->is_followed = 0;
            t->offset_object_base = 0;
            t->size = sz - sizeof( struct rv_system_memory_allocation_s ) * 2;
        //footer
            rv_system_memory_allocation_get_components( t, &f, 0, 0 );
            f->is_used = 0;
            f->size = t->size;
            f->is_followed = 0;
            f->offset_object_base = t->offset_object_base;
        //return status
            return rv_system_memory_allocation_validate( t );
        }

    //rv_system_memory_allocation_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_memory_allocation_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s     *t
        )
        {
            struct rv_system_memory_allocation_s *n;
        //validate condition
            if( !rv_system_memory_allocation_validate( t ) )
                return;
        //destroy next allocation
            rv_system_memory_allocation_get_components( t, 0, 0, &n );
            if( n )
                rv_system_memory_allocation_destroy_static( n );
        }

    //rv_system_memory_allocation_get_components() computes offset to header, footer, and data
        void rv_system_memory_allocation_get_components
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s     *t,
        //pointer to footer
            struct rv_system_memory_allocation_s     **f,
        //pointer to data
            void                                    **pd,
        //pointer to next
            struct rv_system_memory_allocation_s     **n
        )
        {
            union
            {
                struct rv_system_memory_allocation_s    *t;
                void                                    *v;
                uint8_t                                 *b;
            } a;
        //initial
            a.t = t;
        //data
            a.b += sizeof( struct rv_system_memory_allocation_s );
            if( pd )
                *pd = a.v;
        //footer
            a.b += t->size;
            if( f )
                *f = a.t;
        //next
            if( !t->is_followed )
                a.b = 0;
            else
                a.b += sizeof( struct rv_system_memory_allocation_s );
            if( n )
                *n = a.t;
        };

    //rv_system_memory_allocation_validate() verifies allocation header and footer to catch overruns
        bool rv_system_memory_allocation_validate
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s     *t
        )
        {
            struct rv_system_memory_allocation_s *f;
            bool b;
        //fetch footer
            rv_system_memory_allocation_get_components( t, &f, 0, 0 );
            if( !f )
                return 0;
        //test footer and header
            b = t->is_used == f->is_used;
            b &= t->size == f->size;
            b &= t->is_followed == f->is_followed;
            b &= t->offset_object_base == f->offset_object_base;
        //return result
            #ifdef rv_system_memory_allocation_print_errors
                if( !b )
                {
                    union
                    {
                        unsigned int    ui;
                        void            *p;
                        uint32_t        ui32;
                        uint64_t        ui64;
                    } u_ptr, u_sz;
                    u_ptr.p = (void *)t;
                    u_sz.ui32 = t->size;
                    fprintf( stderr, "Allocation at %u validation failed with %u bytes.\n", u_ptr.ui, u_sz.ui );
                }
            #endif
            return b;
        };

    //rv_system_memory_allocation_split() breaks apart a free allocation into two allocations with one being a specified size internally
    //  returns true if could be split. new allocation is always created at the end of the old allocation
        bool rv_system_memory_allocation_split
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s    *t,
        //size of the new allocation internally (not including size of header and footer)
            uint32_t                                sz,
        //returned pointer to new allocation created by the split
            struct rv_system_memory_allocation_s    **f
        )
        {
            struct rv_system_memory_allocation_s *tf, *tn, *tnf;
            uint8_t ofllw;
        //must be freed
            if( t->is_used )
                return 0;
        //test size, must fit inside this allocation
            sz = sz + sizeof( struct rv_system_memory_allocation_s ) * 2;
            if( sz > t->size )
                return 0;
        //validate this allocation
            if( !rv_system_memory_allocation_validate( t ) )
                return 0;
        //truncate first allocation
            t->size -= sz;
            ofllw = t->is_followed;
            t->is_followed = 43;
        //fix footer
            rv_system_memory_allocation_get_components( t, &tf, 0, &tn );
            t->is_followed = ofllw;
            tf->size = t->size;
            tf->is_used = t->is_used;
            tf->is_followed = t->is_followed;
            tf->offset_object_base = t->offset_object_base;
        //init new allocation
            if( !tn )
                return 0;
            if( !rv_system_memory_allocation_create_static( tn, sz ) )
                return 0;
            rv_system_memory_allocation_get_components( tn, &tnf, 0, 0 );
            tnf->is_followed = tn->is_followed = t->is_followed;
            tf->is_followed = t->is_followed = 43;
            tnf->offset_object_base = tn->offset_object_base = 0;
            #ifdef rv_system_memory_allocation_print_all
                union
                {
                    unsigned int    ui;
                    void            *p;
                    uint32_t        ui32;
                    uint64_t        ui64;
                } u_ptr, u_sz;
                u_ptr.p = (void *)tnf;
                u_sz.ui32 = tn->size;
                fprintf( stdout, "Allocation at %u created with %u bytes.\n", u_ptr.ui, u_sz.ui );
            #endif
        //return status
            if( f )
                *f = tn;
            return 1;
        };

    //rv_system_memory_allocation_allocate() if size is same as this allocation and is free, will take this allocation.
    //                                          else if possible will split and use new allocation.
    //                                          else returns false and memory was not allocated
        bool rv_system_memory_allocation_allocate
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s    *t,
        //size of the new allocation internally (not including size of header and footer)
            uint32_t                                sz,
        //pointer to actual allocation used
            struct rv_system_memory_allocation_s    **n,
        //pointer to start of allocated memory inside allocation
            void                                    **pd,
        //are we allocating memory for an object?
            bool                                    is_rwl_object,
        //offset to object_base from start of allocation
            uint16_t                                offset_object_base
        )
        {
            struct rv_system_memory_allocation_s *f;
        //validate
            if( !rv_system_memory_allocation_validate( t ) )
                return 0;
        //if not used and size matches
            if( !t->is_used && sz == t->size )
            {
                rv_system_memory_allocation_get_components( t, &f, pd, 0 );
                f->is_used = t->is_used = 43;
                if( is_rwl_object )
                    t->offset_object_base = 1 + offset_object_base;
                else
                    t->offset_object_base = 0;
                f->offset_object_base = t->offset_object_base;
                #ifdef rv_system_memory_allocation_print_all
                    union
                    {
                        unsigned int    ui;
                        void            *p;
                        uint32_t        ui32;
                        uint64_t        ui64;
                    } u_ptr, u_sz;
                    u_ptr.p = (void *)t;
                    u_sz.ui32 = sz;
                    fprintf( stdout, "Allocation at %u used with %u bytes.\n", u_ptr.ui, u_sz.ui );
                #endif
                if( n )
                    *n = t;
                return 1;
            }
        //attempt to split
            rv_system_memory_allocation_split( t, sz, 0 );
        //attempt to allocate from next
            rv_system_memory_allocation_get_components( t, 0, 0, &f );
            if( f )
                return rv_system_memory_allocation_allocate( f, sz, n, pd, is_rwl_object, offset_object_base );
        //return fail
            return 0;
        }

    //rv_system_memory_allocation_release() finds allocation to release by address.
    //                                          if not this allocation attempts next so on and so forth
    //                                          returns true when found and released
        bool rv_system_memory_allocation_release
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s    *t,
        //pointer to start of allocated memory
            void                                    *pd
        )
        {
            struct rv_system_memory_allocation_s *n, *f;
            union
            {
                void        *d;
                uint64_t    l;
            } a, b, c;
            bool r = 0;
        //validate
            if( !rv_system_memory_allocation_validate( t ) )
                return 0;
        //test values for this allocation
            rv_system_memory_allocation_get_components( t, &f, &a.d, &n );
            if( t->is_used )
            {
                b.d = pd;
                c.l = a.l + t->size;
                if( a.l <= b.l && b.l < c.l )
                {
                    f->is_used = t->is_used = 0;
                    #ifdef rv_system_memory_allocation_print_all
                        union
                        {
                            unsigned int    ui;
                            void            *p;
                            uint32_t        ui32;
                            uint64_t        ui64;
                        } u_ptr, u_sz;
                        u_ptr.p = (void *)t;
                        u_sz.ui32 = t->size;
                        fprintf( stdout, "Allocation at %u released with %u bytes.\n", u_ptr.ui, u_sz.ui );
                    #endif
                    r = 1;
                }
            }
        //recursively combine with next allocation if its also free
            if( !t->is_used )
            {
                while( n && !n->is_used )
                {
                    t->size += n->size + sizeof( struct rv_system_memory_allocation_s ) * 2;
                    t->is_followed = n->is_followed;
                    rv_system_memory_allocation_get_components( t, &f, 0, &n );
                    f->is_followed = t->is_followed;
                    f->is_used = t->is_used;
                    f->size = t->size;
                    f->offset_object_base = t->offset_object_base;
                }
            }
            if( r )
                return 1;
        //try next allocation
            if( n )
                return rv_system_memory_allocation_release( n, pd );
        //return fail
            return 0;
        }

    //rv_system_memory_allocation_compute_size() returns size needed to hold an allocation including headers and footers
        uint32_t rv_system_memory_allocation_compute_size
        (
        //size of the data to be stored in allocation
            uint32_t    sz
        )
        {
            sz += sizeof( struct rv_system_memory_allocation_s ) * 2;
            return sz;
        }

    //rv_system_memory_allocation_print() prints info about allocation to console
        void rv_system_memory_allocation_print
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s    *t
        )
        {
            struct rv_system_memory_allocation_s *n;
        //validate
            if( !rv_system_memory_allocation_validate( t ) )
                return;
        //print
            #ifdef rv_system_memory_allocation_print_enabled
                union
                {
                    unsigned int    ui;
                    void            *p;
                    uint32_t        ui32;
                    uint64_t        ui64;
                    struct rv_system_object_base_s *ob;
                } u_ptr, u_sz;
            //used or free and size
                if( t->is_used )
                    fprintf( stdout, "\t\tUsed " );
                else
                    fprintf( stdout, "\t\tFree " );
                u_ptr.p = (void *)t;
                u_sz.ui32 = t->size;
                fprintf( stdout, "Allocation at %u with %u bytes.\n", u_ptr.ui, u_sz.ui );
            //get next and pointer to object
                rv_system_memory_allocation_get_components( t, 0, &u_ptr.p, &n );
            //print object
                if( t->is_used && t->offset_object_base )
                {
                    u_ptr.ui64 += t->offset_object_base - 1;
                    fprintf( stdout, "\t\t\t%s with size %u\n", rv_system_object_base_get_type_value( u_ptr.ob ), (unsigned int)rv_system_object_base_get_size( u_ptr.ob ) );
                }
            #else
            //get next
                rv_system_memory_allocation_get_components( t, 0, 0, &n );
            #endif
        //print next
            if( !n )
                return;
            rv_system_memory_allocation_print( n );
        };

    //rv_system_memory_allocation_get_stats() compute memory statistics
        void rv_system_memory_allocation_get_stats
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s      *t,
        //stats
            struct rv_system_memory_stats_s     *s
        )
        {
            uint32_t i;
            struct rv_system_memory_allocation_s *n;
        //validate
            if( !rv_system_memory_allocation_validate( t ) )
                return;
        //accrue stats
            i = sizeof( struct rv_system_memory_allocation_s ) * 2;
            s->cnt_allocations += 1;
            s->avg_allocation_size += i + t->size;
            s->mem_allocation_overhead += i;
            s->mem_overhead += i;
            s->allocation_size += t->size;
            if( !t->is_used )
            {
                s->mem_used -=  t->size + i;
                s->mem_free += t->size + i;
            }
            else
                s->allocation_used += t->size;
        //get next
            rv_system_memory_allocation_get_components( t, 0, 0, &n );
        //print next
            if( !n )
                return;
            rv_system_memory_allocation_get_stats( n, s );
        };

//header guard end
    #endif




