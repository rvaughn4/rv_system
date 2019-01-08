
/* ============================ rv_system_object_writelock.h ===================================== //

    rv_system_object_writelock.h

    handles vtble for objects and ctor and dtor

// ============================ rv_system_object_writelock.h ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_object_SLASH_rv_system_object_writelock_DOT_h
    #define rv_system_SLASH_rv_system_object_SLASH_rv_system_object_writelock_DOT_h

/* ------------------- included headers --------------------------------------- */

    //object base
        #include "rv_system_object_base.h"

/* ------------------- structure stubs --------------------------------------- */

    #define rv_system_object_type__object_writelock "rv_system_object_type__object_writelock"

/* ----------- virtual function/method stubs and typedefs -------------------- */

        struct rv_system_object_base_vtble_s rv_system_object_writelock_vtble;

/* ------------------- structure definition ---------------------------------- */

    //object writelock
        struct rv_system_object_writelock_s
        {
        //super
            struct rv_system_object_base_s base;
        //object
            struct rv_system_object_s *obj;
        };

/* ------------------- static function stubs --------------------------------- */

    //rv_system_object_writelock_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_object_writelock_create_static
        (
        //pointer to memory holding struct
            struct rv_system_object_writelock_s          *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                                    sz,
        //memory
            struct rv_system_memory_s                   *mem
        );
        typedef bool (* rv_system_object_writelock_create_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_object_writelock_s          *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                                    sz,
        //memory
            struct rv_system_memory_s                   *mem
        );

    //rv_system_object_writelock_create_super_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_object_writelock_create_super_static
        (
        //pointer to memory holding struct
            struct rv_system_object_writelock_s          *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                                    sz,
        //vtble
            struct rv_system_object_base_vtble_s        *vtble,
        //top object
            void                                        *top,
        //memory
            struct rv_system_memory_s                   *mem
        );
        typedef bool (* rv_system_object_writelock_create_super_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_object_writelock_s          *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                                    sz,
        //vtble
            struct rv_system_object_base_vtble_s        *vtble,
        //top object
            void                                        *top,
        //memory
            struct rv_system_memory_s                   *mem
        );

    //rv_system_object_writelock_create() initiates struct in newly allocated memory
        struct rv_system_object_writelock_s *rv_system_object_writelock_create
        (
        //memory
            struct rv_system_memory_s                  *mem,
        //memory lock (optional)
            struct rv_system_memory_lock_s             *mem_lock_optional
        );
        typedef struct rv_system_object_writelock_s *(* rv_system_object_writelock_create_ptr)
        (
        //memory
            struct rv_system_memory_s                  *mem,
        //memory lock (optional)
            struct rv_system_memory_lock_s             *mem_lock_optional
        );

    //rv_system_object_writelock_create_super() initiates struct in newly allocated memory
    //returns top object when successful
        void *rv_system_object_writelock_create_super
        (
        //pointer to receive base
            struct rv_system_object_writelock_s          **pt,
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
        typedef void *(* rv_system_object_writelock_create_super_ptr)
        (
        //pointer to receive base
            struct rv_system_object_writelock_s          **pt,
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

/* -- virtual method corresponding static function stubs --------------------- */

    //init function, returns true if successful
        bool __rv_system_object_writelock_init
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        );

    //deinit function
        void __rv_system_object_writelock_deinit
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        );

    //gen ref function, returns false if fails
        bool __rv_system_object_writelock_gen_ref
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //pointer to receive ref
            struct rv_system_object_ref_s       **pp
        );

    //gen readlock function, returns false if fails
        bool __rv_system_object_writelock_gen_readlock
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //pointer to receive readlock
            struct rv_system_object_readlock_s **pp
        );

    //gen writelock function, returns false if fails
        bool __rv_system_object_writelock_gen_writelock
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //pointer to receive writelock
            struct rv_system_object_writelock_s **pp
        );

    //get pointer to type function, returns false if not available
        bool __rv_system_object_writelock_get_type
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //pointer to receive object of type
            void **pp,
        //string name of type to fetch
            char *ctype
        );

    //get type name function, returns size needed to copy, even if buffer is null or too small
        uint16_t __rv_system_object_writelock_get_type_name
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //buffer to hold name
            char                                *pb,
        //size of buffer
            uint16_t                            szb
        );

    //get all type names function, returns size needed to copy even if buffer is null or too small
        uint16_t __rv_system_object_writelock_get_all_type_names
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //buffer to hold name
            char                                *pb,
        //size to buffer
            uint16_t                            szb
        );

    //get size funcion, returns size of object and all memory owned by object including child objects
        uint64_t __rv_system_object_writelock_get_size
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        );

    //get type function
        char *__rv_system_object_writelock_get_type_value
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        );

    //test type function, returns true if object is of that type
        bool __rv_system_object_writelock_is_type
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //string type name
            char *ctype
        );

/* -------- helper functions to be used by inherited objects to perform work in virtual functions --------------------- */

    //none

/* -------- structures containing easy function pointers --------------------- */

    //contains methods
        struct rv_system_object_writelock_ptr_s
        {
        //object base
            struct rv_system_object_base_ptr_s                     *super;
        //create static
            rv_system_object_writelock_create_static_ptr             create_static;
        //create super static
            rv_system_object_writelock_create_super_static_ptr       create_super_static;
        //create
            rv_system_object_writelock_create_ptr                    create;
        //create super
            rv_system_object_writelock_create_super_ptr              create_super;
        };
        struct rv_system_object_writelock_ptr_s rv_system_object_writelock;

//header guard end
    #endif





