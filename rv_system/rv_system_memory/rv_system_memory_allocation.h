
/* ============================ rv_system_memory_allocation.h ===================================== //

    rv_system_memory_allocation.h

    allocates memory in a thread safe manner
    memory is locked yields
        memory_lock which allocates memory, internally uses
            memory_frames's which are allocated from system calls, contains
                memory_allocations which are created when lib user requests memory
                memory_allocation structs are inline between actual memory being allocated
                memory_frame structs are inline before allocations in the page
                memory and memory_lock are created in static memory provided by the lib user (on the stack usually)

// ============================ rv_system_memory_allocation.h ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_memory_SLASH_rv_system_memory_allocation_DOT_h
    #define rv_system_SLASH_rv_system_memory_SLASH_rv_system_memory_allocation_DOT_h

/* ------------------- included headers --------------------------------------- */

    //standard int size types
        #include <stdint.h>
    //standard boolean type
        #include <stdbool.h>
    //debug print out
        //#define rv_system_memory_allocation_print_enabled
        //#define rv_system_memory_allocation_print_errors
        //#define rv_system_memory_allocation_print_all

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
        struct rv_system_memory_allocation_s
        {
        //stats
            uint32_t    size;
        //is allocated
            uint8_t     is_used;
        //does allocation have another after it
            uint8_t     is_followed;
        //(offset to object_base+1), is nonzero if offset stored, if zero not an object
            uint16_t    offset_object_base;
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
        );
        typedef bool (* rv_system_memory_allocation_create_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        );

    //rv_system_memory_allocation_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_memory_allocation_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s     *t
        );
        typedef void (* rv_system_memory_allocation_destroy_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s     *t
        );

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
        );
        typedef void (* rv_system_memory_allocation_get_components_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s     *t,
        //pointer to footer
            struct rv_system_memory_allocation_s     **f,
        //pointer to data
            void                                    **pd,
        //pointer to next
            struct rv_system_memory_allocation_s     **n
        );

    //rv_system_memory_allocation_validate() verifies allocation header and footer to catch overruns
        bool rv_system_memory_allocation_validate
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s     *t
        );
        typedef bool (* rv_system_memory_allocation_validate_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s     *t
        );

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
        );
        typedef bool (* rv_system_memory_allocation_split_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s    *t,
        //size of the new allocation internally (not including size of header and footer)
            uint32_t                                sz,
        //returned pointer to new allocation created by the split
            struct rv_system_memory_allocation_s    **f
        );

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
        );
        typedef bool (* rv_system_memory_allocation_allocate_ptr)
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
        );

    //rv_system_memory_allocation_release() finds allocation to release by address.
    //                                          if not this allocation attempts next so on and so forth
    //                                          returns true when found and released
        bool rv_system_memory_allocation_release
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s    *t,
        //pointer to start of allocated memory
            void                                    *pd
        );
        typedef bool (* rv_system_memory_allocation_release_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s    *t,
        //pointer to start of allocated memory
            void                                    *pd
        );

    //rv_system_memory_allocation_compute_size() returns size needed to hold an allocation including headers and footers
        uint32_t rv_system_memory_allocation_compute_size
        (
        //size of the data to be stored in allocation
            uint32_t    sz
        );
        typedef uint32_t (* rv_system_memory_allocation_compute_size_ptr)
        (
        //size of the data to be stored in allocation
            uint32_t    sz
        );

    //rv_system_memory_allocation_print() prints info about allocation to console
        void rv_system_memory_allocation_print
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s    *t
        );
        typedef void (* rv_system_memory_allocation_print_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s    *t
        );

    //rv_system_memory_allocation_get_stats() compute memory statistics
        void rv_system_memory_allocation_get_stats
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s      *t,
        //stats
            struct rv_system_memory_stats_s     *s
        );
        typedef void (* rv_system_memory_allocation_get_stats_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_memory_allocation_s      *t,
        //stats
            struct rv_system_memory_stats_s     *s
        );

/* -- virtual method corresponding static function stubs --------------------- */

    //none

/* -------- structures containing easy function pointers --------------------- */

    //contains struct methods
        struct rv_system_memory_allocation_ptr_s
        {
        //create static
            rv_system_memory_allocation_create_static_ptr   create_static;
        //destroy static
            rv_system_memory_allocation_destroy_static_ptr  destroy_static;
        //get components
            rv_system_memory_allocation_get_components_ptr  get_components;
        //validate
            rv_system_memory_allocation_validate_ptr        validate;
        //split
            rv_system_memory_allocation_split_ptr           split;
        //allocate
            rv_system_memory_allocation_allocate_ptr        allocate;
        //release
            rv_system_memory_allocation_release_ptr         release;
        //compute size
            rv_system_memory_allocation_compute_size_ptr    compute_size;
        //print
            rv_system_memory_allocation_print_ptr           print;
        //get_stats
            rv_system_memory_allocation_get_stats_ptr       get_stats;
        };
        struct rv_system_memory_allocation_ptr_s rv_system_memory_allocation;

//header guard end
    #endif



