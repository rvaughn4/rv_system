
/* ============================ rv_system_object_base.h ===================================== //

    rv_system_object_base.h

    handles vtble for objects and ctor and dtor

// ============================ rv_system_object_base.h ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_object_SLASH_rv_system_object_base_DOT_h
    #define rv_system_SLASH_rv_system_object_SLASH_rv_system_object_base_DOT_h

/* ------------------- included headers --------------------------------------- */

    //standard int size types
        #include <stdint.h>
    //standard boolean type
        #include <stdbool.h>

/* ------------------- structure stubs --------------------------------------- */

    //object base
        struct rv_system_object_base_s;
    //object
        struct rv_system_object_s;
    //object read lock
        struct rv_system_object_readlock_s;
    //object write lock
        struct rv_system_object_writelock_s;
    //object ref
        struct rv_system_object_ref_s;
    //object ref readlock
        struct rv_system_object_ref_readlock_s;
    //object ref writelock
        struct rv_system_object_ref_writelock_s;
    //vtble
        struct rv_system_object_base_vtble_s;
    //memory
        struct rv_system_memory_s;
    //memory lock
        struct rv_system_memory_lock_s;

    #define rv_system_object_type__object_base "rv_system_object_type__object_base"

/* ----------- virtual function/method stubs and typedefs -------------------- */

    //init function, returns true if successful
        typedef bool (* __rv_system_object_base_init_ptr)
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        );

    //deinit function
        typedef void (* __rv_system_object_base_deinit_ptr)
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        );

    //gen ref function, returns false if fails
        typedef bool (* __rv_system_object_base_gen_ref_ptr)
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //pointer to receive ref
            struct rv_system_object_ref_s       **pp
        );

    //gen readlock function, returns false if fails
        typedef bool (* __rv_system_object_base_gen_readlock_ptr)
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //pointer to receive readlock
            struct rv_system_object_readlock_s **pp
        );

    //gen writelock function, returns false if fails
        typedef bool (* __rv_system_object_base_gen_writelock_ptr)
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //pointer to receive writelock
            struct rv_system_object_writelock_s **pp
        );

    //get pointer to type function, returns false if not available
        typedef bool (* __rv_system_object_base_get_type_ptr)
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
        typedef uint16_t (* __rv_system_object_base_get_type_name_ptr)
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
        typedef uint16_t (* __rv_system_object_base_get_all_type_names_ptr)
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
        typedef uint64_t (* __rv_system_object_base_get_size_ptr)
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        );

    //get type function
        typedef char *(* __rv_system_object_base_get_type_value_ptr)
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        );

    //test type function, returns true if object is of that type
        typedef bool (* __rv_system_object_base_is_type_ptr)
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //string type name
            char *ctype
        );

    //link object to this object, used for linking refs and locks
        typedef bool (* __rv_system_object_base_link_ptr)
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to object base to link
            struct rv_system_object_base_s      *p_link,
        //should we block if locking is required?
            bool                                is_blocking,
        //how long should we wait in ms if not blocking before we stop trying to link
            uint64_t                            timeout_ms
        );

    //vtble
        struct rv_system_object_base_vtble_s
        {
        //init
            __rv_system_object_base_init_ptr                  init;
        //deinit
            __rv_system_object_base_deinit_ptr                deinit;
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
        //link
            __rv_system_object_base_link_ptr                  link;
        };
        struct rv_system_object_base_vtble_s rv_system_object_base_vtble;

/* ------------------- structure definition ---------------------------------- */

    //object base
        struct rv_system_object_base_s
        {
        //memory
            struct rv_system_memory_s              *mem;
        //vtble
            struct rv_system_object_base_vtble_s   *vtble;
        //object pointer
            void                                   *top;
        //was allocated dynamically by create function
            bool                                    is_dynamic;
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
            struct rv_system_memory_s           *mem
        );
        typedef bool (* rv_system_object_base_create_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                            sz,
        //memory
            struct rv_system_memory_s           *mem
        );

    //rv_system_object_base_create_super_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_object_base_create_super_static
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s              *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                                    sz,
        //vtble
            struct rv_system_object_base_vtble_s        *vtble,
        //top object
            void                                        *top,
        //memory
            struct rv_system_memory_s                   *mem
        );
        typedef bool (* rv_system_object_base_create_super_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s              *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                                    sz,
        //vtble
            struct rv_system_object_base_vtble_s        *vtble,
        //top object
            void                                        *top,
        //memory
            struct rv_system_memory_s                   *mem
        );

    //rv_system_object_base_create() initiates struct in newly allocated memory
        struct rv_system_object_base_s *rv_system_object_base_create
        (
        //memory
            struct rv_system_memory_s                  *mem,
        //memory lock (optional)
            struct rv_system_memory_lock_s             *mem_lock_optional
        );
        typedef struct rv_system_object_base_s *(* rv_system_object_base_create_ptr)
        (
        //memory
            struct rv_system_memory_s                  *mem,
        //memory lock (optional)
            struct rv_system_memory_lock_s             *mem_lock_optional
        );

    //rv_system_object_base_create_super() initiates struct in newly allocated memory
    //returns top object when successful
        void *rv_system_object_base_create_super
        (
        //pointer to receive base
            struct rv_system_object_base_s              **pt,
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
        typedef void *(* rv_system_object_base_create_super_ptr)
        (
        //pointer to receive base
            struct rv_system_object_base_s              **pt,
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
            void                                **pp,
        //type to get
            char                                *ctype
        );
        typedef bool (* rv_system_object_base_get_type_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t,
        //pointer to receive object of type
            void                                **pp,
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
        bool __rv_system_object_base_init
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        );

    //deinit function
        void __rv_system_object_base_deinit
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        );

    //gen ref function, returns false if fails
        bool __rv_system_object_base_gen_ref
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //pointer to receive ref
            struct rv_system_object_ref_s       **pp
        );

    //gen readlock function, returns false if fails
        bool __rv_system_object_base_gen_readlock
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //pointer to receive readlock
            struct rv_system_object_readlock_s **pp
        );

    //gen writelock function, returns false if fails
        bool __rv_system_object_base_gen_writelock
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //pointer to receive writelock
            struct rv_system_object_writelock_s **pp
        );

    //get pointer to type function, returns false if not available
        bool __rv_system_object_base_get_type
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
        uint16_t __rv_system_object_base_get_type_name
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
        uint16_t __rv_system_object_base_get_all_type_names
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
        uint64_t __rv_system_object_base_get_size
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        );

    //get type function
        char *__rv_system_object_base_get_type_value
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        );

    //test type function, returns true if object is of that type
        bool __rv_system_object_base_is_type
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //string type name
            char *ctype
        );

    //link object to this object, used for linking refs and locks
        bool __rv_system_object_base_link
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to object base to link
            struct rv_system_object_base_s      *p_link,
        //should we block if locking is required?
            bool                                is_blocking,
        //how long should we wait in ms if not blocking before we stop trying to link
            uint64_t                            timeout_ms
        );

/* -------- helper functions to be used by inherited objects to perform work in virtual functions --------------------- */

    //helper function that actually does work behind get_type_name function
        uint16_t __rv_system_object_base_get_type_name__helper
        (
        //buffer to hold name
            char                                *pb,
        //size of buffer
            uint16_t                            szb,
        //type name actual
            char                                *ctype
        );

    //helper function that does work behind get_all_type_names()
        uint16_t __rv_system_object_base_get_all_type_names__helper
        (
        //pointer to object base
            struct rv_system_object_base_s          *p_base,
        //pointer to top level object, inherits base object
            void                                    *top,
        //buffer to hold name
            char                                    *pb,
        //size to buffer
            uint16_t                                szb,
        //parent vtble
            struct rv_system_object_base_vtble_s    *next_vtble,
        //parent object pointer
            void                                    *next_object
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


