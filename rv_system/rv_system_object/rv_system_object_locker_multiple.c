
/* ============================ rv_system_object_locker_multiple.c ===================================== //

    rv_system_object_locker_multiple.h

    maintains the lifecycle of one or more rwlocked objects

// ============================ rv_system_object_locker_multiple.c ==================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_object_SLASH_rv_system_object_locker_multiple_DOT_c
    #define rv_system_SLASH_rv_system_object_SLASH_rv_system_object_locker_multiple_DOT_c

/* ------------------- included headers --------------------------------------- */

    //include super
        #include "rv_system_object_locker_multiple.h"
        #include "rv_system_object_base.h"

/* -------- structures containing easy function pointers --------------------- */

    //contains struct methods
        struct rv_system_object_locker_multiple_ptr_s rv_system_object_locker_multiple =
        {
            /*.create_static=*/     rv_system_object_locker_multiple_create_static,
            /*.destroy_static=*/    rv_system_object_locker_multiple_destroy_static,
            /*.add=*/               rv_system_object_locker_multiple_add,
            /*.clear=*/             rv_system_object_locker_multiple_clear,
            /*.lock=*/              rv_system_object_locker_multiple_lock,
            /*.unlock=*/            rv_system_object_locker_multiple_unlock,
            /*.contains=*/          rv_system_object_locker_multiple_contains,
            /*.is_locked=*/         rv_system_object_locker_multiple_is_locked
        };

/* ------------------- static function definitions --------------------------------- */

    //rv_system_object_locker_multiple_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_object_locker_multiple_create_static
        (
        //pointer to memory holding struct
            struct rv_system_object_locker_multiple_s    *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                                     sz
        )
        {
            struct rv_system_object_entry_s *e;
            int i;
        //test size
            if( sz < sizeof( struct rv_system_object_locker_multiple_s ) )
                return 0;
        //init super
            if( !rv_system_object_locker_create_static( &t->super, sz ) )
                return 0;
        //init multiple
            t->super.entry_cnt = rv_system_object_locker_multiple_entry_max;
            t->super.entries = &t->entries[ 0 ];
        //init entires
            for( i = 0; i < rv_system_object_locker_multiple_entry_max; i++ )
            {
                e = &t->entries[ i ];
                e->is_locked = 0;
                e->is_write = 0;
                e->d = 0;
                e->l = 0;
                e->o = 0;
            }
        //return success
            return 1;
        }


    //rv_system_object_locker_multiple_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_object_locker_multiple_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_object_locker_multiple_s     *t
        )
        {
            rv_system_object_locker_destroy_static( &t->super );
        };

    //rv_system_object_locker_multiple_add() add rwlock to holder collection
        bool rv_system_object_locker_multiple_add
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s           *t,
        //pointer to object to add
            struct rv_system_object_base_s                      *o,
        //pointer to lock to add (optional)
            struct rv_system_object_base_s                      *l_optional,
        //type of locking to perform, read or write
            bool                                                is_write
        )
        {
            return rv_system_object_locker_add( &t->super, o, l_optional, is_write );
        }

    //rv_system_object_locker_multiple_clear() clear all mutexes (will unlock them)
        void rv_system_object_locker_multiple_clear
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s     *t
        )
        {
            rv_system_object_locker_clear( &t->super );
        };

    //rv_system_object_locker_multiple_lock() lock add mutexes
        bool rv_system_object_locker_multiple_lock
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s       *t,
        //wait forever if true
            bool                                            is_blocking,
        //timeout in milliseconds
            uint64_t                                        timeout_ms,
        //all must be locked or else fail and unlock those already locked
            bool                                            all_must_lock_or_fail
        )
        {
            return rv_system_object_locker_lock( &t->super, is_blocking, timeout_ms, all_must_lock_or_fail );
        }


    //rv_system_object_locker_multiple_unlock() unlock all mutexes
        void rv_system_object_locker_multiple_unlock
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s     *t
        )
        {
            rv_system_object_locker_unlock( &t->super );
        };


    //rv_system_object_locker_multiple_contains() returns true if collection contains object
        bool rv_system_object_locker_multiple_contains
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s       *t,
        //pointer to object to test
            struct rv_system_object_base_s                  *o
        )
        {
            return rv_system_object_locker_contains( &t->super, o );
        };

    //rv_system_object_locker_multiple_is_locked() returns true if object is in the collection and locked
        bool rv_system_object_locker_multiple_is_locked
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s       *t,
        //pointer to lock to test
            struct rv_system_object_base_s                  *o
        )
        {
            return rv_system_object_locker_is_locked( &t->super, o );
        };

    //rv_system_object_locker_multiple_get_locked() returns true if object is in the collection and locked,
    //      fetches pointer to lock of specified type
        bool rv_system_object_locker_multiple_get_locked
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s       *t,
        //pointer to object to test
            struct rv_system_object_base_s                  *o,
        //type of lock to fetch
            char                                            *ctype,
        //pointer to receive pointer to lock
            void                                            **pl
        )
        {
            return rv_system_object_locker_get_locked( &t->super, o, ctype, pl );
        }

//header guard end
    #endif






