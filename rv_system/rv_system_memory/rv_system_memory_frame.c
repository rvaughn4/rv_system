
/* ============================ rv_system_memory_frame.c ===================================== //

    rv_system_memory_frame.c

    allocates memory in a thread safe manner
    memory is locked yields
        memory_lock which allocates memory, internally uses
            memory_frames's which are allocated from system calls, contains
                memory_allocations which are created when lib user requests memory
                memory_allocation structs are inline between actual memory being allocated
                memory_frame structs are inline before allocations in the page
                memory and memory_lock are created in static memory provided by the lib user (on the stack usually)

// ============================ rv_system_memory_frame.c ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_memory_SLASH_rv_system_memory_frame_DOT_c
    #define rv_system_SLASH_rv_system_memory_SLASH_rv_system_memory_frame_DOT_c

/* ------------------- included headers --------------------------------------- */

    //headers
        #include "rv_system_memory.h"
        #include "rv_system_memory_lock.h"
        #include "rv_system_memory_frame.h"
        #include "rv_system_memory_allocation.h"
    //printing
        #if !defined( rv_system_memory_frame_print_enabled ) && defined( rv_system_memory_frame_print_errors )
            #undef rv_system_memory_frame_print_errors
        #endif
        #if !defined( rv_system_memory_frame_print_enabled ) && defined( rv_system_memory_frame_print_all )
            #undef rv_system_memory_frame_print_all
        #endif
        #if defined( rv_system_memory_frame_print_all ) && !defined( rv_system_memory_frame_print_errors )
            #define rv_system_memory_frame_print_errors
        #endif
        #ifdef rv_system_memory_frame_print_enabled
            #include <stdio.h>
            #include <stdlib.h>
        #endif

/* -------- structures containing easy function pointers --------------------- */

    //contains struct methods
        struct rv_system_memory_frame_ptr_s rv_system_memory_frame =
        {
            /*.create_static=*/ rv_system_memory_frame_create_static,
            /*.destroy_static=*/ rv_system_memory_frame_destroy_static,
            /*.get_components=*/ rv_system_memory_frame_get_components,
            /*.verfiy=*/ rv_system_memory_frame_verify,
            /*.allocate=*/ rv_system_memory_frame_allocate,
            /*.release=*/ rv_system_memory_frame_release,
            /*.compute_size=*/ rv_system_memory_frame_compute_size,
            /*.print=*/ rv_system_memory_frame_print,
            /*.get_stats=*/ rv_system_memory_frame_get_stats
        };

/* ------------------- static function definitions --------------------------------- */

    //rv_system_memory_create_frame_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_memory_frame_create_static
        (
        //pointer to memory holding struct
            struct rv_system_memory_frame_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        )
        {
            struct rv_system_memory_frame_s *f;
            struct rv_system_memory_allocation_s *a;
        //test size
            if( sz < sizeof( struct rv_system_memory_frame_s ) * 2 )
                return 0;
        //init
            t->next = 0;
            t->size = 0;
        //compute frame size
            t->size = sz - sizeof( struct rv_system_memory_frame_s ) * 2;
        //set values
            rv_system_memory_frame_get_components( t, &f, &a );
            f->next = t->next;
            f->size = t->size;
        //create first allocation
            if( !rv_system_memory_allocation_create_static( a, t->size ) )
                return 0;
        //return sucess
            return rv_system_memory_frame_verify( t );
        }

    //rv_system_memory_frame_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_memory_frame_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_memory_frame_s         *t,
        //memory lock
            struct rv_system_memory_lock_s          *ml
        )
        {
            struct rv_system_memory_frame_s *f;
            struct rv_system_memory_allocation_s *a;
        //validate
            if( !rv_system_memory_frame_verify( t ) )
                return;
        //remove next frame
            rv_system_memory_frame_get_components( t, &f, &a );
            if( t->next && ml )
            {
                rv_system_memory_frame_destroy_static( t->next, ml );
                rv_system_memory_lock_release_raw( ml, t->next->size + sizeof( struct rv_system_memory_frame_s ) * 2, t->next );
                f->next = t->next = 0;
            }
        //release all allocations
            rv_system_memory_allocation_destroy_static( a );
        };

    //rv_system_memory_frame_get_components() gets offsets to parts of frame
        void rv_system_memory_frame_get_components
        (
        //pointer to memory holding struct
            struct rv_system_memory_frame_s         *t,
        //pointer to footer
            struct rv_system_memory_frame_s         **f,
        //pointer to allocation
            struct rv_system_memory_allocation_s    **a
        )
        {
            union
            {
                uint64_t                                l;
                struct rv_system_memory_frame_s         *t;
                struct rv_system_memory_allocation_s    *a;
            } u;
        //init
            u.t = t;
        //allocation
            u.l += sizeof( struct rv_system_memory_frame_s );
            if( a )
                *a = u.a;
        //footer
            u.l += t->size;
            if( f )
                *f = u.t;
        };

    //rv_system_memory_frame_validate() verifies consistency of header and footer
        bool rv_system_memory_frame_verify
        (
        //pointer to memory holding struct
            struct rv_system_memory_frame_s         *t
        )
        {
            struct rv_system_memory_frame_s *f;
            bool b;
        //get footer
            rv_system_memory_frame_get_components( t, &f, 0 );
        //verify
            b = t->next == f->next;
            b &= t->size == f->size;
        //return results
            #ifdef rv_system_memory_frame_print_errors
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
                    fprintf( stderr, "Frame at %u validate error with %u bytes\n", u_ptr.ui, u_sz.ui );
                }
            #endif
            return b;
        };

    //rv_system_memory_frame_allocate() attempts to allocate from an allocation on this frame
    //                                      else allocates from next frame or
    //                                      creates next frame then allocates from it
    //                                      returns false if all else fails
        bool rv_system_memory_frame_allocate
        (
        //pointer to memory holding struct
            struct rv_system_memory_frame_s         *t,
        //size to allocate
            uint32_t                                sz,
        //pointer to start of allocated memory
            void                                    **pd,
        //memory lock
            struct rv_system_memory_lock_s          *ml,
        //is object
            bool                                    is_rv_object,
        //object base offset after start of allocation
            uint16_t                                offset_object_base
        )
        {
            uint32_t nsz, i;
            struct rv_system_memory_frame_s *f, *nf;
            struct rv_system_memory_allocation_s *a;
        //verify
            if( !rv_system_memory_frame_verify( t ) )
                return 0;
        //allocate from this frame first
            rv_system_memory_frame_get_components( t, &f, &a );
            if( rv_system_memory_allocation_allocate( a, sz, 0, pd, is_rv_object, offset_object_base ) )
                return 1;
        //create next frame
            if( !t->next && ml )
            {
                nsz = rv_system_memory_frame_compute_size( sz * 2 );
                i = 0;
                while( i < nsz )
                    i += 4098;
                nsz = i;
                nf = 0;
                if( !rv_system_memory_lock_allocate_raw( ml, nsz, (void **)&nf ) )
                    return 0;
                if( !nf )
                    return 0;
                if( !rv_system_memory_frame_create_static( nf, nsz ) )
                {
                    rv_system_memory_lock_release_raw( ml, nsz, nf );
                    return 0;
                }
                #ifdef rv_system_memory_frame_print_all
                    union
                    {
                        unsigned int    ui;
                        void            *p;
                        uint32_t        ui32;
                        uint64_t        ui64;
                    } u_ptr, u_sz;
                    u_ptr.p = (void *)nf;
                    u_sz.ui32 = nsz;
                    fprintf( stdout, "Frame at %u created with %u bytes\n", u_ptr.ui, u_sz.ui );
                #endif
                f->next = t->next = nf;
            }
        //allocate from next frame
            if( !t->next )
                return 0;
            return rv_system_memory_frame_allocate( t->next, sz, pd, ml, is_rv_object, offset_object_base );
        }

    //rv_system_memory_frame_release() releases memory at address
    //                                      attempts to release from allocations in this frame
    //                                      or releases from next frame recursively
    //                                      returns false if all else fails
        bool rv_system_memory_frame_release
        (
        //pointer to memory holding struct
            struct rv_system_memory_frame_s         *t,
        //pointer to start of allocated memory
            void                                    *pd
        )
        {
            struct rv_system_memory_allocation_s *a;
        //verify
            if( !rv_system_memory_frame_verify( t ) )
                return 0;
        //attempt releasing from allocation
            rv_system_memory_frame_get_components( t, 0, &a );
            if( rv_system_memory_allocation_release( a, pd ) )
                return 1;
        //attempt to release from next frame
            if( !t->next )
                return 0;
            t = t->next;
            return rv_system_memory_frame_release( t, pd );
        }

    //rv_system_memory_frame_compute_size() fiqures size needed to store memory including frame header and footer and allocation header and footer
        uint32_t rv_system_memory_frame_compute_size
        (
        //size required of data
            uint32_t    sz
        )
        {
            sz = rv_system_memory_allocation_compute_size( sz );
            sz += sizeof( struct rv_system_memory_frame_s ) * 2;
            return sz;
        }

    //rv_system_memory_frame_print() prints info about frame to console
        void rv_system_memory_frame_print
        (
        //pointer to memory holding struct
            struct rv_system_memory_frame_s    *t
        )
        {
            struct rv_system_memory_allocation_s *a;
        //validate
            if( !rv_system_memory_frame_verify( t ) )
                return;
        //print
            #ifdef rv_system_memory_frame_print_enabled
                union
                {
                    unsigned int    ui;
                    void            *p;
                    uint32_t        ui32;
                    uint64_t        ui64;
                } u_ptr, u_sz;
                u_ptr.p = (void *)t;
                u_sz.ui32 = t->size;
                fprintf( stdout, "\tFrame at %u with %u bytes.\n", u_ptr.ui, u_sz.ui );
            #endif
        //get next
            rv_system_memory_frame_get_components( t, 0, &a );
        //print allocation
            if( a )
                rv_system_memory_allocation_print( a );
        //print next
            if( t->next )
                rv_system_memory_frame_print( t->next );
        };

    //rv_system_memory_lock_get_stats() compute memory statistics
        void rv_system_memory_frame_get_stats
        (
        //pointer to memory holding struct
            struct rv_system_memory_frame_s      *t,
        //stats
            struct rv_system_memory_stats_s     *s
        )
        {
            struct rv_system_memory_allocation_s *a;
            uint32_t i;
        //validate
            if( !rv_system_memory_frame_verify( t ) )
                return;
        //accrue frame stats
            i = sizeof( struct rv_system_memory_frame_s ) * 2;
            s->cnt_frames += 1;
            s->avg_frame_size += t->size + i;
            s->mem_frame_overhead += i;
            s->mem_overhead += i;
            s->mem_used += i + t->size;
            s->mem_free -= i + t->size;
            s->frame_size += t->size;
        //get next
            rv_system_memory_frame_get_components( t, 0, &a );
        //print allocation
            if( a )
                rv_system_memory_allocation_get_stats( a, s );
        //print next
            if( t->next )
                rv_system_memory_frame_get_stats( t->next, s );
        };

//header guard end
    #endif



