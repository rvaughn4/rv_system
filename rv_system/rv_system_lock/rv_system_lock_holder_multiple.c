
/* ============================ rv_system_lock_holder_multiple.c ===================================== //

    rv_system_lock_holder_multiple.c

    maintains the lifecycle of one or more locks on a mutex

// ============================ rv_system_lock_holder_multiple.c ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_lock_SLASH_rv_system_lock_holder_multiple_DOT_c
    #define rv_system_SLASH_rv_system_lock_SLASH_rv_system_lock_holder_multiple_DOT_c

/* ------------------- included headers --------------------------------------- */

    //header
        #include "rv_system_lock_holder_multiple.h"

/* -------- structures containing easy function pointers --------------------- */

    //contains time struct methods
        struct rv_system_lock_holder_multiple_ptr_s rv_system_lock_holder_multiple =
        {
            /*.create_static=*/ rv_system_lock_holder_multiple_create_static,
            /*.destroy_static=*/ rv_system_lock_holder_multiple_destroy_static,
            /*.add=*/ rv_system_lock_holder_multiple_add,
            /*.contains=*/ rv_system_lock_holder_multiple_contains,
            /*.is_locked=*/ rv_system_lock_holder_multiple_is_locked,
            /*.clear=*/ rv_system_lock_holder_multiple_clear,
            /*.lock=*/ rv_system_lock_holder_multiple_lock,
            /*.unlock=*/ rv_system_lock_holder_multiple_unlock
        };

/* ------------------- static function definitions --------------------------------- */

    //rv_system_lock_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_lock_holder_multiple_create_static
        (
        //pointer to memory holding struct
            struct rv_system_lock_holder_multiple_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        )
        {
            uint16_t i, m;
        //check size
            if( sz < sizeof( struct rv_system_lock_holder_multiple_s ) )
                return 0;
        //init super
            if( !rv_system_lock_holder_create_static( &t->super, sz ) )
                return 0;
            m = rv_system_lock_holder_multiple_entry_max;
            for( i = 0; i < m; i++ )
                t->entries[ i ].p = 0;
        //init values
            t->super.entries = t->entries;
            t->super.entry_cnt = rv_system_lock_holder_multiple_entry_max;
        //return success
            return 1;
        }

    //rv_system_time_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_lock_holder_multiple_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_lock_holder_multiple_s     *t
        )
        {
        //clear all
            rv_system_lock_holder_destroy_static( &t->super );
        }

    //rv_system_lock_holder_add() add mutex to holder collection
        bool rv_system_lock_holder_multiple_add
        (
        //pointer to struct
            struct rv_system_lock_holder_multiple_s     *t,
        //pointer to lock to add
            struct rv_system_lock_s            *l
        )
        {
            return rv_system_lock_holder_add( &t->super, l );
        }

    //rv_system_lock_holder_contains() returns true if mutex is in collection
        bool rv_system_lock_holder_multiple_contains
        (
        //pointer to struct
            struct rv_system_lock_holder_multiple_s     *t,
        //pointer to lock to add
            struct rv_system_lock_s            *l
        )
        {
            return rv_system_lock_holder_contains( &t->super, l );
        }

    //rv_system_lock_holder_is_locked() returns true if collection contains that mutex and its locked
        bool rv_system_lock_holder_multiple_is_locked
        (
        //pointer to struct
            struct rv_system_lock_holder_multiple_s     *t,
        //pointer to lock to add
            struct rv_system_lock_s            *l
        )
        {
            return rv_system_lock_holder_is_locked( &t->super, l );
        }

    //rv_system_lock_holder_clear() clear all mutexes (will unlock them)
        void rv_system_lock_holder_multiple_clear
        (
        //pointer to struct
            struct rv_system_lock_holder_multiple_s     *t
        )
        {
            rv_system_lock_holder_clear( &t->super );
        }

    //rv_system_lock_holder_lock() lock add mutexes
        bool rv_system_lock_holder_multiple_lock
        (
        //pointer to struct
            struct rv_system_lock_holder_multiple_s     *t,
        //wait forever if true
            bool                                is_blocking,
        //timeout in milliseconds
            uint64_t                            timeout_ms,
        //all must be locked to succeed
            bool                                fail_when_any_not_locked
        )
        {
            return rv_system_lock_holder_lock( &t->super, is_blocking, timeout_ms, fail_when_any_not_locked );
        }

    //rv_system_lock_holder_unlock() unlock all mutexes
        void rv_system_lock_holder_multiple_unlock
        (
        //pointer to struct
            struct rv_system_lock_holder_multiple_s     *t
        )
        {
            rv_system_lock_holder_unlock( &t->super );
        }

//header guard end
    #endif
