
/* ============================ rv_system_object.c ===================================== //

    rv_system_object.c

    handles vtble for objects and ctor and dtor

// ============================ rv_system_object.c ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_object_SLASH_rv_system_object_DOT_c
    #define rv_system_SLASH_rv_system_object_SLASH_rv_system_object_DOT_c

/* ------------------- included headers --------------------------------------- */

    //object
        #include "rv_system_object.h"
    //object
        #include "rv_system_object_readlock.h"
    //object
        #include "rv_system_object_writelock.h"
    //object
        #include "rv_system_object_ref.h"
    //memory
        #include "../rv_system_memory/rv_system_memory.h"
        #include "../rv_system_memory/rv_system_memory_lock.h"
    //rwl
        #include "../rv_system_rwlock/rv_system_rwlock.h"
        #include "../rv_system_rwlock/rv_system_rwlock_holder.h"

        char *rv_system_object_type__object = "rv_system_object_type__object";

/* ----------- virtual function/method stubs and typedefs -------------------- */

        struct rv_system_object_base_vtble_s rv_system_object_vtble =
        {
        /*.init=*/                  __rv_system_object_init,
        /*.deinit=*/                __rv_system_object_deinit,
        /*.gen_ref=*/               __rv_system_object_gen_ref,
        /*.gen_readlock=*/          __rv_system_object_gen_readlock,
        /*.gen_writelock=*/         __rv_system_object_gen_writelock,
        /*.get_type=*/              __rv_system_object_get_type,
        /*.get_type_name=*/         __rv_system_object_get_type_name,
        /*.get_all_type_names=*/    __rv_system_object_get_all_type_names,
        /*.get size=*/              __rv_system_object_get_size,
        /*.get_type_value=*/        __rv_system_object_get_type_value,
        /*.is_type=*/               __rv_system_object_is_type,
        /*.link=*/                  __rv_system_object_link,
        /*.unlink=*/                __rv_system_object_unlink,
        /*.get_rwl=*/               __rv_system_object_get_rwl
        };

/* -------- structures containing easy function pointers --------------------- */

    //contains methods
        struct rv_system_object_ptr_s rv_system_object =
        {
        /*.super=*/                 &rv_system_object_base,
        /*.create_static=*/         rv_system_object_create_static,
        /*.create_super_static*/    rv_system_object_create_super_static,
        /*.create*/                 rv_system_object_create,
        /*.create_super*/           rv_system_object_create_super,
        /*.get_super_offset=*/      rv_system_object_get_super_offset,
        /*.get_base_offset=*/       rv_system_object_get_base_offset
        };

/* ------------------- static function definitions --------------------------------- */

    //rv_system_object_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_object_create_static
        (
        //pointer to memory holding struct
            struct rv_system_object_s          *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                            sz,
        //memory
            struct rv_system_memory_s           *mem
        )
        {
            return rv_system_object_create_super_static( t, sz, &rv_system_object_vtble, (void *)t, mem );
        };


    //rv_system_object_create_super_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_object_create_super_static
        (
        //pointer to memory holding struct
            struct rv_system_object_s                   *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                                    sz,
        //vtble
            struct rv_system_object_base_vtble_s        *vtble,
        //top object
            void                                        *top,
        //memory
            struct rv_system_memory_s                   *mem
        )
        {
            uint64_t szr;
        //test size
            if( sz < sizeof(struct rv_system_object_s) )
                return 0;
        //compute size remaining
            szr = sz - rv_system_object_get_super_offset();
        //super
            return rv_system_object_base_create_super_static( &t->base, szr, &rv_system_object_vtble, top, mem );
        };

    //rv_system_object_create() initiates struct in newly allocated memory
        struct rv_system_object_s *rv_system_object_create
        (
        //memory
            struct rv_system_memory_s                  *mem,
        //memory lock (optional)
            struct rv_system_memory_lock_s             *mem_lock_optional
        )
        {
            return (struct rv_system_object_s *)rv_system_object_create_super( 0, 0, sizeof( struct rv_system_object_s ), &rv_system_object_vtble, mem, mem_lock_optional );
        }

    //rv_system_object_create_super() initiates struct in newly allocated memory
    //returns top object when successful
        void *rv_system_object_create_super
        (
        //pointer to receive base
            struct rv_system_object_s                  **pt,
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
        )
        {
            struct rv_system_object_base_s  *b;
            void *r;
        //create super
            r = rv_system_object_base_create_super( &b, base_offset + 0, sz, vtble, mem, mem_lock_optional );
        //return pointers
            if( pt )
                b->vtble->get_type( b, (void **)pt, rv_system_object_type__object );
            return r;
        };

    //rv_system_object_get_super_offset() returns offset of super
        uint64_t rv_system_object_get_super_offset
        (
            void
        )
        {
            struct rv_system_object_s ds;
            union
            {
                struct rv_system_object_s           *top;
                struct rv_system_object_base_s      *super;
                uint64_t                            l;
            } a, b;
            a.top = &ds;
            b.super = &ds.base;
            return b.l - a.l;
        }

    //rv_system_object_get_base_offset() returns offset of base
        uint64_t rv_system_object_get_base_offset
        (
            void
        )
        {
            struct rv_system_object_s ds;
            union
            {
                struct rv_system_object_s           *top;
                struct rv_system_object_base_s      *base;
                uint64_t                            l;
            } a, b;
            a.top = &ds;
            b.base = &ds.base;
            return b.l - a.l;
        }

/* -- virtual method corresponding static function definitions --------------------- */

    //init function, returns true if successful
        bool __rv_system_object_init
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        )
        {
            struct rv_system_object_s *po;
        //init super first
            if( !__rv_system_object_base_init( p_base, top ) )
                return 0;
        //fail loop
            do
            {
            //get obj
                if( !p_base->vtble->get_type( p_base, (void **)&po, rv_system_object_type__object ) )
                    continue;
            //init ref list
                __rv_system_object_reset_ref_list( po );
            //init rwlock
                if( !rv_system_rwlock_create_static( &po->rwl, sizeof( po->rwl ) ) )
                    continue;
            //init rwlock
                if( !rv_system_rwlock_create_static( &po->ref_lk, sizeof( po->ref_lk ) ) )
                {
                    rv_system_rwlock_destroy_static( &po->rwl );
                    continue;
                }
            //return success
                return 1;
            }
            while( 0 );
        //deinit
            __rv_system_object_base_deinit( p_base );
        //return failure
            return 0;
        }

    //deinit function
        void __rv_system_object_deinit
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base
        )
        {
            struct rv_system_object_s *po;
        //get type
            if( p_base->vtble->get_type( p_base, (void **)&po, rv_system_object_type__object ) )
            {
            //unlink refs and release list
                __rv_system_object_unlink_all( po );
            //destroy lock
                rv_system_rwlock_destroy_static( &po->rwl );
            //destroy lock
                rv_system_rwlock_destroy_static( &po->ref_lk );
            //unlink refs and release list
                __rv_system_object_destroy_ref_list( po );
            }
        //deinit super
            __rv_system_object_base_deinit( p_base );
        }

    //gen ref function, returns false if fails
        bool __rv_system_object_gen_ref
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to receive ref
            struct rv_system_object_ref_s       **pp
        )
        {
            struct rv_system_object_ref_s *r;
            r = rv_system_object_ref_create( p_base->mem, 0 );
            if( pp )
                *pp = r;
            return r != 0;
        };

    //gen readlock function, returns false if fails
        bool __rv_system_object_gen_readlock
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to receive readlock
            struct rv_system_object_readlock_s **pp
        )
        {
            return rv_system_object_readlock_create( p_base->mem, 0 );
        };

    //gen writelock function, returns false if fails
        bool __rv_system_object_gen_writelock
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to receive writelock
            struct rv_system_object_writelock_s **pp
        )
        {
            return rv_system_object_writelock_create( p_base->mem, 0 );
        };

    //get pointer to type function, returns false if not available
        bool __rv_system_object_get_type
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
            if( __rv_system_object_base_get_type( p_base, pp, ctype ) )
                return 1;
        //type match?
            if( ctype == (char *)rv_system_object_type__object )
            {
                if( pp )
                    *pp = (void *)p_base;
                return 1;
            }
        //failed
            return 0;
        }

    //get type name function, returns size needed to copy, even if buffer is null or too small
        uint16_t __rv_system_object_get_type_name
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //buffer to hold name
            char                                *pb,
        //size of buffer
            uint16_t                            szb
        )
        {
            return __rv_system_object_base_get_type_name__helper( pb, szb, rv_system_object_type__object );
        }

    //get all type names function, returns size needed to copy even if buffer is null or too small
        uint16_t __rv_system_object_get_all_type_names
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //buffer to hold name
            char                                *pb,
        //size to buffer
            uint16_t                            szb
        )
        {
            return __rv_system_object_base_get_all_type_names__helper( p_base, pb, szb, &rv_system_object_base_vtble );
        }

    //get size funcion, returns size of object and all memory owned by object including child objects
        uint64_t __rv_system_object_get_size
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base
        )
        {
            return sizeof( struct rv_system_object_s );
        }

    //get type function
        char *__rv_system_object_get_type_value
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base
        )
        {
            return rv_system_object_type__object;
        }

    //test type function, returns true if object is of that type
        bool __rv_system_object_is_type
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //string type name
            char                                *ctype
        )
        {
        //handle super first
            if( __rv_system_object_base_is_type( p_base, ctype ) )
                return 1;
        //test this object
            return ctype == (char *)rv_system_object_type__object;
        }

    //link object to this object, used for linking refs and locks
        bool __rv_system_object_link
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
            struct rv_system_rwlock_holder_s lh;
            struct rv_system_object_s *t;
            bool s = 0;
        //get object
            if( !p_base->vtble->get_type( p_base, (void **)&t, rv_system_object_type__object ) )
                return 0;
        //init lock
            if( !rv_system_rwlock_holder_create_static( &lh, sizeof( lh ) ) )
                return 0;
        //lock guard loop
            do
            {
            //attempt to lock
                if( !rv_system_rwlock_holder_add( &lh, &t->ref_lk, 1 ) )
                    continue;
                if( !rv_system_rwlock_holder_lock( &lh, is_blocking, timeout_ms, 1 ) )
                    continue;
            //make sure not already linked
                if( __rv_system_object_on_ref_list( t, p_link ) )
                {
                    s = 1;
                    continue;
                }
            //attempt to add without resize
                if( __rv_system_object_add_ref_list( t, p_link ) )
                {
                    s = 1;
                    continue;
                }
            //failed? attempt resize
                if( !__rv_system_object_resize_ref_list( t ) )
                    continue;
            //attempt to add again
                if( __rv_system_object_add_ref_list( t, p_link ) )
                    s = 1;
            }
            while( 0 );
        //release lock
            rv_system_rwlock_holder_destroy_static( &lh );
        //link
            if( s && p_link )
                p_link->vtble->link( p_link, p_base, is_blocking, timeout_ms );
        //return status
            return s;
        }

    //unlink object to this object
        bool __rv_system_object_unlink
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
            struct rv_system_rwlock_holder_s lh;
            struct rv_system_object_s *t;
            bool s = 0;
        //get object
            if( !p_base->vtble->get_type( p_base, (void **)&t, rv_system_object_type__object ) )
                return 0;
        //init lock
            if( !rv_system_rwlock_holder_create_static( &lh, sizeof( lh ) ) )
                return 0;
        //lock guard loop
            do
            {
            //attempt to lock
                if( !rv_system_rwlock_holder_add( &lh, &t->ref_lk, 1 ) )
                    continue;
                if( !rv_system_rwlock_holder_lock( &lh, is_blocking, timeout_ms, 1 ) )
                    continue;
            //attempt to add again
                if( __rv_system_object_remove_ref_list( t, p_link ) )
                    s = 1;
            }
            while( 0 );
        //release lock
            rv_system_rwlock_holder_destroy_static( &lh );
        //unlink
            if( s && p_link )
                p_link->vtble->unlink( p_link, p_base, is_blocking, timeout_ms );
        //return status
            return s;
        }

    //returns pointer to rwl for object
        struct rv_system_rwlock_s *__rv_system_object_get_rwl
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base
        )
        {
            struct rv_system_object_s *t;
        //get object
            if( !p_base->vtble->get_type( p_base, (void **)&t, rv_system_object_type__object ) )
                return 0;
        //return rwl
            return &t->rwl;
        };

/* -------- helper functions  --------------------- */

    //reset/init original ref list
        void __rv_system_object_reset_ref_list
        (
            struct rv_system_object_s   *t
        )
        {
            uint32_t i;
        //default list size
            t->cnt_refs = rv_system_object__refs_max;
            t->refs = &t->first_refs[ 0 ];
        //zero it
            for( i = 0; i < t->cnt_refs; i++ )
                t->refs[ i ] = 0;
        };

    //destroy ref list
        void __rv_system_object_destroy_ref_list
        (
            struct rv_system_object_s   *t
        )
        {
        //unlink all
            __rv_system_object_unlink_all( t );
        //release memory
            if( t->refs != &t->first_refs[ 0 ] && t->base.mem )
            {
                struct rv_system_memory_lock_s ml;
                if( rv_system_memory_lock_create_static( &ml, sizeof( ml ) ) )
                {
                    if( rv_system_memory_lock_lock( &ml, t->base.mem ) )
                        rv_system_memory_lock_release( &ml, (void *)t->refs );
                    rv_system_memory_lock_destroy_static( &ml );
                }
            }
        //reset
            __rv_system_object_reset_ref_list( t );
        };

    //unlink all refs on list
        void __rv_system_object_unlink_all
        (
            struct rv_system_object_s   *t
        )
        {
            uint32_t i;
            struct rv_system_object_base_s *r;
        //unlink all
            for( i = 0; i < t->cnt_refs; i++ )
            {
                r = t->refs[ i ];
            //skip nulls
                if( !r )
                    continue;
            //remove to avoid recursive unlink trap
                t->refs[ i ] = 0;
            //unlink
                r->vtble->unlink( r, &t->base, 1, 0 );
            }
        };

    //resize ref list
        bool __rv_system_object_resize_ref_list
        (
            struct rv_system_object_s   *t
        )
        {
            struct rv_system_object_base_s **np, **op;
            uint16_t nsz, osz;
            struct rv_system_memory_lock_s ml;
            uint32_t i;
            bool r = 0;
        //memory allocator?
            if( !t->base.mem )
                return 0;
        //create lock
            if( !rv_system_memory_lock_create_static( &ml, sizeof( ml ) ) )
                return 0;
        //lock keeper loop
            do
            {
            //lock memory
                if( !rv_system_memory_lock_lock( &ml, t->base.mem ) )
                    continue;
            //copy old
                op = t->refs;
                osz = t->cnt_refs;
            //compute new size
                nsz = osz * 2;
                if( nsz < 13 )
                    nsz = 13;
            //create new buffer
                if( !rv_system_memory_lock_allocate( &ml, nsz * sizeof( struct rv_system_object_base_s * ), (void **)&np ) )
                    continue;
            //copy old into new
                for( i = 0; i < nsz; i++ )
                {
                    if( i < osz )
                        np[ i ] = op[ i ];
                    else
                        np[ i ] = 0;
                }
                t->refs = np;
                t->cnt_refs = nsz;
                r = 1;
            //release old buffer
                if( op != &t->first_refs[ 0 ] )
                    rv_system_memory_lock_release( &ml, (void *)op );
            }
            while( 0 );
        //release lock
            rv_system_memory_lock_destroy_static( &ml );
        //return result
            return r;
        };

    //add ref to list
        bool __rv_system_object_add_ref_list
        (
            struct rv_system_object_s       *t,
        //ref
            struct rv_system_object_base_s  *r
        )
        {
            uint32_t i;
        //find null
            for( i = 0; i < t->cnt_refs; i++ )
            {
            //skip
                if( t->refs[ i ] )
                    continue;
            //set
                t->refs[ i ] = r;
            //return success
                return 1;
            }
        //return fail
            return 0;
        };

    //remove ref to list
        bool __rv_system_object_remove_ref_list
        (
            struct rv_system_object_s       *t,
        //ref
            struct rv_system_object_base_s  *r
        )
        {
            uint32_t i;
        //find value
            for( i = 0; i < t->cnt_refs; i++ )
            {
            //skip
                if( t->refs[ i ] != r )
                    continue;
            //set
                t->refs[ i ] = 0;
            //return success
                return 1;
            }
        //return fail
            return 0;
        };

    //add ref to list
        bool __rv_system_object_on_ref_list
        (
            struct rv_system_object_s       *t,
        //ref
            struct rv_system_object_base_s  *r
        )
        {
            uint32_t i;
        //find null
            for( i = 0; i < t->cnt_refs; i++ )
            {
            //skip
                if( t->refs[ i ] != r )
                    continue;
            //return success
                return 1;
            }
        //return fail
            return 0;
        };

/* -------- helper functions to be used by inherited objects to perform work in virtual functions --------------------- */

    //none

//header guard end
    #endif




