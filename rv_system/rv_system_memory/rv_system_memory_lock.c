
/* ============================ rv_system_memory_lock.c ===================================== //

    rv_system_memory_lock.c

    allocates memory in a thread safe manner
    memory is locked yields
        memory_lock which allocates memory, internally uses
            memory_frames's which are allocated from system calls, contains
                memory_allocations which are created when lib user requests memory
                memory_allocation structs are inline between actual memory being allocated
                memory_frame structs are inline before allocations in the page
                memory and memory_lock are created in static memory provided by the lib user (on the stack usually)

// ============================ rv_system_memory_lock.c ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_memory_SLASH_rv_system_memory_lock_DOT_c
    #define rv_system_SLASH_rv_system_memory_SLASH_rv_system_memory_lock_DOT_c

/* ------------------- included headers --------------------------------------- */

    //headers
        #include "rv_system_memory.h"
        #include "rv_system_memory_lock.h"
        #include "rv_system_memory_frame.h"
        #include "rv_system_memory_allocation.h"
        #include "../os_define.h"
    //posix memmap
        #ifdef rv_system_os_is_posix
            #include <unistd.h>
            #include <sys/mman.h>
        #endif
        #ifdef rv_system_os_is_linux
            #include <sys/time.h>
            #include <sys/resource.h>
        #endif
    //printing
        #if !defined( rv_system_memory_lock_print_enabled ) && defined( rv_system_memory_lock_print_errors )
            #undef rv_system_memory_lock_print_errors
        #endif
        #if !defined( rv_system_memory_lock_print_enabled ) && defined( rv_system_memory_lock_print_all )
            #undef rv_system_memory_lock_print_all
        #endif
        #if defined( rv_system_memory_lock_print_all ) && !defined( rv_system_memory_lock_print_errors )
            #define rv_system_memory_lock_print_errors
        #endif
        #ifdef rv_system_memory_lock_print_enabled
            #include <stdio.h>
            #include <stdlib.h>
        #endif

/* -------- structures containing easy function pointers --------------------- */

    //contains struct methods
        struct rv_system_memory_lock_ptr_s rv_system_memory_lock =
        {
            /*.create_static=*/         rv_system_memory_lock_create_static,
            /*.destroy_static=*/        rv_system_memory_lock_destroy_static,
            /*.lock=*/                  rv_system_memory_lock_lock,
            /*.unlock=*/                rv_system_memory_lock_unlock,
            /*.allocate=*/              rv_system_memory_lock_allocate,
            /*.allocate_object=*/       rv_system_memory_lock_allocate_object,
            /*.release=*/               rv_system_memory_lock_release,
            /*.allocate_raw=*/          rv_system_memory_lock_allocate_raw,
            /*.release_raw=*/           rv_system_memory_lock_release_raw,
            /*.print=*/                 rv_system_memory_lock_print,
            /*.get_stats=*/             rv_system_memory_lock_get_stats,
            /*.print_stats=*/           rv_system_memory_lock_print_stats
        };

/* ------------------- static function definitions --------------------------------- */

    //rv_system_memory_lock_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_memory_lock_create_static
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        )
        {
        //test size
            if( sz < sizeof( struct rv_system_memory_lock_s ) )
                return 0;
        //init
            t->t = 0;
            if( !rv_system_lock_holder_create_static( &t->lh, sizeof( t->lh ) ) )
                return 0;
        //return status
            return 1;
        }

    //rv_system_memory_lock_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_memory_lock_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s     *t
        )
        {
        //unlock
            rv_system_memory_lock_unlock( t );
        //destroy holder
            rv_system_lock_holder_destroy_static( &t->lh );
        }

    //rv_system_memory_lock_create_lock() locks memory so allocation and release can take place
    //returns true when successful
        bool rv_system_memory_lock_lock
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t,
        //pointer to memory holding struct
            struct rv_system_memory_s           *l
        )
        {
        //attempt to lock memory
            rv_system_lock_holder_clear( &t->lh );
            if( !rv_system_lock_holder_add( &t->lh, &l->lk ) )
                return 0;
            if( !rv_system_lock_holder_lock( &t->lh, 1, 0, 1 ) )
                return 0;
        //sucess
            t->t = l;
            return 1;
        }

    //rv_system_memory_lock_create_unlock() unlocks memory
        void rv_system_memory_lock_unlock
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t
        )
        {
            t->t = 0;
            rv_system_lock_holder_clear( &t->lh );
        }

    //rv_system_memory_lock_create_allocate() allocates memory from a frame and an allocation
        bool rv_system_memory_lock_allocate
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t,
        //size to allocate
            uint32_t                            sz,
        //pointer to start of allocated memory
            void                                **pd
        )
        {
            return rv_system_memory_lock_allocate_object( t, sz, pd, 0, 0 );
        }

    //rv_system_memory_lock_create_allocate_object() allocates memory from a frame and an allocation
        bool rv_system_memory_lock_allocate_object
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s          *t,
        //size to allocate
            uint32_t                                sz,
        //pointer to start of allocated memory
            void                                    **pd,
        //is object
            bool                                    is_rv_object,
        //object base offset after start of allocation
            uint16_t                                offset_object_base
        )
        {
            bool r;
        //must be locked
            if( !t->t )
                return 0;
        //allocate
            if( !t->t->first )
                return 0;
            r = rv_system_memory_frame_allocate( t->t->first, sz, pd, t, is_rv_object, offset_object_base );
            #ifdef rv_system_memory_lock_print_errors
                if( !r )
                    fprintf( stdout, "Failed allocating memory %u bytes\n", (unsigned int)sz );
            #endif
            #ifdef rv_system_memory_lock_print_all
                if( r )
                    fprintf( stdout, "Allocating memory %u bytes\n", (unsigned int)sz );
                rv_system_memory_lock_print( t );
            #endif
            return r;
        }

    //rv_system_memory_lock_create_release() releases memory from a frame and an allocation
        bool rv_system_memory_lock_release
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t,
        //pointer to start of allocated memory
            void                                *pd
        )
        {
            bool r;
        //must be locked first
            if( !t->t )
                return 0;
        //release from frame
            if( !t->t->first )
                return 0;
            r = rv_system_memory_frame_release( t->t->first, pd );
            #ifdef rv_system_memory_lock_print_errors
                union
                {
                    unsigned int ui;
                    void    *p;
                } u_ptr;
                u_ptr.p = pd;
                if( !r )
                    fprintf( stdout, "Failed releasing memory %X\n", u_ptr.ui );
            #endif
            #ifdef rv_system_memory_lock_print_all
                if( r )
                    fprintf( stdout, "Releasing memory %u\n", u_ptr.ui );
                rv_system_memory_lock_print( t );
            #endif
            return r;
        }

    //rv_system_memory_lock_create_allocate_raw() allocates raw memory from physical pages on the system
        uint32_t rv_system_memory_lock_allocate_raw
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t,
        //size to allocate
            uint32_t                            sz,
        //pointer to start of allocated memory
            void                                **pd
        )
        {
            uint32_t pg_sz =4098, i;
            void *r = 0;
        //must be locked first
            if( !t->t )
                return 0;
        //find page size
            #ifdef rv_system_os_is_posix
                pg_sz = sysconf( _SC_PAGE_SIZE );
            #endif
        //page align size to allocate
            i = 0;
            while( i < sz )
                i += pg_sz;
        //attempt to allocate
            #ifdef rv_system_os_is_posix
                #ifndef MAP_ANONYMOUS
                    #define MAP_ANONYMOUS 0
                #endif
                r = mmap( 0, i, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0 );
                if( r == MAP_FAILED )
                    r = 0;
            #endif
            if( !r )
                return 0;
        //return results
            *pd = r;
            return i;
        }

    //rv_system_memory_lock_create_release_raw() releases raw memory from physical pages on the system
        bool rv_system_memory_lock_release_raw
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t,
        //size to allocate
            uint32_t                            sz,
        //pointer to start of allocated memory
            void                                *pd
        )
        {
            bool r = 0;
        //must be locked first
            if( !t->t )
                return 0;
        //release
            #ifdef rv_system_os_is_posix
                r = munmap( pd, sz ) == 0;
            #endif
        //return status
            return r;
        }

    //rv_system_memory_lock_print() prints info about frame to console
        void rv_system_memory_lock_print
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s    *t,
        //line prefix /indentation
            char                              *pref
        )
        {
        //must be locked
            if( !t->t )
                return;
        //print
            #ifdef rv_system_memory_lock_print_enabled
                fprintf( stdout, "%sMemory Lock Printout %s\n", pref, "" );
            #endif
        //print next
            if( t->t->first )
                rv_system_memory_frame_print( t->t->first, pref );
        }

    //rv_system_memory_lock_get_stats() compute memory statistics
        void rv_system_memory_lock_get_stats
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t,
        //stats
            struct rv_system_memory_stats_s     *s
        )
        {
        //init
            s->avg_allocation_size = 0;
            s->avg_frame_size = 0;
            s->cnt_allocations = 0;
            s->cnt_frames = 0;
            s->mem_allocation_overhead = 0;
            s->mem_frame_overhead = 0;
            s->mem_free = 0;
            s->mem_overhead = 0;
            s->mem_used = 0;
            s->allocation_size = 0;
            s->frame_size = 0;
            s->allocation_used = 0;
            #ifdef rv_system_os_is_linux
                struct rlimit rl;
                getrlimit( RLIMIT_MEMLOCK, &rl );
                s->mem_free = rl.rlim_cur;
            #endif
        //must be locked
            if( !t->t )
                return;
        //print next
            if( t->t->first )
                rv_system_memory_frame_get_stats( t->t->first, s );
        //compute averages
            if( s->cnt_allocations )
                s->avg_allocation_size /= s->cnt_allocations;
            if( s->cnt_frames )
                s->avg_frame_size /= s->cnt_frames;
        }

    //rv_system_memory_lock_print_stats() print memory statistics
    //                  will create its own stats if null
        void rv_system_memory_lock_print_stats
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t,
        //stats
            struct rv_system_memory_stats_s     *s,
        //line prefix /indentation
            char                                *pref
        )
        {
            struct rv_system_memory_stats_s ss;
        //if not stats provided we must get our own
            if( !s )
            {
                s = &ss;
                rv_system_memory_lock_get_stats( t, s );
            }
            #ifdef rv_system_memory_lock_print_enabled
                fprintf( stdout, "%sMemory Stats\n", pref );
            //print allocation stats
                fprintf( stdout, "%s\tAllocations\n", pref );
                fprintf( stdout, "%s\t\tCount: %u allocations\n", pref, (unsigned int)s->cnt_allocations );
                fprintf( stdout, "%s\t\tAvg Size: %u bytes\n", pref, (unsigned int)s->avg_allocation_size );
                fprintf( stdout, "%s\t\tOverhead: %u bytes\n", pref, (unsigned int)s->mem_allocation_overhead );
                fprintf( stdout, "%s\t\tTotal: %u bytes\n", pref, (unsigned int)s->allocation_size );
                fprintf( stdout, "%s\t\tUsed: %u bytes\n", pref, (unsigned int)s->allocation_used );
            //print frame stats
                fprintf( stdout, "%s\tFrames\n", pref );
                fprintf( stdout, "%s\t\tCount: %u frames\n", pref, (unsigned int)s->cnt_frames );
                fprintf( stdout, "%s\t\tAvg Size: %u bytes\n", pref, (unsigned int)s->avg_frame_size );
                fprintf( stdout, "%s\t\tOverhead: %u bytes\n", pref, (unsigned int)s->mem_frame_overhead );
                fprintf( stdout, "%s\t\tTotal: %u bytes\n", pref, (unsigned int)s->frame_size );
            //print overall stats
                fprintf( stdout, "%s\tTotals\n", pref );
                fprintf( stdout, "%s\t\tUsed: %u bytes\n", pref, (unsigned int)s->mem_used );
                fprintf( stdout, "%s\t\tFree: %u bytes\n", pref, (unsigned int)s->mem_free );
                fprintf( stdout, "%s\t\tOverhead: %u bytes\n", pref, (unsigned int)s->mem_overhead );
            #endif
        }

//header guard end
    #endif



