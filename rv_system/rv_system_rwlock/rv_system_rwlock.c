
/* ============================ rv_system_rwlock.c ===================================== //

    rv_system_rwlock.c

    handles reader writer locking

// ============================ rv_system_rwlock.c ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_rwlock_SLASH_rv_system_rwlock_DOT_c
    #define rv_system_SLASH_rv_system_rwlock_SLASH_rv_system_rwlock_DOT_c

/* ------------------- included headers --------------------------------------- */

    //header
        #include "rv_system_rwlock.h"

/* -------- structures containing easy function pointers --------------------- */

    //contains time struct methods
        struct rv_system_rwlock_ptr_s rv_system_rwlock =
        {
            /*.create_static=*/ rv_system_rwlock_create_static,
            /*.destroy_static=*/ rv_system_rwlock_destroy_static
        };

/* ------------------- static function definitions --------------------------------- */

    //rv_system_rwlock_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_rwlock_create_static
        (
        //pointer to memory holding struct
            struct rv_system_rwlock_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        )
        {
        //test size
            if( sz < sizeof( struct rv_system_rwlock_s ) )
                return 0;
        //init lock
            if( !rv_system_lock_create_static( &t->lk, sizeof( t->lk ) ) )
                return 0;
        //init values
            t->rd_cnt = 0;
            t->wr_cnt = 0;
        //return success
            return 1;
        }

    //rv_system_time_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_rwlock_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_rwlock_s     *t
        )
        {
        //try to write lock
        //deinit lock
            rv_system_lock_destroy_static( &t->lk );
        }

//header guard end
    #endif

