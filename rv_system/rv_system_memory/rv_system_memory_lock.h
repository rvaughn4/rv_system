
/* ============================ rv_system_memory_lock.h ===================================== //

    rv_system_memory_lock.h

    allocates memory in a thread safe manner
    memory is locked yields
        memory_lock which allocates memory, internally uses
            memory_frames's which are allocated from system calls, contains
                memory_allocations which are created when lib user requests memory
                memory_allocation structs are inline between actual memory being allocated
                memory_frame structs are inline before allocations in the page
                memory and memory_lock are created in static memory provided by the lib user (on the stack usually)

// ============================ rv_system_memory_lock.h ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_memory_SLASH_rv_system_memory_lock_DOT_h
    #define rv_system_SLASH_rv_system_memory_SLASH_rv_system_memory_lock_DOT_h

/* ------------------- included headers --------------------------------------- */

    //standard int size types
        #include <stdint.h>
    //standard boolean type
        #include <stdbool.h>
    //lock holder
        #include "../rv_system_lock/rv_system_lock_holder.h"
    //printing to console
        #define rv_system_memory_lock_print_enabled
        #define rv_system_memory_lock_print_errors
        //#define rv_system_memory_lock_print_all
    //printing to console
        #define rv_system_memory_frame_print_enabled
        #define rv_system_memory_frame_print_errors
        //#define rv_system_memory_frame_print_all
    //printing to console
        #define rv_system_memory_allocation_print_enabled
        #define rv_system_memory_allocation_print_errors
        //#define rv_system_memory_allocation_print_all

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
        struct rv_system_memory_lock_s
        {
        //pointer to memory struct
            struct rv_system_memory_s *t;
        //lock holder
            struct rv_system_lock_holder_s lh;
        };

    //memory stats
        struct rv_system_memory_stats_s
        {
            uint64_t mem_used, mem_free, mem_overhead, mem_frame_overhead, mem_allocation_overhead;
            uint64_t avg_frame_size, avg_allocation_size, frame_size, allocation_size, allocation_used;
            uint32_t cnt_frames, cnt_allocations;
        };

/* ------------------- static function stubs --------------------------------- */

    //rv_system_memory_lock_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_memory_lock_create_static
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        );
        typedef bool (* rv_system_memory_lock_create_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        );

    //rv_system_memory_lock_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_memory_lock_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s     *t
        );
        typedef void (* rv_system_memory_lock_destroy_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s     *t
        );

    //rv_system_memory_lock_create_lock() locks memory so allocation and release can take place
    //returns true when successful
        bool rv_system_memory_lock_lock
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t,
        //pointer to memory holding struct
            struct rv_system_memory_s           *l
        );
        typedef bool (* rv_system_memory_lock_lock_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t,
        //pointer to memory holding struct
            struct rv_system_memory_s           *l
        );

    //rv_system_memory_lock_create_unlock() unlocks memory
        void rv_system_memory_lock_unlock
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t
        );
        typedef void (* rv_system_memory_lock_unlock_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t
        );

    //rv_system_memory_lock_create_allocate() allocates memory from a frame and an allocation
        bool rv_system_memory_lock_allocate
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t,
        //size to allocate
            uint32_t                            sz,
        //pointer to start of allocated memory
            void                                **pd
        );
        typedef bool (* rv_system_memory_lock_allocate_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t,
        //size to allocate
            uint32_t                            sz,
        //pointer to start of allocated memory
            void                                **pd
        );

    //rv_system_memory_lock_create_release() releases memory from a frame and an allocation
        bool rv_system_memory_lock_release
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t,
        //pointer to start of allocated memory
            void                                *pd
        );
        typedef bool (* rv_system_memory_lock_release_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t,
        //pointer to start of allocated memory
            void                                *pd
        );

    //rv_system_memory_lock_create_allocate_raw() allocates raw memory from physical pages on the system
        uint32_t rv_system_memory_lock_allocate_raw
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t,
        //size to allocate
            uint32_t                            sz,
        //pointer to start of allocated memory
            void                                **pd
        );
        typedef uint32_t (* rv_system_memory_lock_allocate_raw_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t,
        //size to allocate
            uint32_t                            sz,
        //pointer to start of allocated memory
            void                                **pd
        );

    //rv_system_memory_lock_create_release_raw() releases raw memory from physical pages on the system
        bool rv_system_memory_lock_release_raw
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t,
        //size to allocate
            uint32_t                            sz,
        //pointer to start of allocated memory
            void                                *pd
        );
        typedef bool (* rv_system_memory_lock_release_raw_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t,
        //size to allocate
            uint32_t                            sz,
        //pointer to start of allocated memory
            void                                *pd
        );

    //rv_system_memory_lock_print() prints info about frame to console
        void rv_system_memory_lock_print
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s    *t
        );
        typedef void (* rv_system_memory_lock_print_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s    *t
        );

    //rv_system_memory_lock_get_stats() compute memory statistics
        void rv_system_memory_lock_get_stats
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t,
        //stats
            struct rv_system_memory_stats_s     *s
        );
        typedef void (* rv_system_memory_lock_get_stats_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t,
        //stats
            struct rv_system_memory_stats_s     *s
        );

    //rv_system_memory_lock_print_stats() print memory statistics
    //                  will create its own stats if null
        void rv_system_memory_lock_print_stats
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t,
        //stats
            struct rv_system_memory_stats_s     *s
        );
        typedef void (* rv_system_memory_lock_print_stats_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_lock_s      *t,
        //stats
            struct rv_system_memory_stats_s     *s
        );

/* -- virtual method corresponding static function stubs --------------------- */

    //none

/* -------- structures containing easy function pointers --------------------- */

    //contains struct methods
        struct rv_system_memory_lock_ptr_s
        {
        //create static
            rv_system_memory_lock_create_static_ptr     create_static;
        //destroy static
            rv_system_memory_lock_destroy_static_ptr    destroy_static;
        //lock
            rv_system_memory_lock_lock_ptr              lock;
        //unlock
            rv_system_memory_lock_unlock_ptr            unlock;
        //allocate
            rv_system_memory_lock_allocate_ptr          allocate;
        //release
            rv_system_memory_lock_release_ptr           release;
        //allocate raw
            rv_system_memory_lock_allocate_raw_ptr      allocate_raw;
        //release raw
            rv_system_memory_lock_release_raw_ptr       release_raw;
        //print
            rv_system_memory_lock_print_ptr             print;
        //get_stats
            rv_system_memory_lock_get_stats_ptr         get_stats;
        //print_stats
            rv_system_memory_lock_print_stats_ptr       print_stats;
        };
        struct rv_system_memory_lock_ptr_s rv_system_memory_lock;

//header guard end
    #endif


