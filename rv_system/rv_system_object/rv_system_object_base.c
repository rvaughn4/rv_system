
/* ============================ rv_system_object_base.c ===================================== //

    rv_system_object_base.h

    handles vtble for objects and ctor and dtor

// ============================ rv_system_object_base.c ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_object_SLASH_rv_system_object_base_DOT_c
    #define rv_system_SLASH_rv_system_object_SLASH_rv_system_object_base_DOT_c

/* ------------------- included headers --------------------------------------- */

    //headers
        #include "rv_system_object.h"
        #include "rv_system_object_base.h"
        #include "rv_system_object_readlock.h"
        #include "rv_system_object_writelock.h"
        #include "rv_system_object_ref.h"
    //memory
        #include "../rv_system_memory/rv_system_memory.h"
        #include "../rv_system_memory/rv_system_memory_lock.h"

/* ----------- virtual function/method stubs and typedefs -------------------- */

    //vtble
        struct rv_system_object_base_vtble_s rv_system_object_base_vtble =
        {
        /*.init=*/      (__rv_system_object_base_init_ptr)      __rv_system_object_base_init,
        /*.deinit=*/    (__rv_system_object_base_deinit_ptr)    __rv_system_object_base_deinit,
        //gen ref
            __rv_system_object_base_gen_ref_ptr               gen_ref;
        //gen readlock
            __rv_system_object_base_gen_readlock_ptr          gen_readlock;
        //gen_writelock
            __rv_system_object_base_gen_writelock_ptr         gen_writelock;
        //get type
            __rv_system_object_base_get_type_ptr              get_type;
        //get type name
            __rv_system_object_base_get_type_name_ptr         get_type_name;
        //get all type names
            __rv_system_object_base_get_all_type_names_ptr    get_all_type_names;
        //get size
            __rv_system_object_base_get_size_ptr              get_size;
        //get type value
            __rv_system_object_base_get_type_value_ptr        get_type_value;
        //is type
            __rv_system_object_base_is_type_ptr               is_type;
        };

/* ------------------- structure definition ---------------------------------- */

    //object base
        struct rv_system_object_base_s
        {
        //memory
            rv_system_memory_s              *mem;
        //vtble
            rv_system_object_base_vtble_s   *vtble;
        //object pointer
            void                            *top;
        };

/* ------------------- static function stubs --------------------------------- */

    //rv_system_object_base_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_object_base_create_static
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                            sz,
        //memory
            rv_system_memory_s                  *mem
        );
        typedef bool (* rv_system_object_base_create_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                            sz,
        //memory
            rv_system_memory_s                  *mem
        );

    //rv_system_object_base_create_super_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_object_base_create_super_static
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                            sz,
        //vtble
            rv_system_object_base_vtble_s       *vtble,
        //top object
            void                                *top,
        //memory
            rv_system_memory_s                  *mem
        );
        typedef bool (* rv_system_object_base_create_super_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                            sz,
        //vtble
            rv_system_object_base_vtble_s       *vtble,
        //top object
            void                                *top,
        //memory
            rv_system_memory_s                  *mem
        );

    //rv_system_object_base_create() initiates struct in newly allocated memory
    //returns true when successful
        bool rv_system_object_base_create
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                            sz,
        //memory
            rv_system_memory_s                  *mem,
        //memory lock (optional)
            rv_system_memory_lock_s             *mem_lock_optional
        );
        typedef bool (* rv_system_object_base_create_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                            sz,
        //memory
            rv_system_memory_s                  *mem,
        //memory lock (optional)
            rv_system_memory_lock_s             *mem_lock_optional
        );

    //rv_system_object_base_create_super() initiates struct in newly allocated memory
    //returns true when successful
        bool rv_system_object_base_create_super
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                            sz,
        //vtble
            rv_system_object_base_vtble_s       *vtble,
        //top object
            void                                *top,
        //memory
            rv_system_memory_s                  *mem,
        //memory lock (optional)
            rv_system_memory_lock_s             *mem_lock_optional
        );
        typedef bool (* rv_system_object_base_create_super_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                            sz,
        //vtble
            rv_system_object_base_vtble_s       *vtble,
        //top object
            void                                *top,
        //memory
            rv_system_memory_s                  *mem,
        //memory lock (optional)
            rv_system_memory_lock_s             *mem_lock_optional
        );

    //rv_system_object_base_destroy() releases resources in struct, releases struct memory if was allocated dynamically
        void rv_system_object_base_destroy
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t
        );
        typedef void (* rv_system_object_base_destroy_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t
        );

    //rv_system_object_base_get_type() gets a pointer to the type specified if available for this object
    //          returns true if type is available
        bool rv_system_object_base_get_type
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t,
        //pointer to receive object of type
            void                                **pp;
        //type to get
            char                                *ctype
        );
        typedef bool (* rv_system_object_base_get_type_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t,
        //pointer to receive object of type
            void                                **pp;
        //type to get
            char                                *ctype
        );

    //rv_system_object_base_get_type_name() copies name of type into buffer
    //          returns sized needed even if buffer is null or too small
        uint16_t rv_system_object_base_get_type_name
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t,
        //pointer to buffer
            void                                *buff,
        //size of buffer
            uint16_t                            buff_size
        );
        typedef uint16_t (* rv_system_object_base_get_type_name_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t,
        //pointer to buffer
            void                                *buff,
        //size of buffer
            uint16_t                            buff_size
        );

    //rv_system_object_base_get_all_type_names() copies name of all types in this object into buffer
    //          returns sized needed even if buffer is null or too small
        uint16_t rv_system_object_base_get_all_type_names
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t,
        //pointer to buffer
            void                                *buff,
        //size of buffer
            uint16_t                            buff_size
        );
        typedef uint16_t (* rv_system_object_base_get_all_type_names_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t,
        //pointer to buffer
            void                                *buff,
        //size of buffer
            uint16_t                            buff_size
        );

    //rv_system_object_base_get_size() returns size of this object and all memory used by this object including memory not contained within this object (child objects etc)
        uint64_t rv_system_object_base_get_size
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t
        );
        typedef uint64_t (* rv_system_object_base_get_size_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t
        );

    //rv_system_object_base_get_type_value() returns string for type name
        char *rv_system_object_base_get_type_value
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t
        );
        typedef char *(* rv_system_object_base_get_type_value_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t
        );

    //rv_system_object_base_is_type() returns true if type is found in object
        bool rv_system_object_base_is_type
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t,
        //type
            char                                *ctype
        );
        typedef bool (* rv_system_object_base_is_type_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t,
        //type
            char                                *ctype
        );

/* -- virtual method corresponding static function stubs --------------------- */

    //init function, returns true if successful
        typedef bool (* __rv_system_object_base_init)
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        );

    //deinit function
        typedef void (* __rv_system_object_base_deinit)
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        );

    //gen ref function, returns false if fails
        typedef bool (* __rv_system_object_base_gen_ref)
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //pointer to receive ref
            struct rv_system_object_ref_s       **pp
        );

    //gen readlock function, returns false if fails
        typedef bool (* __rv_system_object_base_gen_readlock)
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //pointer to receive readlock
            struct rv_system_object_readlock_s **pp
        );

    //gen writelock function, returns false if fails
        typedef bool (* __rv_system_object_base_gen_writelock)
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //pointer to receive writelock
            struct rv_system_object_writelock_s **pp
        );

    //get pointer to type function, returns false if not available
        typedef bool (* __rv_system_object_base_get_type)
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
        typedef uint16_t (* __rv_system_object_base_get_type_name)
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
        typedef uint16_t (* __rv_system_object_base_get_all_type_names)
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
        typedef uint64_t (* __rv_system_object_base_get_size)
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        );

    //get type function
        typedef char *(* __rv_system_object_base_get_type_value)
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        );

    //test type function, returns true if object is of that type
        typedef bool (* __rv_system_object_base_is_type)
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //string type name
            char *ctype
        );

/* -------- structures containing easy function pointers --------------------- */

    //contains methods
        struct rv_system_object_base_ptr_s
        {
        //create static
            rv_system_object_base_create_static_ptr             create_static;
        //create super static
            rv_system_object_base_create_super_static_ptr       create_super_static;
        //create
            rv_system_object_base_create_ptr                    create;
        //create super
            rv_system_object_base_create_super_ptr              create_super;
        //destroy
            rv_system_object_base_destroy_ptr                   destroy;
        //get type
            rv_system_object_base_get_type_ptr                  get_type;
        //get type name
            rv_system_object_base_get_type_name_ptr             get_type_name;
        //get all type names
            rv_system_object_base_get_all_type_names_ptr        get_all_type_names;
        //get size
            rv_system_object_base_get_size_ptr                  get_size;
        //get type value
            rv_system_object_base_get_type_value_ptr            get_type_value;
        //is type
            rv_system_object_base_is_type_ptr                   is_type;
        };
        struct rv_system_object_base_ptr_s rv_system_object_base;

//header guard end
    #endif



