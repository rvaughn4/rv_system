
/* ============================ rv_system_lock_holder.c ===================================== //

    rv_system_lock_holder.c

    maintains the lifecycle of one or more locks on a mutex

// ============================ rv_system_lock_holder.c ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_lock_SLASH_rv_system_lock_holder_DOT_c
    #define rv_system_SLASH_rv_system_lock_SLASH_rv_system_lock_holder_DOT_c

/* ------------------- included headers --------------------------------------- */

    //header
        #include "rv_system_lock_holder.h"
    //lock
        #include "rv_system_lock.h"
    //time struct
        #include "../rv_system_time/rv_system_time.h"

/* -------- structures containing easy function pointers --------------------- */

    //contains time struct methods
        struct rv_system_lock_holder_ptr_s rv_system_lock_holder =
        {
            /*.create_static=*/ rv_system_lock_holder_create_static,
            /*.destroy_static=*/ rv_system_lock_holder_destroy_static,
            /*.add=*/ rv_system_lock_holder_add,
            /*.contains=*/ rv_system_lock_holder_contains,
            /*.is_locked=*/ rv_system_lock_holder_is_locked,
            /*.clear=*/ rv_system_lock_holder_clear,
            /*.lock=*/ rv_system_lock_holder_lock,
            /*.unlock=*/ rv_system_lock_holder_unlock
        };

/* ------------------- static function definitions --------------------------------- */

    //rv_system_lock_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_lock_holder_create_static
        (
        //pointer to memory holding struct
            struct rv_system_lock_holder_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        )
        {
        //check size
            if( sz < sizeof( struct rv_system_lock_holder_s ) )
                return 0;
        //init values
            t->entries = &t->first_entry;
            t->entry_cnt = 1;
            t->first_entry.p = 0;
        //return success
            return 1;
        }

    //rv_system_time_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_lock_holder_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_lock_holder_s     *t
        )
        {
        //clear all
            rv_system_lock_holder_clear( t );
        }

    //rv_system_lock_holder_add() add mutex to holder collection
        bool rv_system_lock_holder_add
        (
        //pointer to struct
            struct rv_system_lock_holder_s     *t,
        //pointer to lock to add
            struct rv_system_lock_s            *l
        )
        {
            uint16_t i, m;
        //loop through until blank found
            m = t->entry_cnt;
            for( i = 0; i < m; i++ )
            {
            //is not blank, skip
                if( t->entries[ i ].p )
                    continue;
            //fill blank and return
                t->entries[ i ].p = l;
                t->entries[ i ].is_locked = 0;
                return 1;
            }
        //blank not found
            return 0;
        }

    //rv_system_lock_holder_contains() returns true if in collection
        bool rv_system_lock_holder_contains
        (
        //pointer to struct
            struct rv_system_lock_holder_s     *t,
        //pointer to lock to add
            struct rv_system_lock_s            *l
        )
        {
            uint16_t i, m;
            struct rv_system_lock_entry_s *e;
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

    //rv_system_lock_holder_is_locked() returns true if collection contains that mutex and its locked
        bool rv_system_lock_holder_is_locked
        (
        //pointer to struct
            struct rv_system_lock_holder_s     *t,
        //pointer to lock to add
            struct rv_system_lock_s            *l
        )
        {
            uint16_t i, m;
            struct rv_system_lock_entry_s *e;
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

    //rv_system_lock_holder_clear() clear all mutexes (will unlock them)
        void rv_system_lock_holder_clear
        (
        //pointer to struct
            struct rv_system_lock_holder_s     *t
        )
        {
            uint16_t i, m;
        //unlock all
            rv_system_lock_holder_unlock( t );
        //loop through until blank found
            m = t->entry_cnt;
            for( i = 0; i < m; i++ )
            {
                t->entries[ i ].p = 0;
                t->entries[ i ].is_locked = 0;
            }
        }

    //rv_system_lock_holder_lock() lock add mutexes
        bool rv_system_lock_holder_lock
        (
        //pointer to struct
            struct rv_system_lock_holder_s     *t,
        //wait forever if true
            bool                                is_blocking,
        //timeout in milliseconds
            uint64_t                            timeout_ms,
        //all must be locked to succeed
            bool                                fail_when_any_not_locked
        )
        {
            uint16_t i, m, hc;
            uint64_t st;
            bool r = 0, b;
            struct rv_system_lock_entry_s *e;
            struct rv_system_time_s tm;
        //init time
            if( !rv_system_time_create_static( &tm, sizeof( tm ) ) )
                return 0;
        //compute stop time
            st = tm.ticks_ms + timeout_ms;
            hc = 0;
        //outter timeout loop
            b = 0;
            r = 1;
            while( !b && ( is_blocking || st >= tm.ticks_ms ) )
            {
                m = t->entry_cnt;
                b = 1;
                for( i = 0; i < m; i++ )
                {
                    e = &t->entries[ i ];
                //is blank or locked, skip
                    if( !e->p || e->is_locked )
                        continue;
                    if( hc < i )
                        hc = i + 1;
                //attempt to lock
                    if( m == 1 || ( r && hc == i ) )
                    {
                        if( __rv_system_lock_lock( e->p, is_blocking, timeout_ms ) )
                            e->is_locked = 1;
                    }
                    else
                    {
                        if( __rv_system_lock_lock( e->p, 0, 0 ) )
                            e->is_locked = 1;
                    }
                    if( !e->is_locked )
                    {
                        b = 0;
                        if( fail_when_any_not_locked )
                            r = 0;
                    }
                }
            //update time
                rv_system_time_query( &tm );
            }
        //if failed, unlock all
            if( !r )
                rv_system_lock_holder_unlock( t );
        //release time
            rv_system_time_destroy_static( &tm );
        //return status
            return r;
        }

    //rv_system_lock_holder_unlock() unlock all mutexes
        void rv_system_lock_holder_unlock
        (
        //pointer to struct
            struct rv_system_lock_holder_s     *t
        )
        {
            uint16_t i, m;
        //loop through until blank found
            m = t->entry_cnt;
            for( i = 0; i < m; i++ )
            {
            //is blank, skip
                if( !t->entries[ i ].p )
                    continue;
            //if locked, unlock
                if( t->entries[ i ].is_locked )
                    __rv_system_lock_unlock( t->entries[ i ].p );
            //blank out
                t->entries[ i ].is_locked = 0;
            }
        }

//header guard end
    #endif



