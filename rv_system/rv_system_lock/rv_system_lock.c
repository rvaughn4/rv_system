
/* ============================ rv_system_lock.c ===================================== //

    rv_system_lock.c

    wrapper for handling the querying of the epoch time and system tick count
    epoch time is the integer seconds elapsed since 1/1/1970
    tick count is the integer milliseconds elapsed since system boot

// ============================ rv_system_lock.c ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_lock_SLASH_rv_system_lock_DOT_c
    #define rv_system_SLASH_rv_system_lock_SLASH_rv_system_lock_DOT_c

/* ------------------- included headers --------------------------------------- */

    //header
        #include "rv_system_lock.h"
    //dump lock status to stdout
        //#define rv_system_lock_diagnose_locking
        #ifdef rv_system_lock_diagnose_locking
            #include <stdio.h>
            #include <stdlib.h>
        #endif

/* -------- structures containing easy function pointers --------------------- */

    //contains lock struct methods
        struct rv_system_lock_ptr_s rv_system_lock =
        {
            /*.create_static=*/ rv_system_lock_create_static,
            /*.destroy_static=*/ rv_system_lock_destroy_static
        };
        struct __rv_system_lock_ptr_s __rv_system_lock =
        {
            /*.pub=*/ &rv_system_lock,
            /*.lock=*/ __rv_system_lock_lock,
            /*.unlock=*/ __rv_system_lock_unlock
        };

/* ------------------- static function definitions --------------------------------- */

    //rv_system_lock_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_lock_create_static
        (
        //pointer to memory holding struct
            struct rv_system_lock_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        )
        {
            bool r = 0;
        //test size
            if( sz < sizeof( struct rv_system_lock_s ) )
                return 0;
        //init values
            #ifdef rv_system_os_is_posix
                r = pthread_mutex_init( &t->mtx, 0 ) == 0;
            #endif
        //success
            return r;
        }

    //rv_system_time_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_lock_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_lock_s     *t
        )
        {
        //destroy system primitive
            #ifdef rv_system_os_is_posix
                pthread_mutex_destroy( &t->mtx );
            #endif
        };

    //__rv_system_lock_lock() attempts to lock mutex before timeout
        bool __rv_system_lock_lock
        (
        //pointer to struct
            struct rv_system_lock_s *t,
        //true if should wait forever for lock
            bool is_blocking,
        //timeout in milliseconds, returns sooner if lock acquired
            uint64_t timeout_ms
        )
        {
            bool r = 0;
        //blocking
            if( is_blocking )
            {
                #ifdef rv_system_os_is_posix
                    r = pthread_mutex_lock( &t->mtx ) == 0;
                    #ifdef rv_system_lock_diagnose_locking
                        fprintf( stdout, "locked\n" );
                    #endif
                #endif
            }
            else
            {
                if( !timeout_ms )
                {
                    #ifdef rv_system_os_is_posix
                        r = pthread_mutex_trylock( &t->mtx ) == 0;
                        #ifdef rv_system_lock_diagnose_locking
                            fprintf( stdout, "locked\n" );
                        #endif
                    #endif
                }
                else
                {
                    #ifdef rv_system_os_is_posix
                        struct timespec ts;
                        ts.tv_sec = timeout_ms / 1000;
                        ts.tv_nsec = ( timeout_ms % 1000 ) * 1000000;
                        r = pthread_mutex_timedlock( &t->mtx, &ts ) == 0;
                        #ifdef rv_system_lock_diagnose_locking
                            fprintf( stdout, "locked\n" );
                        #endif
                    #endif
                }
            }
        //return status
            return r;
        }

    //__rv_system_lock_unlock() unlock mutex
        void __rv_system_lock_unlock
        (
        //pointer to struct
            struct rv_system_lock_s *t
        )
        {
        #ifdef rv_system_os_is_posix
            pthread_mutex_unlock( &t->mtx );
            #ifdef rv_system_lock_diagnose_locking
                fprintf( stdout, "unlocked\n" );
            #endif
        #endif
        };

/* -- virtual method corresponding static function definitions --------------------- */

    //none


//header guard end
    #endif


