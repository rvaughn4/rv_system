
/* ============================ rv_system_object_writelock.c ===================================== //

    rv_system_object_writelock.c

    handles vtble for objects and ctor and dtor

// ============================ rv_system_object_writelock.c ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_object_SLASH_rv_system_object_writelock_DOT_c
    #define rv_system_SLASH_rv_system_object_SLASH_rv_system_object_writelock_DOT_c

/* ------------------- included headers --------------------------------------- */

    //object
        #include "rv_system_object.h"
    //object
        #include "rv_system_object_readlock.h"
    //object
        #include "rv_system_object_writelock.h"
    //object
        #include "rv_system_object_ref.h"
    //rwl
        #include "../rv_system_rwlock/rv_system_rwlock.h"
        #include "../rv_system_rwlock/rv_system_rwlock_holder.h"

/* ----------- virtual function/method stubs and typedefs -------------------- */

        struct rv_system_object_base_vtble_s rv_system_object_writelock_vtble =
        {
        /*.init=*/                  (__rv_system_object_base_init_ptr)                  __rv_system_object_writelock_init,
        /*.deinit=*/                (__rv_system_object_base_deinit_ptr)                __rv_system_object_writelock_deinit,
        /*.gen_ref=*/               (__rv_system_object_base_gen_ref_ptr)               __rv_system_object_writelock_gen_ref,
        /*.gen_writelock=*/         (__rv_system_object_base_gen_readlock_ptr)          __rv_system_object_writelock_gen_readlock,
        /*.gen_writelock=*/         (__rv_system_object_base_gen_writelock_ptr)         __rv_system_object_writelock_gen_writelock,
        /*.get_type=*/              (__rv_system_object_base_get_type_ptr)              __rv_system_object_writelock_get_type,
        /*.get_type_name=*/         (__rv_system_object_base_get_type_name_ptr)         __rv_system_object_writelock_get_type_name,
        /*.get_all_type_names=*/    (__rv_system_object_base_get_all_type_names_ptr)    __rv_system_object_writelock_get_all_type_names,
        /*.get size=*/              (__rv_system_object_base_get_size_ptr)              __rv_system_object_writelock_get_size,
        /*.get_type_value=*/        (__rv_system_object_base_get_type_value_ptr)        __rv_system_object_writelock_get_type_value,
        /*.is_type=*/               (__rv_system_object_base_is_type_ptr)               __rv_system_object_writelock_is_type,
        /*.link=*/                  (__rv_system_object_base_link_ptr)                  __rv_system_object_writelock_link
        };

/* -------- structures containing easy function pointers --------------------- */

    //contains methods
        struct rv_system_object_writelock_ptr_s rv_system_object_writelock =
        {
        /*.super=*/                 &rv_system_object_base,
        /*.create_static=*/         rv_system_object_writelock_create_static,
        /*.create_super_static*/    rv_system_object_writelock_create_super_static,
        /*.create*/                 rv_system_object_writelock_create,
        /*.create_super*/           rv_system_object_writelock_create_super,
        /*.get_super_offset=*/      rv_system_object_writelock_get_super_offset,
        /*.get_base_offset=*/       rv_system_object_writelock_get_base_offset
        };

/* ------------------- static function definitions --------------------------------- */

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
        )
        {
            return rv_system_object_writelock_create_super_static( t, sz, &rv_system_object_writelock_vtble, (void *)t, mem );
        };


    //rv_system_object_writelock_create_super_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_object_writelock_create_super_static
        (
        //pointer to memory holding struct
            struct rv_system_object_writelock_s                   *t,
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
            if( sz < sizeof(struct rv_system_object_writelock_s) )
                return 0;
        //compute size remaining
            szr = sz - rv_system_object_writelock_get_super_offset();
        //super
            return rv_system_object_base_create_super_static( &t->base, szr, &rv_system_object_writelock_vtble, top, mem );
        };

    //rv_system_object_writelock_create() initiates struct in newly allocated memory
        struct rv_system_object_writelock_s *rv_system_object_writelock_create
        (
        //memory
            struct rv_system_memory_s                  *mem,
        //memory lock (optional)
            struct rv_system_memory_lock_s             *mem_lock_optional
        )
        {
            return (struct rv_system_object_writelock_s *)rv_system_object_writelock_create_super( 0, 0, sizeof( struct rv_system_object_writelock_s ), &rv_system_object_writelock_vtble, mem, mem_lock_optional );
        }

    //rv_system_object_writelock_create_super() initiates struct in newly allocated memory
    //returns top object when successful
        void *rv_system_object_writelock_create_super
        (
        //pointer to receive base
            struct rv_system_object_writelock_s                  **pt,
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
            union
            {
                struct rv_system_object_writelock_s       *o;
                struct rv_system_object_base_s           *b;
            } a;
            void *r;
        //create super
            r = rv_system_object_base_create_super( &a.b, base_offset + 0, sz, vtble, mem, mem_lock_optional );
        //return pointers
            if( pt )
                *pt = a.o;
            return r;
        };

    //rv_system_object_writelock_get_super_offset() returns offset of super
        uint64_t rv_system_object_writelock_get_super_offset
        (
            void
        )
        {
            struct rv_system_object_writelock_s ds;
            union
            {
                struct rv_system_object_writelock_s         *top;
                struct rv_system_object_base_s              *super;
                uint64_t                                    l;
            } a, b;
            a.top = &ds;
            b.super = &ds.base;
            return b.l - a.l;
        }

    //rv_system_object_writelock_get_base_offset() returns offset of base
        uint64_t rv_system_object_writelock_get_base_offset
        (
            void
        )
        {
            struct rv_system_object_writelock_s ds;
            union
            {
                struct rv_system_object_writelock_s         *top;
                struct rv_system_object_base_s              *base;
                uint64_t                                    l;
            } a, b;
            a.top = &ds;
            b.base = &ds.base;
            return b.l - a.l;
        }

/* -- virtual method corresponding static function definitions --------------------- */

    //init function, returns true if successful
        bool __rv_system_object_writelock_init
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        )
        {
            struct rv_system_object_writelock_s *po;
        //init super first
            if( !__rv_system_object_base_init( p_base, top ) )
                return 0;
        //init
            do
            {
                if( !p_base->vtble->get_type( p_base, top, (void **)&po, rv_system_object_type__object_writelock ) )
                    continue;
                po->obj = 0;
            //return success
                return 1;
            }
            while( 0 );
        //fail
            __rv_system_object_base_deinit( p_base, top );
            return 0;
        }

    //deinit function
        void __rv_system_object_writelock_deinit
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        )
        {
            struct rv_system_object_writelock_s *po;
        //deinit this object - nothing todo
            if( p_base->vtble->get_type( p_base, top, (void **)&po, rv_system_object_type__object_writelock ) )
                po->obj = 0;
        //deinit super
            __rv_system_object_base_deinit( p_base, top );
        }

    //gen ref function, returns false if fails
        bool __rv_system_object_writelock_gen_ref
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //pointer to receive ref
            struct rv_system_object_ref_s       **pp
        )
        {
            return rv_system_object_ref_create( p_base->mem, 0 );
        };

    //gen readlock function, returns false if fails
        bool __rv_system_object_writelock_gen_readlock
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //pointer to receive readlock
            struct rv_system_object_readlock_s **pp
        )
        {
            return 0;
        };

    //gen writelock function, returns false if fails
        bool __rv_system_object_writelock_gen_writelock
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //pointer to receive writelock
            struct rv_system_object_writelock_s **pp
        )
        {
            return 0;
        };

    //get pointer to type function, returns false if not available
        bool __rv_system_object_writelock_get_type
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //pointer to receive object of type
            void                                **pp,
        //string name of type to fetch
            char                                *ctype
        )
        {
        //handle super first
            if( __rv_system_object_base_get_type( p_base, top, pp, ctype ) )
                return 1;
        //type match?
            if( ctype == (char *)rv_system_object_type__object_writelock )
            {
                if( pp )
                    *pp = (void *)p_base;
                return 1;
            }
        //failed
            return 0;
        }

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
        )
        {
            return __rv_system_object_base_get_type_name__helper( pb, szb, rv_system_object_type__object_writelock );
        }

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
        )
        {
            return __rv_system_object_base_get_all_type_names__helper( p_base, top, pb, szb, &rv_system_object_base_vtble, top );
        }

    //get size funcion, returns size of object and all memory owned by object including child objects
        uint64_t __rv_system_object_writelock_get_size
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        )
        {
            return sizeof( struct rv_system_object_writelock_s );
        }

    //get type function
        char *__rv_system_object_writelock_get_type_value
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        )
        {
            return rv_system_object_type__object_writelock;
        }

    //test type function, returns true if object is of that type
        bool __rv_system_object_writelock_is_type
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //string type name
            char                                *ctype
        )
        {
        //handle super first
            if( __rv_system_object_base_is_type( p_base, top, ctype ) )
                return 1;
        //test this object
            return ctype == (char *)rv_system_object_type__object_writelock;
        }

    //link object to this object, used for linking refs and locks
        bool __rv_system_object_writelock_link
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to object base to link
            struct rv_system_object_base_s      *p_link,
        //should we block if locking is required?
            bool                                is_blocking,
        //how long should we wait in ms if not blocking before we stop trying to link
            uint64_t                            timeout_ms
        )
        {
            struct rv_system_object_s *o;
            struct rv_system_object_ref_s *r;
            struct rv_system_object_writelock_s *t;
        //get this object
            if( !p_link->vtble->get_type( p_link, p_link->top, (void **)&t, rv_system_object_type__object_writelock ) )
                return 0;
        //convert to object
            if( p_link->vtble->get_type( p_link, p_link->top, (void **)&o, rv_system_object_type__object ) )
            {
                t->obj = o;
                return t->obj != 0;
            }
        //convert to ref and fetch object
            if( p_link->vtble->get_type( p_link, p_link->top, (void **)&r, rv_system_object_type__object_ref ) )
            {
                struct rv_system_rwlock_holder_s rwlh;
            //lock ref
                if( !rv_system_rwlock_holder_create_static( &rwlh, sizeof( rwlh ) ) )
                    return 0;
            //be sure to unlock
                do
                {
                //add
                    if( !rv_system_rwlock_holder_add( &rwlh, &r->rwl, 0 ) )
                        continue;
                //lock
                    if( !rv_system_rwlock_holder_lock( &rwlh, is_blocking, timeout_ms, 1 ) )
                        continue;
                //get object
                    t->obj = r->obj;
                }
                while( 0 );
            //unlock ref
                rv_system_rwlock_holder_destroy_static( &rwlh );
            //return
                return t->obj != 0;
            }
        //failed
            return 0;
        }

/* -------- helper functions to be used by inherited objects to perform work in virtual functions --------------------- */

    //none

//header guard end
    #endif






