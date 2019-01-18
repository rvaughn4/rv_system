
/* ============================ rv_system_memory_frame.h ===================================== //

    rv_system_memory_frame.h

    allocates memory in a thread safe manner
    memory is locked yields
        memory_lock which allocates memory, internally uses
            memory_frames's which are allocated from system calls, contains
                memory_allocations which are created when lib user requests memory
                memory_allocation structs are inline between actual memory being allocated
                memory_frame structs are inline before allocations in the page
                memory and memory_lock are created in static memory provided by the lib user (on the stack usually)

// ============================ rv_system_memory_frame.h ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_memory_SLASH_rv_system_memory_frame_DOT_h
    #define rv_system_SLASH_rv_system_memory_SLASH_rv_system_memory_frame_DOT_h

/* ------------------- included headers --------------------------------------- */

    //standard int size types
        #include <stdint.h>
    //standard boolean type
        #include <stdbool.h>
    //printing
        //#define rv_system_memory_frame_print_enabled
        //#define rv_system_memory_frame_print_errors
        //#define rv_system_memory_frame_print_all

/* ------------------- structure stubs --------------------------------------- */

    //main memory lib
        struct rv_system_memory_s;
    //locked memory lib
        struct rv_system_memory_lock_s;
    //memory frame
        struct rv_system_memory_frame_s;
    //memory allocation
        struct rv_system_memory_allocation_s;
    //stats
        struct rv_system_memory_stats_s;

/* ----------- virtual function/method stubs and typedefs -------------------- */

    //none

/* ------------------- structure definition ---------------------------------- */

    //memory frame struct
        struct rv_system_memory_frame_s
        {
        //stats
            uint64_t    size;
        //next frame
            struct rv_system_memory_frame_s *next;
        };

/* ------------------- static function stubs --------------------------------- */

    //rv_system_memory_create_frame_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_memory_frame_create_static
        (
        //pointer to memory holding struct
            struct rv_system_memory_frame_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        );
        typedef bool (* rv_system_memory_frame_create_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_frame_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        );

    //rv_system_memory_frame_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_memory_frame_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_memory_frame_s         *t,
        //memory lock
            struct rv_system_memory_lock_s          *ml
        );
        typedef void (* rv_system_memory_frame_destroy_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_frame_s         *t,
        //memory lock
            struct rv_system_memory_lock_s          *ml
        );

    //rv_system_memory_frame_get_components() gets offsets to parts of frame
        void rv_system_memory_frame_get_components
        (
        //pointer to memory holding struct
            struct rv_system_memory_frame_s         *t,
        //pointer to footer
            struct rv_system_memory_frame_s         **f,
        //pointer to allocation
            struct rv_system_memory_allocation_s    **a
        );
        typedef void (* rv_system_memory_frame_get_components_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_frame_s         *t,
        //pointer to footer
            struct rv_system_memory_frame_s         **f,
        //pointer to allocation
            struct rv_system_memory_allocation_s    **a
        );

    //rv_system_memory_frame_validate() verifies consistency of header and footer
        bool rv_system_memory_frame_verify
        (
        //pointer to memory holding struct
            struct rv_system_memory_frame_s         *t
        );
        typedef bool (* rv_system_memory_frame_verify_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_frame_s         *t
        );

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
        );
        typedef bool (* rv_system_memory_frame_allocate_ptr)
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
        );

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
        );
        typedef bool (* rv_system_memory_frame_release_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_frame_s         *t,
        //pointer to start of allocated memory
            void                                    *pd
        );

    //rv_system_memory_frame_compute_size() fiqures size needed to store memory including frame header and footer and allocation header and footer
        uint32_t rv_system_memory_frame_compute_size
        (
        //size required of data
            uint32_t    sz
        );
        typedef uint32_t (* rv_system_memory_frame_compute_size_ptr)
        (
        //size required of data
            uint32_t    sz
        );

    //rv_system_memory_frame_print() prints info about frame to console
        void rv_system_memory_frame_print
        (
        //pointer to memory holding struct
            struct rv_system_memory_frame_s    *t
        );
        typedef void (* rv_system_memory_frame_print_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_frame_s    *t
        );

    //rv_system_memory_lock_get_stats() compute memory statistics
        void rv_system_memory_frame_get_stats
        (
        //pointer to memory holding struct
            struct rv_system_memory_frame_s      *t,
        //stats
            struct rv_system_memory_stats_s     *s
        );
        typedef void (* rv_system_memory_frame_get_stats_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_frame_s      *t,
        //stats
            struct rv_system_memory_stats_s     *s
        );

/* -- virtual method corresponding static function stubs --------------------- */

    //none

/* -------- structures containing easy function pointers --------------------- */

    //contains struct methods
        struct rv_system_memory_frame_ptr_s
        {
        //create static
            rv_system_memory_frame_create_static_ptr    create_static;
        //destroy static
            rv_system_memory_frame_destroy_static_ptr   destroy_static;
        //get components
            rv_system_memory_frame_get_components_ptr   get_components;
        //verify
            rv_system_memory_frame_verify_ptr           verify;
        //allocate
            rv_system_memory_frame_allocate_ptr         allocate;
        //release
            rv_system_memory_frame_release_ptr          release;
        //compute size
            rv_system_memory_frame_compute_size_ptr     compute_size;
        //print
            rv_system_memory_frame_print_ptr            print;
        //get_stats
            rv_system_memory_frame_get_stats_ptr        get_stats;
        };
        struct rv_system_memory_frame_ptr_s rv_system_memory_frame;

//header guard end
    #endif


