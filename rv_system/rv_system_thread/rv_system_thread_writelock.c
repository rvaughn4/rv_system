
/* ============================ rv_system_thread_writelock.c ===================================== //

    rv_system_thread_writelock.c

    writelock for thread, for querying thread stats

// ============================ rv_system_thread_writelock.c ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_thread_SLASH_rv_system_thread_writelock_DOT_c
    #define rv_system_SLASH_rv_system_thread_SLASH_rv_system_thread_writelock_DOT_c

/* ------------------- included headers --------------------------------------- */

    //object
        #include "rv_system_thread.h"
    //object
        #include "rv_system_thread_readlock.h"
    //object
        #include "rv_system_thread_writelock.h"

        char *rv_system_object_type__thread_writelock = "thread_writelock";

/* ----------- virtual function/method stubs and typedefs -------------------- */

        struct rv_system_object_base_vtble_s rv_system_thread_writelock_vtble =
        {
        /*.init=*/                  __rv_system_thread_writelock_init,
        /*.deinit=*/                __rv_system_thread_writelock_deinit,
        /*.gen_ref=*/               __rv_system_object_base_gen_ref,
        /*.gen_readlock=*/          __rv_system_object_base_gen_readlock,
        /*.gen_writelock=*/         __rv_system_object_base_gen_writelock,
        /*.get_type=*/              __rv_system_thread_writelock_get_type,
        /*.get_type_name=*/         __rv_system_thread_writelock_get_type_name,
        /*.get_all_type_names=*/    __rv_system_thread_writelock_get_all_type_names,
        /*.get size=*/              __rv_system_thread_writelock_get_size,
        /*.get_type_value=*/        __rv_system_thread_writelock_get_type_value,
        /*.is_type=*/               __rv_system_thread_writelock_is_type,
        /*.link=*/                  __rv_system_object_writelock_link,
        /*.unlink=*/                __rv_system_object_writelock_unlink,
        /*.get_rwl=*/               __rv_system_object_base_get_rwl,
        /*.get_link=*/              __rv_system_object_writelock_get_link
        };

/* -------- structures containing easy function pointers --------------------- */

    //contains methods
        struct rv_system_thread_writelock_ptr_s rv_system_thread_writelock =
        {
        /*.super=*/                 &rv_system_object_writelock,
        /*.create_static=*/         rv_system_thread_writelock_create_static,
        /*.create_super_static*/    rv_system_thread_writelock_create_super_static,
        /*.create*/                 rv_system_thread_writelock_create,
        /*.create_super*/           rv_system_thread_writelock_create_super,
        /*.get_super_offset=*/      rv_system_thread_writelock_get_super_offset,
        /*.get_base_offset=*/       rv_system_thread_writelock_get_base_offset
        };

/* ------------------- static function definitions --------------------------------- */

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
        )
        {
            return rv_system_thread_writelock_create_super_static( t, sz, &rv_system_thread_writelock_vtble, (void *)t, mem );
        }

    //rv_system_thread_writelock_create_super_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_thread_writelock_create_super_static
        (
        //pointer to memory holding struct
            struct rv_system_thread_writelock_s                   *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                                             sz,
        //vtble
            struct rv_system_object_base_vtble_s                 *vtble,
        //top object
            void                                                 *top,
        //memory
            struct rv_system_memory_s                            *mem
        )
        {
            uint64_t szr;
        //test size
            if( sz < sizeof(struct rv_system_thread_writelock_s) )
                return 0;
        //compute size remaining
            szr = sz - rv_system_thread_writelock_get_base_offset();
        //super
            return rv_system_object_writelock_create_super_static( &t->base, szr, vtble, top, mem );
        }

    //rv_system_thread_writelock_create() initiates struct in newly allocated memory
        struct rv_system_thread_writelock_s *rv_system_thread_writelock_create
        (
        //memory
            struct rv_system_memory_s                  *mem,
        //memory lock (optional)
            struct rv_system_memory_lock_s             *mem_lock_optional
        )
        {
            return (struct rv_system_thread_writelock_s *)rv_system_thread_writelock_create_super( 0, 0, sizeof( struct rv_system_object_writelock_s ), &rv_system_thread_writelock_vtble, mem, mem_lock_optional );
        }

    //rv_system_thread_writelock_create_super() initiates struct in newly allocated memory
    //returns top object when successful
        void *rv_system_thread_writelock_create_super
        (
        //pointer to receive base
            struct rv_system_thread_writelock_s                  **pt,
        //offset to base object
            uint16_t                                            base_offset,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                                            sz,
        //vtble
            struct rv_system_object_base_vtble_s                *vtble,
        //memory
            struct rv_system_memory_s                           *mem,
        //memory lock (optional)
            struct rv_system_memory_lock_s                      *mem_lock_optional
        )
        {
            struct rv_system_object_writelock_s           *b;
            void *r;
        //create super
            r = rv_system_object_writelock_create_super( &b, base_offset + 0, sz, vtble, mem, mem_lock_optional );
        //return pointers
            if( pt )
                b->base.vtble->get_type( &b->base, (void **)pt, rv_system_object_type__thread_writelock );
            return r;
        }

    //rv_system_thread_writelock_get_super_offset() returns offset of super
        uint64_t rv_system_thread_writelock_get_super_offset
        (
            void
        )
        {
            struct rv_system_thread_writelock_s ds;
            union
            {
                struct rv_system_thread_writelock_s          *top;
                struct rv_system_object_writelock_s          *super;
                uint64_t                                    l;
            } a, b;
            a.top = &ds;
            b.super = &ds.base;
            return b.l - a.l;
        }

    //rv_system_thread_writelock_get_base_offset() returns offset of base
        uint64_t rv_system_thread_writelock_get_base_offset
        (
            void
        )
        {
            struct rv_system_thread_writelock_s ds;
            union
            {
                struct rv_system_thread_writelock_s          *top;
                struct rv_system_object_base_s              *base;
                uint64_t                                    l;
            } a, b;
            a.top = &ds;
            b.base = &ds.base.base;
            return b.l - a.l;
        }

/* -- virtual method corresponding static function definitions --------------------- */

    //init function, returns true if successful
        bool __rv_system_thread_writelock_init
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        )
        {
            struct rv_system_thread_writelock_s *po;
        //init super first
            if( !__rv_system_object_writelock_init( p_base, top ) )
                return 0;
        //init
            do
            {
            //valid type
                if( !p_base->vtble->get_type( p_base, (void **)&po, rv_system_object_type__thread_writelock ) )
                    continue;
            //return
                return 1;
            }
            while( 0 );
        //failure
            __rv_system_object_writelock_deinit( p_base );
            return 0;
        }

    //deinit function
        void __rv_system_thread_writelock_deinit
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base
        )
        {
        //deinit super
            __rv_system_object_writelock_deinit( p_base );
        }

    //get pointer to type function, returns false if not available
        bool __rv_system_thread_writelock_get_type
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to receive object of type
            void                                **pp,
        //string name of type to fetch
            char                                *ctype
        )
        {
        //handle super first
            if( __rv_system_object_writelock_get_type( p_base, pp, ctype ) )
                return 1;
        //type match?
            if( ctype == (char *)rv_system_object_type__thread_writelock )
            {
                if( pp )
                    *pp = (void *)p_base;
                return 1;
            }
        //failed
            return 0;
        }

    //get type name function, returns size needed to copy, even if buffer is null or too small
        uint16_t __rv_system_thread_writelock_get_type_name
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //buffer to hold name
            char                                *pb,
        //size of buffer
            uint16_t                            szb
        )
        {
            (void)p_base;
            return __rv_system_object_base_get_type_name__helper( pb, szb, rv_system_object_type__thread_writelock );
        }

    //get all type names function, returns size needed to copy even if buffer is null or too small
        uint16_t __rv_system_thread_writelock_get_all_type_names
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //buffer to hold name
            char                                *pb,
        //size to buffer
            uint16_t                            szb
        )
        {
            return __rv_system_object_base_get_all_type_names__helper( p_base, pb, szb, &rv_system_object_writelock_vtble );
        }

    //get size funcion, returns size of object and all memory owned by object including child objects
        uint64_t __rv_system_thread_writelock_get_size
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base
        )
        {
            (void)p_base;
            return sizeof( struct rv_system_thread_writelock_s );
        }

    //get type function
        char *__rv_system_thread_writelock_get_type_value
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base
        )
        {
            (void)p_base;
            return rv_system_object_type__thread_writelock;
        }

    //test type function, returns true if object is of that type
        bool __rv_system_thread_writelock_is_type
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //string type name
            char                                *ctype
        )
        {
        //handle super first
            if( __rv_system_object_writelock_is_type( p_base, ctype ) )
                return 1;
        //test this object
            return ctype == (char *)rv_system_object_type__thread_writelock;
        }

/* -------- helper functions to be used by inherited objects to perform work in virtual functions --------------------- */

    //none

//header guard end
    #endif





