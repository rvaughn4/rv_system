
/* ============================ rv_system_rwlock_holder.c ===================================== //

    rv_system_rwlock_holder.c

    maintains the lifecycle of one or more locks on a rwlock

// ============================ rv_system_rwlock_holder.c ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_rwlock_SLASH_rv_system_rwlock_holder_DOT_c
    #define rv_system_SLASH_rv_system_rwlock_SLASH_rv_system_rwlock_holder_DOT_c

/* ------------------- included headers --------------------------------------- */

    //header
        #include "rv_system_rwlock_holder.h"
    //lock
        #include "rv_system_rwlock.h"
    //time struct
        #include "../rv_system_time/rv_system_time.h"
    //lock holder
        #include "../rv_system_lock/rv_system_lock_holder_multiple.h"

/* -------- structures containing easy function pointers --------------------- */

    //contains time struct methods
        struct rv_system_rwlock_holder_ptr_s rv_system_rwlock_holder =
        {
            /*.create_static=*/ rv_system_rwlock_holder_create_static,
            /*.destroy_static=*/ rv_system_rwlock_holder_destroy_static,
            /*.add=*/ rv_system_rwlock_holder_add,
            /*.clear=*/ rv_system_rwlock_holder_clear,
            /*.lock=*/ rv_system_rwlock_holder_lock,
            /*.unlock=*/ rv_system_rwlock_holder_unlock,
            /*.contains=*/ rv_system_rwlock_holder_contains,
            /*.is_locked=*/ rv_system_rwlock_holder_is_locked
        };

/* ------------------- static function definitions --------------------------------- */

    //rv_system_rwlock_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_rwlock_holder_create_static
        (
        //pointer to memory holding struct
            struct rv_system_rwlock_holder_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        )
        {
        //check size
            if( sz < sizeof( struct rv_system_rwlock_holder_s ) )
                return 0;
        //init values
            t->entries = &t->first_entry;
            t->entry_cnt = 1;
            t->first_entry.p = 0;
        //return success
            return 1;
        }

    //rv_system_rwlock_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_rwlock_holder_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_rwlock_holder_s     *t
        )
        {
        //clear all
            rv_system_rwlock_holder_clear( t );
        }

    //rv_system_rwlock_holder_add() add mutex to holder collection
        bool rv_system_rwlock_holder_add
        (
        //pointer to struct
            struct rv_system_rwlock_holder_s     *t,
        //pointer to lock to add
            struct rv_system_rwlock_s            *l,
        //type of locking to do, read or write
            bool                                is_write
        )
        {
            uint16_t i, m;
            struct rv_system_rwlock_entry_s *e;
        //loop through until blank found
            m = t->entry_cnt;
            for( i = 0; i < m; i++ )
            {
                e = &t->entries[ i ];
            //is not blank, skip
                if( e->p )
                    continue;
            //fill blank and return
                e->p = l;
                e->is_locked = 0;
                e->is_write = is_write;
                return 1;
            }
        //blank not found
            return 0;
        }

    //rv_system_lock_holder_clear() clear all mutexes (will unlock them)
        void rv_system_rwlock_holder_clear
        (
        //pointer to struct
            struct rv_system_rwlock_holder_s     *t
        )
        {
            uint16_t i, m;
        //unlock all
            rv_system_rwlock_holder_unlock( t );
        //loop through until blank found
            m = t->entry_cnt;
            for( i = 0; i < m; i++ )
                t->entries[ i ].p = 0;
        }

    //rv_system_lock_holder_lock() lock add mutexes
        bool rv_system_rwlock_holder_lock
        (
        //pointer to struct
            struct rv_system_rwlock_holder_s     *t,
        //wait forever if true
            bool                                is_blocking,
        //timeout in milliseconds
            uint64_t                            timeout_ms,
        //all must lock or fails, unlocks those that were locked
            bool                                all_must_lock_or_fail
        )
        {
            uint16_t i, m;
            uint64_t st, tr;
            bool r;
            union
            {
                struct rv_system_lock_holder_multiple_s lm;
                struct rv_system_lock_holder_s lh;
            } ll;
            struct rv_system_rwlock_entry_s *e;
            struct rv_system_lock_holder_s *lh;
            struct rv_system_time_s tm;
        //init time
            if( !rv_system_time_create_static( &tm, sizeof( tm ) ) )
                return 0;
        //init lock holder
            if( t->entry_cnt > 1 )
            {
                if( !rv_system_lock_holder_multiple_create_static( &ll.lm, sizeof( ll.lm ) ) )
                    return 0;
                lh = &ll.lm.super;
            }
            else
            {
                if( !rv_system_lock_holder_create_static( &ll.lh, sizeof( ll.lh ) ) )
                    return 0;
                lh = &ll.lh;
            }
        //compute stop time
            st = tm.ticks_ms + timeout_ms;
        //outter timeout loop
            r = 0;
            while( !r && ( is_blocking || st >= tm.ticks_ms ) )
            {
             //do nothing loop hack
                do
                {
                //populate lock holder
                    for( i = 0; i < t->entry_cnt; i++ )
                    {
                        e = &t->entries[ i ];
                        if( !e->p || e->is_locked )
                            continue;
                    //to allow multiple readlocks on same thread
                        if( e->is_write || !rv_system_lock_holder_contains( lh, &e->p->lk ) )
                            rv_system_lock_holder_add( lh, &e->p->lk );
                    }
                //attempt locking it
                    if( st > tm.ticks_ms )
                        tr = st - tm.ticks_ms;
                    else
                        tr = 0;
                    if( !rv_system_lock_holder_lock( lh, is_blocking, tr, all_must_lock_or_fail ) )
                        continue;
                //loop through all entries and do read or write locking tests
                    r = 1;
                    if( all_must_lock_or_fail )
                    {
                        for( i = 0; r && i < t->entry_cnt; i++ )
                        {
                            e = &t->entries[ i ];
                            if( !e->p || e->is_locked )
                                continue;
                            if( e->p->wr_cnt > 0 )
                                r = 0;
                            if( e->is_write && e->p->rd_cnt > 0 )
                                r = 0;
                        }
                    //if failed tests, continue timeout loop
                        if( !r )
                            continue;
                    }
                //perform locking actions
                    for( i = 0; r && i < t->entry_cnt; i++ )
                    {
                        e = &t->entries[ i ];
                        if( !e->p || e->is_locked )
                            continue;
                        if( !all_must_lock_or_fail && !rv_system_lock_holder_is_locked( lh, &e->p->lk ) )
                            continue;
                        if( e->p->wr_cnt > 0 || ( e->is_write && e->p->rd_cnt > 0 ) )
                        {
                            r = !all_must_lock_or_fail;
                            continue;
                        }
                        if( e->is_write )
                            e->p->wr_cnt++;
                        e->p->rd_cnt++;
                        e->is_locked = 1;
                    }
                //unlock if failed at locking
                    if( !r )
                    {
                        m = i;
                        for( i = 0; i < m; i++ )
                        {
                            e = &t->entries[ i ];
                            if( !e->p || !e->is_locked )
                                continue;
                            if( e->p->rd_cnt > 0 )
                                e->p->rd_cnt--;
                            if( e->p->wr_cnt > 0 )
                                e->p->wr_cnt--;
                            e->is_locked = 0;
                        }
                    }
                }
                while( 0 );
            //clear lock holder
                rv_system_lock_holder_clear( lh );
            //update time
                if( !r )
                    rv_system_time_query( &tm );
            }
        //release lock holder
            rv_system_lock_holder_destroy_static( lh );
        //release time
            rv_system_time_destroy_static( &tm );
        //return status
            return r;
        }

    //rv_system_lock_holder_unlock() unlock all mutexes
        void rv_system_rwlock_holder_unlock
        (
        //pointer to struct
            struct rv_system_rwlock_holder_s     *t
        )
        {
            uint16_t i;
            union
            {
                struct rv_system_lock_holder_multiple_s lm;
                struct rv_system_lock_holder_s lh;
            } ll;
            struct rv_system_rwlock_entry_s *e;
            struct rv_system_lock_holder_s *lh;
        //init lock holder
            if( t->entry_cnt > 1 )
            {
                if( !rv_system_lock_holder_multiple_create_static( &ll.lm, sizeof( ll.lm ) ) )
                    return;
                lh = &ll.lm.super;
            }
            else
            {
                if( !rv_system_lock_holder_create_static( &ll.lh, sizeof( ll.lh ) ) )
                    return;
                lh = &ll.lh;
            }
        //populate lock holder
            for( i = 0; i < t->entry_cnt; i++ )
            {
                e = &t->entries[ i ];
                if( !e->p || !e->is_locked )
                    continue;
                if( !rv_system_lock_holder_contains( lh, &e->p->lk ) )
                    rv_system_lock_holder_add( lh, &e->p->lk );
            }
        //attempt to lock
            if( !rv_system_lock_holder_lock( lh, 1, 0, 1 ) )
            {
                rv_system_lock_holder_destroy_static( lh );
                return;
            }
        //subtract locks
            for( i = 0; i < t->entry_cnt; i++ )
            {
                e = &t->entries[ i ];
                if( !e->p || !e->is_locked )
                    continue;
                if( e->p->rd_cnt > 0 )
                    e->p->rd_cnt--;
                if( e->p->wr_cnt > 0 )
                    e->p->wr_cnt--;
                e->is_locked = 0;
            }
        //release lock holder
            rv_system_lock_holder_destroy_static( lh );
        }

    //rv_system_rwlock_holder_contains() returns true if collection contains rwlock
        bool rv_system_rwlock_holder_contains
        (
        //pointer to struct
            struct rv_system_rwlock_holder_s     *t,
        //pointer to lock to add
            struct rv_system_rwlock_s            *l
        )
        {
            uint16_t i, m;
            struct rv_system_rwlock_entry_s *e;
        //loop through until blank found
            m = t->entry_cnt;
            for( i = 0; i < m; i++ )
            {
                e = &t->entries[ i ];
            //skip
                if( e->p != l )
                    continue;
                return 1;
            }
        //not found
            return 0;
        }

    //rv_system_rwlock_holder_is_locked() returns true if rwlock is in the collection and locked
        bool rv_system_rwlock_holder_is_locked
        (
        //pointer to struct
            struct rv_system_rwlock_holder_s     *t,
        //pointer to lock to add
            struct rv_system_rwlock_s            *l
        )
        {
            uint16_t i, m;
            struct rv_system_rwlock_entry_s *e;
        //loop through until blank found
            m = t->entry_cnt;
            for( i = 0; i < m; i++ )
            {
                e = &t->entries[ i ];
            //skip
                if( e->p != l )
                    continue;
                return e->is_locked;
            }
        //not found
            return 0;
        }

//header guard end
    #endif




