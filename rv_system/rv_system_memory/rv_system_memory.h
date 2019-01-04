
/* ============================ rv_system_memory.h ===================================== //

    rv_system_memory.h

    allocates memory in a thread safe manner
    memory is locked yields
        memory_lock which allocates memory, internally uses
            memory_frames's which are allocated from system calls, contains
                memory_allocations which are created when lib user requests memory
                memory_allocation structs are inline between actual memory being allocated
                memory_frame structs are inline before allocations in the page
                memory and memory_lock are created in static memory provided by the lib user (on the stack usually)

// ============================ rv_system_memory.h ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_memory_SLASH_rv_system_memory_DOT_h
    #define rv_system_SLASH_rv_system_memory_SLASH_rv_system_memory_DOT_h

/* ------------------- included headers --------------------------------------- */

    //standard int size types
        #include <stdint.h>
    //standard boolean type
        #include <stdbool.h>
    //lock
        #include "../rv_system_lock/rv_system_lock.h"

/* ------------------- structure stubs --------------------------------------- */

    //main memory lib
        struct rv_system_memory_s;
    //locked memory lib
        struct rv_system_memory_lock_s;
    //memory frame
        struct rv_system_memory_frame_s;

/* ----------- virtual function/method stubs and typedefs -------------------- */

    //none

/* ------------------- structure definition ---------------------------------- */

    //memory struct
        struct rv_system_memory_s
        {
        //lock
            struct rv_system_lock_s lk;
        //first frame
            struct rv_system_memory_frame_s *first;
        };

/* ------------------- static function stubs --------------------------------- */

    //rv_system_memory_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_memory_create_static
        (
        //pointer to memory holding struct
            struct rv_system_memory_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        );
        typedef bool (* rv_system_memory_create_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        );

    //rv_system_memory_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_memory_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_memory_s     *t
        );
        typedef void (* rv_system_memory_destroy_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_s     *t
        );

/* -- virtual method corresponding static function stubs --------------------- */

    //none

/* -------- structures containing easy function pointers --------------------- */

    //contains struct methods
        struct rv_system_memory_ptr_s
        {
        //create static
            rv_system_memory_create_static_ptr    create_static;
        //destroy static
            rv_system_memory_destroy_static_ptr   destroy_static;
        };
        struct rv_system_memory_ptr_s rv_system_memory;

//header guard end
    #endif

