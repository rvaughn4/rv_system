
/* ============================ rv_system_object_locker.c ===================================== //

    rv_system_object_locker.h

    maintains the lifecycle of one or more rwlocked objects

// ============================ rv_system_object_locker.c ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_object_SLASH_rv_system_object_locker_DOT_c
    #define rv_system_SLASH_rv_system_object_SLASH_rv_system_object_locker_DOT_c

/* ------------------- included headers --------------------------------------- */

    //headers
        #include "rv_system_object_locker.h"
        #include "rv_system_object_base.h"
        #include "rv_system_object_writelock.h"
        #include "rv_system_object_readlock.h"
    //rwlock
        #include "../rv_system_rwlock/rv_system_rwlock_holder.h"
        #include "../rv_system_rwlock/rv_system_rwlock_holder_multiple.h"
        #include "../rv_system_rwlock/rv_system_rwlock.h"

/* -------- structures containing easy function pointers --------------------- */

    //contains struct methods
        struct rv_system_object_locker_ptr_s rv_system_object_locker =
        {
            /*.create_static=*/     rv_system_object_locker_create_static,
            /*.destroy_static=*/    rv_system_object_locker_destroy_static,
            /*.add=*/               rv_system_object_locker_add,
            /*.clear=*/             rv_system_object_locker_clear,
            /*.lock=*/              rv_system_object_locker_lock,
            /*.unlock=*/            rv_system_object_locker_unlock,
            /*.contains=*/          rv_system_object_locker_contains,
            /*.is_locked=*/         rv_system_object_locker_is_locked
        };

/* ------------------- static function stubs --------------------------------- */

    //rv_system_object_locker_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_object_locker_create_static
        (
        //pointer to memory holding struct
            struct rv_system_object_locker_s    *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                            sz
        )
        {
        //check size
            if( sz < sizeof( struct rv_system_object_locker_s ) )
                return 0;
        //init values
            t->entries = &t->first_entry;
            t->entry_cnt = 1;
            t->first_entry.o = 0;
        //init rwlock holder
            t->lh = &t->slh;
            return rv_system_rwlock_holder_create_static( &t->slh, sizeof( t->slh ) );
        }


    //rv_system_object_locker_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_object_locker_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_object_locker_s     *t
        )
        {
            rv_system_object_locker_clear( t );
            rv_system_rwlock_holder_destroy_static( &t->slh );
        };

    //rv_system_object_locker_add() add rwlock to holder collection
        bool rv_system_object_locker_add
        (
        //pointer to struct
            struct rv_system_object_locker_s        *t,
        //pointer to object to add
            struct rv_system_object_base_s          *o,
        //pointer to lock to add (optional)
            struct rv_system_object_base_s          *l_optional,
        //type of locking to perform, read or write
            bool                                    is_write
        )
        {
            uint16_t i, m;
            struct rv_system_object_entry_s *e;
        //loop through until blank found
            m = t->entry_cnt;
            for( i = 0; i < m; i++ )
            {
                e = &t->entries[ i ];
            //is not blank, skip
                if( e->o )
                    continue;
            //fill blank and return
                e->is_locked = 0;
                e->is_write = is_write;
                e->d = 0;
                e->l = l_optional;
            //no writelock or readlock object provided, must create and delete later
                if( !e->l )
                {
                    if( e->is_write )
                    {
                        struct rv_system_object_writelock_s *wl;
                        o->vtble->gen_writelock( o, &wl );
                        if( wl )
                            e->l = &wl->base;
                    }
                    else
                    {
                        struct rv_system_object_readlock_s *rl;
                        o->vtble->gen_readlock( o, &rl );
                        if( rl )
                            e->l = &rl->base;
                    }
                //make sure to keep up with deleting it!
                    e->d = e->l;
                }
            //failed obtaining lock object
                if( !e->l )
                    return 0;
            //success
                e->o = o;
                return 1;
            }
        //blank not found
            return 0;
        };

    //rv_system_object_locker_clear() clear all mutexes (will unlock them)
        void rv_system_object_locker_clear
        (
        //pointer to struct
            struct rv_system_object_locker_s     *t
        )
        {
            uint16_t i, m;
        //unlock all
            rv_system_object_locker_unlock( t );
        //loop through until blank found
            m = t->entry_cnt;
            for( i = 0; i < m; i++ )
                t->entries[ i ].o = 0;
        //clear lock holder
            rv_system_rwlock_holder_clear( t->lh );
        };

    //rv_system_object_locker_lock() lock add mutexes
        bool rv_system_object_locker_lock
        (
        //pointer to struct
            struct rv_system_object_locker_s    *t,
        //wait forever if true
            bool                                is_blocking,
        //timeout in milliseconds
            uint64_t                            timeout_ms,
        //all must be locked or else fail and unlock those already locked
            bool                                all_must_lock_or_fail
        )
        {
            uint16_t i, m;
            struct rv_system_object_entry_s *e;
            struct rv_system_rwlock_s *rwl;
        //add all entries to lock holder
            m = t->entry_cnt;
            for( i = 0; i < m; i++ )
            {
                e = &t->entries[ i ];
            //skip blanks or locked
                if( !e->o || e->is_locked )
                    continue;
            //fetch rwl
                rwl = 0;
                if( !rwl )
                    return 0;
            //add
                if( !rv_system_rwlock_holder_add( t->lh, rwl, e->is_write ) )
                    return 0;
            }
        //attempt to lock
            if( !rv_system_rwlock_holder_lock( t->lh, is_blocking, timeout_ms, all_must_lock_or_fail ) )
                return 0;
        //set locked flags and link
            for( i = 0; i < m; i++ )
            {
                e = &t->entries[ i ];
            //skip blanks or locked
                if( !e->o || e->is_locked )
                    continue;
            //set locked flags and link
                if( all_must_lock_or_fail )
                {
                    e->is_locked = 1;
                    if( e->l )
                        e->l->vtble->link( e->l, e->o, is_blocking, timeout_ms );
                }
                else
                {
                //fetch rwl
                    rwl = 0;
                    if( !rwl )
                        continue;
                //test
                    e->is_locked = rv_system_rwlock_holder_is_locked( t->lh, rwl );
                //link
                    if( e->l )
                        e->l->vtble->link( e->l, e->o, is_blocking, timeout_ms );
                }
            }
        //return success
            return 1;
        }

    //rv_system_object_locker_unlock() unlock all mutexes
        void rv_system_object_locker_unlock
        (
        //pointer to struct
            struct rv_system_object_locker_s     *t
        )
        {
            uint16_t i, m;
            struct rv_system_object_entry_s *e;
        //loop through and delete maintained locks
            m = t->entry_cnt;
            for( i = 0; i < m; i++ )
            {
                e = &t->entries[ i ];
                e->is_locked = 0;
                if( !e->l )
                    continue;
                e->l->vtble->unlink( e->l, e->o, 1, 0 );
                if( !e->d )
                    rv_system_object_base_destroy( e->d );
            }
        //unlock all in holder
            rv_system_rwlock_holder_unlock( t->lh );
        };

    //rv_system_object_locker_contains() returns true if collection contains object
        bool rv_system_object_locker_contains
        (
        //pointer to struct
            struct rv_system_object_locker_s     *t,
        //pointer to object to test
            struct rv_system_object_base_s       *o
        )
        {
            uint16_t i, m;
            struct rv_system_object_entry_s *e;
        //loop through until blank found
            m = t->entry_cnt;
            for( i = 0; i < m; i++ )
            {
                e = &t->entries[ i ];
            //skip
                if( e->o != o )
                    continue;
                return 1;
            }
        //not found
            return 0;
        };

    //rv_system_object_locker_is_locked() returns true if object is in the collection and locked
        bool rv_system_object_locker_is_locked
        (
        //pointer to struct
            struct rv_system_object_locker_s     *t,
        //pointer to lock to test
            struct rv_system_object_base_s       *o
        )
        {
            uint16_t i, m;
            struct rv_system_object_entry_s *e;
        //loop through until blank found
            m = t->entry_cnt;
            for( i = 0; i < m; i++ )
            {
                e = &t->entries[ i ];
            //skip
                if( e->o != o )
                    continue;
                return e->is_locked;
            }
        //not found
            return 0;
        };

    //rv_system_object_locker_get_locked() returns true if object is in the collection and locked,
    //      fetches pointer to lock of specified type
        bool rv_system_object_locker_get_locked
        (
        //pointer to struct
            struct rv_system_object_locker_s     *t,
        //pointer to object to test
            struct rv_system_object_base_s       *o,
        //type of lock to fetch
            char                                 *ctype,
        //pointer to receive pointer to lock
            void                                 **pl
        )
        {
            uint16_t i, m;
            struct rv_system_object_entry_s *e;
        //loop through until blank found
            m = t->entry_cnt;
            for( i = 0; i < m; i++ )
            {
                e = &t->entries[ i ];
            //skip
                if( e->o != o )
                    continue;
                if( pl )
                    e->l->vtble->get_type( e->l, pl, ctype );
                return e->is_locked;
            }
        //not found
            return 0;
        }

//header guard end
    #endif





