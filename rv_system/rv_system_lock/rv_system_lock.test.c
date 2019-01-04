
/* ============================ rv_system_lock_test.c ===================================== //

    rv_system_lock_test.c

    handles mutual exclusions
    wrapper for system primitive

// ============================ rv_system_lock_test.c ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_lock_SLASH_rv_system_lock_test_DOT_c
    #define rv_system_SLASH_rv_system_lock_SLASH_rv_system_lock_test_DOT_c

/* ------------------- included headers --------------------------------------- */

    //headers
        #include "rv_system_lock.test.h"
    //headers
        #include "rv_system_lock.h"
        #include "rv_system_lock_holder.h"
        #include "rv_system_lock_holder_multiple.h"
    //stdio
        #include <stdio.h>
        #include <stdlib.h>

/* ------------------- static function stubs --------------------------------- */

    //rv_system_lock_test() test lock functionality
    //returns true when successful
        bool rv_system_lock_test
        (
            bool verbose
        )
        {
            bool b;
            struct rv_system_lock_s l0, l1, l2, l3;
            struct rv_system_lock_holder_s lh;
            struct rv_system_lock_holder_multiple_s lm;
        //header
            if( verbose )
                fprintf( stdout, "=======Testing rv_system_lock =========\r\n" );
        //init objects
            if( verbose )
                fprintf( stdout, "\tCreating objects...\r\n" );
            b = rv_system_lock.create_static( &l0, sizeof( l0 ) );
            b &= rv_system_lock.create_static( &l1, sizeof( l1 ) );
            b &= rv_system_lock.create_static( &l2, sizeof( l2 ) );
            b &= rv_system_lock.create_static( &l3, sizeof( l3 ) );
            b &= rv_system_lock_holder.create_static( &lh, sizeof( lh ) );
            b &= rv_system_lock_holder_multiple.create_static( &lm, sizeof( lm ) );
            if( !b )
            {
                fprintf( stderr, "\tCreating objects...FAIL\r\n" );
                fprintf( stderr, "=======Testing rv_system_lock FAILED =========\r\n" );
                return 0;
            }
            if( verbose )
                fprintf( stdout, "\tCreating objects...SUCCESS\r\n" );
        //loop hax
            do
            {
            //lock blocking
                if( verbose )
                    fprintf( stdout, "\tLocking one object blocking...\r\n" );
                b = rv_system_lock_holder.add( &lh, &l0 );
                b &= rv_system_lock_holder.lock( &lh, 1, 0, 1 ) > 0;
                if( !b )
                {
                    fprintf( stderr, "\tLocking one object blocking...FAIL\r\n" );
                    break;
                }
                rv_system_lock_holder.clear( &lh );
                if( verbose )
                    fprintf( stdout, "\tLocking one object blocking...SUCCESS\r\n" );
            //lock with 0 timeout
                if( verbose )
                    fprintf( stdout, "\tLocking one object with 0ms timeout...\r\n" );
                b = rv_system_lock_holder.add( &lh, &l0 );
                b &= rv_system_lock_holder.lock( &lh, 0, 0, 1 ) > 0;
                if( !b )
                {
                    fprintf( stderr, "\tLocking one object with 0ms timeout...FAIL\r\n" );
                    break;
                }
                rv_system_lock_holder.clear( &lh );
                if( verbose )
                    fprintf( stdout, "\tLocking one object with 0ms timeout...SUCCESS\r\n" );
            //lock with 1000 timeout
                if( verbose )
                    fprintf( stdout, "\tLocking one object with 1000ms timeout...\r\n" );
                b = rv_system_lock_holder.add( &lh, &l0 );
                b &= rv_system_lock_holder.lock( &lh, 0, 1000, 1 ) > 0;
                if( !b )
                {
                    fprintf( stderr, "\tLocking one object with 1000ms timeout...FAIL\r\n" );
                    break;
                }
                rv_system_lock_holder.clear( &lh );
                if( verbose )
                    fprintf( stdout, "\tLocking one object with 1000ms timeout...SUCCESS\r\n" );
            //multiple blocking locks on multiple mutexes
                if( verbose )
                    fprintf( stdout, "\tLocking multiple objects blocking...\r\n" );
                b = rv_system_lock_holder_multiple.add( &lm, &l0 );
                b &= rv_system_lock_holder_multiple.add( &lm, &l1 );
                b &= rv_system_lock_holder_multiple.add( &lm, &l2 );
                b &= rv_system_lock_holder_multiple.add( &lm, &l3 );
                b &= rv_system_lock_holder_multiple.lock( &lm, 1, 0, 1 ) > 0;
                if( !b )
                {
                    fprintf( stderr, "\tLocking multiple objects blocking...FAIL\r\n" );
                    break;
                }
                rv_system_lock_holder_multiple.clear( &lm );
                if( verbose )
                    fprintf( stdout, "\tLocking multiple objects blocking...SUCCESS\r\n" );
            //multiple 0 timeout locks on multiple mutexes
                if( verbose )
                    fprintf( stdout, "\tLocking multiple objects with 0ms timeout...\r\n" );
                b = rv_system_lock_holder_multiple.add( &lm, &l0 );
                b &= rv_system_lock_holder_multiple.add( &lm, &l1 );
                b &= rv_system_lock_holder_multiple.add( &lm, &l2 );
                b &= rv_system_lock_holder_multiple.add( &lm, &l3 );
                b &= rv_system_lock_holder_multiple.lock( &lm, 0, 0, 1 ) > 0;
                if( !b )
                {
                    fprintf( stderr, "\tLocking multiple objects with 0ms timeout...FAIL\r\n" );
                    break;
                }
                rv_system_lock_holder_multiple.clear( &lm );
                if( verbose )
                    fprintf( stdout, "\tLocking multiple objects with 0ms timeout...SUCCESS\r\n" );
            //multiple 1000 timeout locks on multiple mutexes
                if( verbose )
                    fprintf( stdout, "\tLocking multiple objects with 1000ms timeout...\r\n" );
                b = rv_system_lock_holder_multiple.add( &lm, &l0 );
                b &= rv_system_lock_holder_multiple.add( &lm, &l1 );
                b &= rv_system_lock_holder_multiple.add( &lm, &l2 );
                b &= rv_system_lock_holder_multiple.add( &lm, &l3 );
                b &= rv_system_lock_holder_multiple.lock( &lm, 0, 1000, 1 ) > 0;
                if( !b )
                {
                    fprintf( stderr, "\tLocking multiple objects with 1000ms timeout...FAIL\r\n" );
                    break;
                }
                rv_system_lock_holder_multiple.clear( &lm );
                if( verbose )
                    fprintf( stdout, "\tLocking multiple objects with 1000ms timeout...SUCCESS\r\n" );
            //multiple locks on same mutex
                if( verbose )
                    fprintf( stdout, "\tLocking same object twice (illegal)...\r\n" );
                b = rv_system_lock_holder_multiple.add( &lm, &l0 );
                b &= rv_system_lock_holder_multiple.add( &lm, &l0 );
                b &= rv_system_lock_holder_multiple.lock( &lm, 0, 100, 1 ) == 0;
                if( !b )
                {
                    fprintf( stderr, "\tLocking same object twice (illegal)...FAIL\r\n" );
                    break;
                }
                rv_system_lock_holder_multiple.clear( &lm );
                if( verbose )
                    fprintf( stdout, "\tLocking same object twice (illegal)...SUCCESS\r\n" );
            }
            while( 0 );
        //cleanup
            rv_system_lock_holder_multiple.destroy_static( &lm );
            rv_system_lock_holder.destroy_static( &lh );
            rv_system_lock.destroy_static( &l0 );
            rv_system_lock.destroy_static( &l1 );
            rv_system_lock.destroy_static( &l2 );
            rv_system_lock.destroy_static( &l3 );
        //print result
            if( !b )
            {
                fprintf( stderr, "=======Testing rv_system_lock FAILED =========\r\n" );
                return 0;
            }
            if( verbose )
                fprintf( stdout, "=======Testing rv_system_lock SUCCESS =========\r\n" );
            return 1;
        }

//header guard end
    #endif



