
/* ============================ rv_system_time.c ===================================== //

    rv_system_time.c

    wrapper for handling the querying of the epoch time and system tick count
    epoch time is the integer seconds elapsed since 1/1/1970
    tick count is the integer milliseconds elapsed since system boot

// ============================ rv_system_time.c ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_time_SLASH_rv_system_time_DOT_c
    #define rv_system_SLASH_rv_system_time_SLASH_rv_system_time_DOT_c

/* ------------------- included headers --------------------------------------- */

    //header
        #include "rv_system_time.h"
    //std time
        #include <time.h>
    //std lib
        #include <stdlib.h>

/* -------- structures containing easy function pointers --------------------- */

    //contains time struct methods
        struct rv_system_time_ptr_s rv_system_time =
        {
            /*.create_static=*/ rv_system_time_create_static,
            /*.destroy_static=*/ rv_system_time_destroy_static,
            /*.query=*/ rv_system_time_query
        };

/* ------------------- static function definitions --------------------------------- */

    //rv_system_time_create_static() initiates time struct in externally allocated memory
    //returns true when successful
        bool rv_system_time_create_static
        (
        //pointer to memory holding struct
            struct rv_system_time_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        )
        {
        //test size
            if( sz < sizeof( struct rv_system_time_s ) )
                return 0;
        //init values
            t->ticks_ms = 0;
            t->epoch_s = 0;
            t->epoch_ms = 0;
        //priming read
            if( !rv_system_time.query( t ) )
                return 0;
        //success
            return 1;
        }

    //rv_system_time_destroy_static() releases resources in time struct in externally allocated memory
        void rv_system_time_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_time_s     *t
        )
        {
            (void)t;
        //nothing to do
        }

    //rv_system_time_query() fetches time from system
    //returns true when successful
        bool rv_system_time_query
        (
        //pointer to memory holding struct
            struct rv_system_time_s    *t
        )
        {
            bool r = 0;
            uint64_t tc = 0, d, ds, ep;
            #ifdef rv_system_os_is_posix
                struct timespec ts;
            #endif
        //get tc
            #ifdef rv_system_os_is_posix
                r = ( clock_gettime( CLOCK_MONOTONIC, &ts ) ) == 0;
                tc = (uint64_t)ts.tv_sec * (uint64_t)1000 + (uint64_t)ts.tv_nsec / (uint64_t)1000000;
            #endif
            #ifdef rv_system_os_is_windows
                r = 1;
                tc = (uint64_t)GetTickCount();
            #endif
        //failed tc?
            if( !r )
                return 0;
        //get epoch
            ep = (uint64_t)time( 0 );
            if( t->ticks_ms > 0 )
                d = tc - t->ticks_ms;
            else
                d = 0;
            ds = ep - t->epoch_s;
            ds *= 1000;
            t->epoch_s = ep;
            t->epoch_ms = t->epoch_s * 1000 + ( d - ds );
        //save tc
            t->ticks_ms = tc;
        //return results
            return r;
        }

/* -- virtual method corresponding static function definitions --------------------- */

    //none


//header guard end
    #endif

