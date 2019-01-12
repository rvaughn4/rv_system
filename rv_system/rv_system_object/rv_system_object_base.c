
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
        /*.init=*/                  (__rv_system_object_base_init_ptr)                  __rv_system_object_base_init,
        /*.deinit=*/                (__rv_system_object_base_deinit_ptr)                __rv_system_object_base_deinit,
        /*.gen_ref=*/               (__rv_system_object_base_gen_ref_ptr)               __rv_system_object_base_gen_ref,
        /*.gen_readlock=*/          (__rv_system_object_base_gen_readlock_ptr)          __rv_system_object_base_gen_readlock,
        /*.gen_writelock=*/         (__rv_system_object_base_gen_writelock_ptr)         __rv_system_object_base_gen_writelock,
        /*.get_type=*/              (__rv_system_object_base_get_type_ptr)              __rv_system_object_base_get_type,
        /*.get_type_name=*/         (__rv_system_object_base_get_type_name_ptr)         __rv_system_object_base_get_type_name,
        /*.get_all_type_names=*/    (__rv_system_object_base_get_all_type_names_ptr)    __rv_system_object_base_get_all_type_names,
        /*.get size=*/              (__rv_system_object_base_get_size_ptr)              __rv_system_object_base_get_size,
        /*.get_type_value=*/        (__rv_system_object_base_get_type_value_ptr)        __rv_system_object_base_get_type_value,
        /*.is_type=*/               (__rv_system_object_base_is_type_ptr)               __rv_system_object_base_is_type,
        /*.link=*/                  (__rv_system_object_base_link_ptr)                  __rv_system_object_base_link,
        /*.unlink=*/                (__rv_system_object_base_unlink_ptr)                __rv_system_object_base_unlink
        };

/* -------- structures containing easy function pointers --------------------- */

    //contains methods
        struct rv_system_object_base_ptr_s rv_system_object_base =
        {
        /*.create_static=*/         (rv_system_object_base_create_static_ptr)           rv_system_object_base_create_static,
        /*.create_super_static*/    (rv_system_object_base_create_super_static_ptr)     rv_system_object_base_create_super_static,
        /*.create*/                 (rv_system_object_base_create_ptr)                  rv_system_object_base_create,
        /*.create_super*/           (rv_system_object_base_create_super_ptr)            rv_system_object_base_create_super,
        /*.destroy*/                (rv_system_object_base_destroy_ptr)                 rv_system_object_base_destroy,
        /*.get_type*/               (rv_system_object_base_get_type_ptr)                rv_system_object_base_get_type,
        /*.get_type_name*/          (rv_system_object_base_get_type_name_ptr)           rv_system_object_base_get_type_name,
        /*.get_all_type_names*/     (rv_system_object_base_get_all_type_names_ptr)      rv_system_object_base_get_all_type_names,
        /*.get_size*/               (rv_system_object_base_get_size_ptr)                rv_system_object_base_get_size,
        /*.get_type_value*/         (rv_system_object_base_get_type_value_ptr)          rv_system_object_base_get_type_value,
        /*.is_type*/                (rv_system_object_base_is_type_ptr)                 rv_system_object_base_is_type
        };

/* ------------------- static function definitions --------------------------------- */

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
        )
        {
            return rv_system_object_base_create_super_static( t, sz, &rv_system_object_base_vtble, (void *)t, mem );
        }

    //rv_system_object_base_create_super_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_object_base_create_super_static
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s             *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                                   sz,
        //vtble
            struct rv_system_object_base_vtble_s       *vtble,
        //top object
            void                                       *top,
        //memory
            struct rv_system_memory_s                  *mem
        )
        {
            if( sz < sizeof( struct rv_system_object_base_s ) )
                return 0;
            t->is_dynamic = 0;
            t->mem = mem;
            t->top = top;
            t->vtble = vtble;
            return t->vtble->init( t, t->top );
        }

    //rv_system_object_base_create() initiates struct in newly allocated memory
        struct rv_system_object_base_s *rv_system_object_base_create
        (
        //memory
            struct rv_system_memory_s                  *mem,
        //memory lock (optional)
            struct rv_system_memory_lock_s             *mem_lock_optional
        )
        {
            return (struct rv_system_object_base_s *)rv_system_object_base_create_super( 0, 0, sizeof( struct rv_system_object_base_s ), &rv_system_object_base_vtble, mem, mem_lock_optional );
        }

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
        )
        {
            struct rv_system_memory_lock_s ml, *pml;
            void        *r;
            union
            {
                void        *r;
                uint64_t    l;
                struct rv_system_object_base_s *t;
            } a;
        //memory lock
            if( !mem && !mem_lock_optional )
                return 0;
            pml = mem_lock_optional;
            if( !pml )
            {
                if( !rv_system_memory_lock_create_static( &ml, sizeof( ml ) ) )
                    return 0;
                pml = &ml;
                if( !rv_system_memory_lock_lock( &ml, mem ) )
                {
                    rv_system_memory_lock_destroy_static( &ml );
                    return 0;
                }
            }
        //allocate and create
            r = 0;
            do
            {
            //allocate memory
                if( !rv_system_memory_lock_allocate( pml, sz, &r ) )
                    continue;
                a.r = r;
                a.l += base_offset;
                if( !rv_system_object_base_create_super_static( a.t, sz - base_offset, vtble, r, mem ) )
                    continue;
            //unlock
                if( !mem_lock_optional )
                    rv_system_memory_lock_destroy_static( &ml );
            //return success
                if( pt )
                    *pt = a.t;
                return r;
            }
            while( 0 );
        //release memory
            if( r )
                rv_system_memory_lock_release( pml, r );
        //unlock
            if( !mem_lock_optional )
                rv_system_memory_lock_destroy_static( &ml );
        //return fail
            return 0;
        }

    //rv_system_object_base_destroy() releases resources in struct, releases struct memory if was allocated dynamically
        void rv_system_object_base_destroy
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t
        )
        {
            struct rv_system_memory_lock_s ml;
        //deinit chain
            t->vtble->deinit( t, t->top );
        //release memory
            if( t->is_dynamic && rv_system_memory_lock_create_static( &ml, sizeof( ml ) ) )
            {
                do
                {
                    if( !rv_system_memory_lock_lock( &ml, t->mem ) )
                        continue;
                    rv_system_memory_lock_release( &ml, t->top );
                }
                while( 0 );
                rv_system_memory_lock_destroy_static( &ml );
            }
        };

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
        )
        {
            return t->vtble->get_type( t, t->top, pp, ctype );
        }

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
        )
        {
            return t->vtble->get_type_name( t, t->top, buff, buff_size );
        }

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
        )
        {
            return t->vtble->get_all_type_names( t, t->top, buff, buff_size );
        }

    //rv_system_object_base_get_size() returns size of this object and all memory used by this object including memory not contained within this object (child objects etc)
        uint64_t rv_system_object_base_get_size
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t
        )
        {
            return t->vtble->get_size( t, t->top );
        };

    //rv_system_object_base_get_type_value() returns string for type name
        char *rv_system_object_base_get_type_value
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t
        )
        {
            return t->vtble->get_type_value( t, t->top );
        };

    //rv_system_object_base_is_type() returns true if type is found in object
        bool rv_system_object_base_is_type
        (
        //pointer to memory holding struct
            struct rv_system_object_base_s     *t,
        //type
            char                                *ctype
        )
        {
            return t->vtble->is_type( t, t->top, ctype );
        }

/* -- virtual method corresponding static function stubs --------------------- */

    //init function, returns true if successful
        bool __rv_system_object_base_init
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        )
        {
            return 1;
        }

    //deinit function
        void __rv_system_object_base_deinit
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        )
        {

        }

    //gen ref function, returns false if fails
        bool __rv_system_object_base_gen_ref
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //pointer to receive ref
            struct rv_system_object_ref_s       **pp
        )
        {
            return 0;
        };

    //gen readlock function, returns false if fails
        bool __rv_system_object_base_gen_readlock
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
        bool __rv_system_object_base_gen_writelock
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
        bool __rv_system_object_base_get_type
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
            if( (char *)ctype == (char *)rv_system_object_type__object_base )
            {
                if( pp )
                    *pp = (void *)p_base;
                return 1;
            }
            return 0;
        }

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
        )
        {
            return __rv_system_object_base_get_type_name__helper( pb, szb, rv_system_object_type__object_base );
        }

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
        )
        {
            return __rv_system_object_base_get_all_type_names__helper( p_base, top, pb, szb, 0, 0 );
        }

    //get size funcion, returns size of object and all memory owned by object including child objects
        uint64_t __rv_system_object_base_get_size
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        )
        {
            return sizeof( struct rv_system_object_base_s );
        }

    //get type function
        char *__rv_system_object_base_get_type_value
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top
        )
        {
            return rv_system_object_type__object_base;
        }

    //test type function, returns true if object is of that type
        bool __rv_system_object_base_is_type
        (
        //pointer to object base
            struct rv_system_object_base_s      *p_base,
        //pointer to top level object, inherits base object
            void                                *top,
        //string type name
            char *ctype
        )
        {
            return (char *)ctype == (char *)rv_system_object_type__object_base;
        }

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
        )
        {
            return 0;
        }

    //unlink object to this object
        bool __rv_system_object_base_unlink
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
            return 0;
        }

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
        )
        {
            uint32_t i, s;
        //loop
            i = 0;
            s = szb;
            do
            {
            //copy
                if( pb && i < s )
                    pb[ i ] = *ctype;
                i++;
                ctype++;
            }
            while( *ctype );
        //return
            return (uint16_t)i;
        }

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
        )
        {
            uint32_t c, szr;
            char *npb;
        //get this type name
            c = p_base->vtble->get_type_name( p_base, top, pb, szb );
            if( !next_vtble || !next_object )
                return (uint16_t)c;
        //compute offset
            if( c )
                c--;
            if( pb && c < (uint32_t)szb )
                npb = &pb[ c ];
            else
                npb = 0;
            szr = (uint32_t)szb - c;
        //spacing
            c += __rv_system_object_base_get_type_name__helper( npb, (uint16_t)szr, "<--" );
        //compute offset
            if( c )
                c--;
            if( pb && c < (uint32_t)szb )
                npb = &pb[ c ];
            else
                npb = 0;
            szr = (uint32_t)szb - c;
        //next name
            c += next_vtble->get_all_type_names( p_base, next_object, npb, (uint16_t)szr );
        //return size
            return (uint16_t)c;
        }

//header guard end
    #endif



