
/* ============================ rv_system_thread_writelock.h ===================================== //

    rv_system_thread_writelock.h

    writelock for thread, for querying thread stats

// ============================ rv_system_thread_writelock.h ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_thread_SLASH_rv_system_thread_writelock_DOT_h
    #define rv_system_SLASH_rv_system_thread_SLASH_rv_system_thread_writelock_DOT_h

/* ------------------- included headers --------------------------------------- */

    //object base
        #include "../rv_system_object/rv_system_object_writelock.h"

/* ------------------- structure stubs --------------------------------------- */

        char *rv_system_object_type__thread_writelock;

/* ----------- virtual function/method stubs and typedefs -------------------- */

        struct rv_system_object_base_vtble_s rv_system_thread_writelock_vtble;

/* ------------------- structure definition ---------------------------------- */

    //object writelock
        struct rv_system_thread_writelock_s
        {
        //super
            struct rv_system_object_writelock_s base;
        };

/* ------------------- static function stubs --------------------------------- */

    //rv_system_thread_writelock_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_thread_writelock_create_static
        (
        //pointer to memory holding struct
            struct rv_system_thread_writelock_s          *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                                    sz,
        //memory
            struct rv_system_memory_s                   *mem
        );
        typedef bool (* rv_system_thread_writelock_create_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_thread_writelock_s          *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                                    sz,
        //memory
            struct rv_system_memory_s                   *mem
        );

    //rv_system_thread_writelock_create_super_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_thread_writelock_create_super_static
        (
        //pointer to memory holding struct
            struct rv_system_thread_writelock_s          *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                                    sz,
        //vtble
            struct rv_system_object_base_vtble_s        *vtble,
        //top object
            void                                        *top,
        //memory
            struct rv_system_memory_s                   *mem
        );
        typedef bool (* rv_system_thread_writelock_create_super_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_thread_writelock_s          *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                                    sz,
        //vtble
            struct rv_system_object_base_vtble_s        *vtble,
        //top object
            void                                        *top,
        //memory
            struct rv_system_memory_s                   *mem
        );

    //rv_system_thread_writelock_create() initiates struct in newly allocated memory
        struct rv_system_thread_writelock_s *rv_system_thread_writelock_create
        (
        //memory
            struct rv_system_memory_s                  *mem,
        //memory lock (optional)
            struct rv_system_memory_lock_s             *mem_lock_optional
        );
        typedef struct rv_system_thread_writelock_s *(* rv_system_thread_writelock_create_ptr)
        (
        //memory
            struct rv_system_memory_s                  *mem,
        //memory lock (optional)
            struct rv_system_memory_lock_s             *mem_lock_optional
        );

    //rv_system_thread_writelock_create_super() initiates struct in newly allocated memory
    //returns top object when successful
        void *rv_system_thread_writelock_create_super
        (
        //pointer to receive base
            struct rv_system_thread_writelock_s          **pt,
        //offset to base object
            uint16_t                                    base_offset,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                                    sz,
        //vtble
            struct rv_system_object_base_vtble_s        *vtble,
        //memory
            struct rv_system_memory_s                   *mem,
        //memory lock (optional)
            struct rv_system_memory_lock_s              *mem_lock_optional
        );
        typedef void *(* rv_system_thread_writelock_create_super_ptr)
        (
        //pointer to receive base
            struct rv_system_thread_writelock_s          **pt,
        //offset to base object
            uint16_t                                    base_offset,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                                    sz,
        //vtble
            struct rv_system_object_base_vtble_s        *vtble,
        //memory
            struct rv_system_memory_s                   *mem,
        //memory lock (optional)
            struct rv_system_memory_lock_s              *mem_lock_optional
        );

    //rv_system_thread_writelock_get_super_offset() returns offset of super
        uint64_t rv_system_thread_writelock_get_super_offset
        (
            void
        );
        typedef uint64_t (* rv_system_thread_writelock_get_super_offset_ptr)
        (
            void
        );

    //rv_system_thread_writelock_get_base_offset() returns offset of base
        uint64_t rv_system_thread_writelock_get_base_offset
        (
            void
        );
        typedef uint64_t (* rv_system_thread_writelock_get_base_offset_ptr)
        (
            void
        );

/* -- virtual method corresponding static function stubs --------------------- */

    //init function, returns true if successful
        bool __rv_system_thread_writelock_init
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        );

    //deinit function
        void __rv_system_thread_writelock_deinit
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base
        );

    //get pointer to type function, returns false if not available
        bool __rv_system_thread_writelock_get_type
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to receive object of type
            void **pp,
        //string name of type to fetch
            char *ctype
        );

    //get type name function, returns size needed to copy, even if buffer is null or too small
        uint16_t __rv_system_thread_writelock_get_type_name
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //buffer to hold name
            char                                *pb,
        //size of buffer
            uint16_t                            szb
        );

    //get all type names function, returns size needed to copy even if buffer is null or too small
        uint16_t __rv_system_thread_writelock_get_all_type_names
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //buffer to hold name
            char                                *pb,
        //size to buffer
            uint16_t                            szb
        );

    //get size funcion, returns size of object and all memory owned by object including child objects
        uint64_t __rv_system_thread_writelock_get_size
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base
        );

    //get type function
        char *__rv_system_thread_writelock_get_type_value
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base
        );

    //test type function, returns true if object is of that type
        bool __rv_system_thread_writelock_is_type
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //string type name
            char *ctype
        );

/* -------- helper functions to be used by inherited objects to perform work in virtual functions --------------------- */

    //none

/* -------- structures containing easy function pointers --------------------- */

    //contains methods
        struct rv_system_thread_writelock_ptr_s
        {
        //object base
            struct rv_system_object_writelock_ptr_s                  *super;
        //create static
            rv_system_thread_writelock_create_static_ptr             create_static;
        //create super static
            rv_system_thread_writelock_create_super_static_ptr       create_super_static;
        //create
            rv_system_thread_writelock_create_ptr                    create;
        //create super
            rv_system_thread_writelock_create_super_ptr              create_super;
        //get super offset
            rv_system_thread_writelock_get_super_offset_ptr          get_super_offset;
        //get base offset
            rv_system_thread_writelock_get_base_offset_ptr           get_base_offset;
        };
        struct rv_system_thread_writelock_ptr_s rv_system_thread_writelock;

//header guard end
    #endif






