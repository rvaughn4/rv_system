
/* ============================ rv_system_rwlock_holder_multiple.c ===================================== //

    rv_system_rwlock_holder_multiple.c

    maintains the lifecycle of one or more rwlocks

// ============================ rv_system_rwlock_holder_multiple.c ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_rwlock_SLASH_rv_system_rwlock_holder_multiple_DOT_c
    #define rv_system_SLASH_rv_system_rwlock_SLASH_rv_system_rwlock_holder_multiple_DOT_c

/* ------------------- included headers --------------------------------------- */

    //header
        #include "rv_system_rwlock_holder_multiple.h"

/* -------- structures containing easy function pointers --------------------- */

    //contains time struct methods
        struct rv_system_rwlock_holder_multiple_ptr_s rv_system_rwlock_holder_multiple =
        {
            /*.create_static=*/ rv_system_rwlock_holder_multiple_create_static,
            /*.destroy_static=*/ rv_system_rwlock_holder_multiple_destroy_static,
            /*.add=*/ rv_system_rwlock_holder_multiple_add,
            /*.clear=*/ rv_system_rwlock_holder_multiple_clear,
            /*.lock=*/ rv_system_rwlock_holder_multiple_lock,
            /*.unlock=*/ rv_system_rwlock_holder_multiple_unlock,
            /*.contains=*/ rv_system_rwlock_holder_multiple_contains,
            /*.is_locked=*/ rv_system_rwlock_holder_multiple_is_locked
        };

/* ------------------- static function definitions --------------------------------- */

    //rv_system_lock_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_rwlock_holder_multiple_create_static
        (
        //pointer to memory holding struct
            struct rv_system_rwlock_holder_multiple_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        )
        {
            uint16_t i, m;
        //check size
            if( sz < sizeof( struct rv_system_rwlock_holder_multiple_s ) )
                return 0;
        //init super
            if( !rv_system_rwlock_holder_create_static( &t->super, sz ) )
                return 0;
            m = rv_system_rwlock_holder_multiple_entry_max;
            for( i = 0; i < m; i++ )
                t->entries[ i ].p = 0;
        //init values
            t->super.entries = t->entries;
            t->super.entry_cnt = rv_system_rwlock_holder_multiple_entry_max;
        //return success
            return 1;
        }

    //rv_system_time_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_rwlock_holder_multiple_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_rwlock_holder_multiple_s     *t
        )
        {
        //clear all
            rv_system_rwlock_holder_destroy_static( &t->super );
        }

    //rv_system_lock_holder_add() add mutex to holder collection
        bool rv_system_rwlock_holder_multiple_add
        (
        //pointer to struct
            struct rv_system_rwlock_holder_multiple_s     *t,
        //pointer to lock to add
            struct rv_system_rwlock_s            *l,
        //locking mode, read or write
            bool                                is_write
        )
        {
            return rv_system_rwlock_holder_add( &t->super, l, is_write );
        }

    //rv_system_lock_holder_clear() clear all mutexes (will unlock them)
        void rv_system_rwlock_holder_multiple_clear
        (
        //pointer to struct
            struct rv_system_rwlock_holder_multiple_s     *t
        )
        {
            rv_system_rwlock_holder_clear( &t->super );
        }

    //rv_system_lock_holder_lock() lock add mutexes
        bool rv_system_rwlock_holder_multiple_lock
        (
        //pointer to struct
            struct rv_system_rwlock_holder_multiple_s     *t,
        //wait forever if true
            bool                                is_blocking,
        //timeout in milliseconds
            uint64_t                            timeout_ms,
        //all must lock or fails, unlocks those that were locked
            bool                                all_must_lock_or_fail
        )
        {
            return rv_system_rwlock_holder_lock( &t->super, is_blocking, timeout_ms, all_must_lock_or_fail );
        }

    //rv_system_lock_holder_unlock() unlock all mutexes
        void rv_system_rwlock_holder_multiple_unlock
        (
        //pointer to struct
            struct rv_system_rwlock_holder_multiple_s     *t
        )
        {
            rv_system_rwlock_holder_unlock( &t->super );
        }

    //rv_system_rwlock_holder_multiple_contains() returns true if collection contains rwlock
        bool rv_system_rwlock_holder_multiple_contains
        (
        //pointer to struct
            struct rv_system_rwlock_holder_multiple_s     *t,
        //pointer to lock to add
            struct rv_system_rwlock_s            *l
        )
        {
            return rv_system_rwlock_holder_contains( &t->super, l );
        }

    //rv_system_rwlock_holder_is_locked() returns true if rwlock is in the collection and locked
        bool rv_system_rwlock_holder_multiple_is_locked
        (
        //pointer to struct
            struct rv_system_rwlock_holder_multiple_s     *t,
        //pointer to lock to add
            struct rv_system_rwlock_s            *l
        )
        {
            return rv_system_rwlock_holder_is_locked( &t->super, l );
        }

//header guard end
    #endif

