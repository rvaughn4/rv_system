
/* ============================ rv_system_memory.c ===================================== //

    rv_system_memory.c

    allocates memory in a thread safe manner
    memory is locked yields
        memory_lock which allocates memory, internally uses
            memory_frames's which are allocated from system calls, contains
                memory_allocations which are created when lib user requests memory
                memory_allocation structs are inline between actual memory being allocated
                memory_frame structs are inline before allocations in the page
                memory and memory_lock are created in static memory provided by the lib user (on the stack usually)

// ============================ rv_system_memory.c ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_memory_SLASH_rv_system_memory_DOT_c
    #define rv_system_SLASH_rv_system_memory_SLASH_rv_system_memory_DOT_c

/* ------------------- included headers --------------------------------------- */

    //header
        #include "rv_system_memory.h"
        #include "rv_system_memory_lock.h"
        #include "rv_system_memory_frame.h"

/* -------- structures containing easy function pointers --------------------- */

    //contains struct methods
        struct rv_system_memory_ptr_s rv_system_memory =
        {
            /*.create_static=*/ rv_system_memory_create_static,
            /*.destroy_static=*/ rv_system_memory_destroy_static
        };

/* ------------------- static function definitions --------------------------------- */

    //rv_system_memory_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_memory_create_static
        (
        //pointer to memory holding struct
            struct rv_system_memory_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        )
        {
            struct rv_system_memory_lock_s mlk;
            uint32_t nsz;
        //test size
            if( sz < sizeof( struct rv_system_memory_s ) )
                return 0;
        //init
            t->first = 0;
        //setup lock
            if( !rv_system_lock_create_static( &t->lk, sizeof( t->lk ) ) )
                return 0;
        //lock memory
            if( !rv_system_memory_lock_create_static( &mlk, sizeof( mlk ) ) )
                return 0;
            if( !rv_system_memory_lock_lock( &mlk, t ) )
                return 0;
        //create first frame
            nsz = rv_system_memory_lock_allocate_raw( &mlk, 1, (void **)&t->first );
            if( nsz )
            {
                if( !rv_system_memory_frame_create_static( t->first, nsz ) )
                {
                    rv_system_memory_lock_release_raw( &mlk, nsz, t->first );
                    t->first = 0;
                }
            }
        //unlock memory
            rv_system_memory_lock_destroy_static( &mlk );
        //return sucess
            return t->first != 0;
        }

    //rv_system_time_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_memory_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_memory_s     *t
        )
        {
            struct rv_system_memory_lock_s mlk;
            uint32_t nsz;
        //lock memory
            if( !rv_system_memory_lock_create_static( &mlk, sizeof( mlk ) ) )
                return;
            if( !rv_system_memory_lock_lock( &mlk, t ) )
                return;
        //release first frame
            if( t->first )
            {
                nsz = t->first->size + sizeof( struct rv_system_memory_frame_s ) * 2;
                rv_system_memory_frame_destroy_static( t->first, &mlk );
                rv_system_memory_lock_release_raw( &mlk, nsz, t->first );
                t->first = 0;
            }
        //unlock memory
            rv_system_memory_lock_destroy_static( &mlk );
        }

//header guard end
    #endif


