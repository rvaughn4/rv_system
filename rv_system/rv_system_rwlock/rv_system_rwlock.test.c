
/* ============================ rv_system_rwlock_test.c ===================================== //

    rv_system_rwlock_test.c

    handles mutual exclusions
    wrapper for system primitive

// ============================ rv_system_rwlock_test.c ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_rwlock_SLASH_rv_system_rwlock_test_DOT_c
    #define rv_system_SLASH_rv_system_rwlock_SLASH_rv_system_rwlock_test_DOT_c

/* ------------------- included headers --------------------------------------- */

    //headers
        #include "rv_system_rwlock.test.h"
        #include "rv_system_rwlock.h"
        #include "rv_system_rwlock_holder.h"
        #include "rv_system_rwlock_holder_multiple.h"
    //stdio
        #include <stdio.h>
        #include <stdlib.h>

/* ------------------- static function stubs --------------------------------- */

    //rv_system_rwlock_test() test lock functionality
    //returns true when successful
        bool rv_system_rwlock_test
        (
            bool verbose
        )
        {
            bool b;
            struct rv_system_rwlock_s l0, l1, l2, l3;
            struct rv_system_rwlock_holder_s lh;
            struct rv_system_rwlock_holder_multiple_s lm;
        //header
            if( verbose )
                fprintf( stdout, "=======Testing rv_system_rwlock =========\r\n" );
        //init objects
            if( verbose )
                fprintf( stdout, "\tCreating objects...\r\n" );
            b = rv_system_rwlock.create_static( &l0, sizeof( l0 ) );
            b &= rv_system_rwlock.create_static( &l1, sizeof( l1 ) );
            b &= rv_system_rwlock.create_static( &l2, sizeof( l2 ) );
            b &= rv_system_rwlock.create_static( &l3, sizeof( l3 ) );
            b &= rv_system_rwlock_holder.create_static( &lh, sizeof( lh ) );
            b &= rv_system_rwlock_holder_multiple.create_static( &lm, sizeof( lm ) );
            if( !b )
            {
                fprintf( stderr, "\tCreating objects...FAIL\r\n" );
                fprintf( stderr, "=======Testing rv_system_rwlock FAILED =========\r\n" );
                return 0;
            }
            if( verbose )
                fprintf( stdout, "\tCreating objects...SUCCESS\r\n" );
        //loop hax
            do
            {
            //lock blocking
                if( verbose )
                    fprintf( stdout, "\tWrite locking one object blocking...\r\n" );
                b = rv_system_rwlock_holder.add( &lh, &l0, 1 );
                b &= rv_system_rwlock_holder.lock( &lh, 1, 0, 1 );
                if( !b )
                {
                    fprintf( stderr, "\tWrite locking one object blocking...FAIL\r\n" );
                    break;
                }
                rv_system_rwlock_holder.clear( &lh );
                if( verbose )
                    fprintf( stdout, "\tWrite locking one object blocking...SUCCESS\r\n" );
            //lock with 0 timeout
                if( verbose )
                    fprintf( stdout, "\tWrite locking one object with 0ms timeout...\r\n" );
                b = rv_system_rwlock_holder.add( &lh, &l0, 1 );
                b &= rv_system_rwlock_holder.lock( &lh, 0, 0, 1 );
                if( !b )
                {
                    fprintf( stderr, "\tWrite locking one object with 0ms timeout...FAIL\r\n" );
                    break;
                }
                rv_system_rwlock_holder.clear( &lh );
                if( verbose )
                    fprintf( stdout, "\tWrite locking one object with 0ms timeout...SUCCESS\r\n" );
            //lock with 100 timeout
                if( verbose )
                    fprintf( stdout, "\tWrite locking one object with 100ms timeout...\r\n" );
                b = rv_system_rwlock_holder.add( &lh, &l0, 1 );
                b &= rv_system_rwlock_holder.lock( &lh, 0, 100, 1 );
                if( !b )
                {
                    fprintf( stderr, "\tWrite locking one object with 100ms timeout...FAIL\r\n" );
                    break;
                }
                rv_system_rwlock_holder.clear( &lh );
                if( verbose )
                    fprintf( stdout, "\tWrite locking one object with 100ms timeout...SUCCESS\r\n" );
            //lock blocking
                if( verbose )
                    fprintf( stdout, "\tRead locking one object blocking...\r\n" );
                b = rv_system_rwlock_holder.add( &lh, &l0, 0 );
                b &= rv_system_rwlock_holder.lock( &lh, 1, 0, 1 );
                if( !b )
                {
                    fprintf( stderr, "\tRead locking one object blocking...FAIL\r\n" );
                    break;
                }
                rv_system_rwlock_holder.clear( &lh );
                if( verbose )
                    fprintf( stdout, "\tRead locking one object blocking...SUCCESS\r\n" );
            //lock with 0 timeout
                if( verbose )
                    fprintf( stdout, "\tRead locking one object with 0ms timeout...\r\n" );
                b = rv_system_rwlock_holder.add( &lh, &l0, 0 );
                b &= rv_system_rwlock_holder.lock( &lh, 0, 0, 1 );
                if( !b )
                {
                    fprintf( stderr, "\tRead locking one object with 0ms timeout...FAIL\r\n" );
                    break;
                }
                rv_system_rwlock_holder.clear( &lh );
                if( verbose )
                    fprintf( stdout, "\tRead locking one object with 0ms timeout...SUCCESS\r\n" );
            //lock with 100 timeout
                if( verbose )
                    fprintf( stdout, "\tRead locking one object with 100ms timeout...\r\n" );
                b = rv_system_rwlock_holder.add( &lh, &l0, 0 );
                b &= rv_system_rwlock_holder.lock( &lh, 0, 100, 1 );
                if( !b )
                {
                    fprintf( stderr, "\tRead locking one object with 100ms timeout...FAIL\r\n" );
                    break;
                }
                rv_system_rwlock_holder.clear( &lh );
                if( verbose )
                    fprintf( stdout, "\tRead locking one object with 100ms timeout...SUCCESS\r\n" );
            //multiple blocking locks on multiple mutexes
                if( verbose )
                    fprintf( stdout, "\tWrite locking multiple objects blocking...\r\n" );
                b = rv_system_rwlock_holder_multiple.add( &lm, &l0, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l1, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l2, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l3, 1 );
                b &= rv_system_rwlock_holder_multiple.lock( &lm, 1, 0, 1 );
                if( !b )
                {
                    fprintf( stderr, "\tWrite locking multiple objects blocking...FAIL\r\n" );
                    break;
                }
                rv_system_rwlock_holder_multiple.clear( &lm );
                if( verbose )
                    fprintf( stdout, "\tWrite locking multiple objects blocking...SUCCESS\r\n" );
            //multiple blocking locks on multiple mutexes
                if( verbose )
                    fprintf( stdout, "\tRead locking multiple objects blocking...\r\n" );
                b = rv_system_rwlock_holder_multiple.add( &lm, &l0, 0 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l1, 0 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l2, 0 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l3, 0 );
                b &= rv_system_rwlock_holder_multiple.lock( &lm, 1, 0, 1 );
                if( !b )
                {
                    fprintf( stderr, "\tRead locking multiple objects blocking...FAIL\r\n" );
                    break;
                }
                rv_system_rwlock_holder_multiple.clear( &lm );
                if( verbose )
                    fprintf( stdout, "\tRead locking multiple objects blocking...SUCCESS\r\n" );
            //multiple 0ms timeout locks on multiple mutexes
                if( verbose )
                    fprintf( stdout, "\tWrite locking multiple objects with 0ms timeout...\r\n" );
                b = rv_system_rwlock_holder_multiple.add( &lm, &l0, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l1, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l2, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l3, 1 );
                b &= rv_system_rwlock_holder_multiple.lock( &lm, 0, 0, 1 );
                if( !b )
                {
                    fprintf( stderr, "\tWrite locking multiple objects with 0ms timeout...FAIL\r\n" );
                    break;
                }
                rv_system_rwlock_holder_multiple.clear( &lm );
                if( verbose )
                    fprintf( stdout, "\tWrite locking multiple objects with 0ms timeout...SUCCESS\r\n" );
            //multiple 0ms timeout locks on multiple mutexes
                if( verbose )
                    fprintf( stdout, "\tRead locking multiple objects with 0ms timeout...\r\n" );
                b = rv_system_rwlock_holder_multiple.add( &lm, &l0, 0 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l1, 0 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l2, 0 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l3, 0 );
                b &= rv_system_rwlock_holder_multiple.lock( &lm, 0, 0, 1 );
                if( !b )
                {
                    fprintf( stderr, "\tRead locking multiple objects with 0ms timeout...FAIL\r\n" );
                    break;
                }
                rv_system_rwlock_holder_multiple.clear( &lm );
                if( verbose )
                    fprintf( stdout, "\tRead locking multiple objects with 0ms timeout...SUCCESS\r\n" );
            //multiple 100ms timeout locks on multiple mutexes
                if( verbose )
                    fprintf( stdout, "\tWrite locking multiple objects with 100ms timeout...\r\n" );
                b = rv_system_rwlock_holder_multiple.add( &lm, &l0, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l1, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l2, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l3, 1 );
                b &= rv_system_rwlock_holder_multiple.lock( &lm, 0, 100, 1 );
                if( !b )
                {
                    fprintf( stderr, "\tWrite locking multiple objects with 100ms timeout...FAIL\r\n" );
                    break;
                }
                rv_system_rwlock_holder_multiple.clear( &lm );
                if( verbose )
                    fprintf( stdout, "\tWrite locking multiple objects with 100ms timeout...SUCCESS\r\n" );
            //multiple 0ms timeout locks on multiple mutexes
                if( verbose )
                    fprintf( stdout, "\tRead locking multiple objects with 100ms timeout...\r\n" );
                b = rv_system_rwlock_holder_multiple.add( &lm, &l0, 0 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l1, 0 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l2, 0 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l3, 0 );
                b &= rv_system_rwlock_holder_multiple.lock( &lm, 0, 100, 1 );
                if( !b )
                {
                    fprintf( stderr, "\tRead locking multiple objects with 100ms timeout...FAIL\r\n" );
                    break;
                }
                rv_system_rwlock_holder_multiple.clear( &lm );
                if( verbose )
                    fprintf( stdout, "\tRead locking multiple objects with 100ms timeout...SUCCESS\r\n" );
            //multiple write locks on same object
                if( verbose )
                    fprintf( stdout, "\tMultiple write locks on same object (illegal)...\r\n" );
                b = rv_system_rwlock_holder_multiple.add( &lm, &l0, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 1 );
                b &= !rv_system_rwlock_holder_multiple.lock( &lm, 0, 100, 1 );
                if( !b )
                {
                    fprintf( stderr, "\tMultiple write locks on same object (illegal)...FAIL\r\n" );
                    break;
                }
                rv_system_rwlock_holder_multiple.clear( &lm );
                if( verbose )
                    fprintf( stdout, "\tMultiple write locks on same object (illegal)...SUCCESS\r\n" );
            //multiple read locks on same object
                if( verbose )
                    fprintf( stdout, "\tMultiple read locks on same object...\r\n" );
                b = rv_system_rwlock_holder_multiple.add( &lm, &l0, 0 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 0 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 0 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 0 );
                b &= rv_system_rwlock_holder_multiple.lock( &lm, 0, 100, 1 );
                if( !b )
                {
                    fprintf( stderr, "\tMultiple read locks on same object...FAIL\r\n" );
                    break;
                }
                rv_system_rwlock_holder_multiple.clear( &lm );
                if( verbose )
                    fprintf( stdout, "\tMultiple read locks on same object...SUCCESS\r\n" );
            //multiple read locks on same object that has been write locked first
                if( verbose )
                    fprintf( stdout, "\tMultiple read locks on same object that has been write locked first (illegal)...\r\n" );
                b = rv_system_rwlock_holder_multiple.add( &lm, &l0, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 0 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 0 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 0 );
                b &= !rv_system_rwlock_holder_multiple.lock( &lm, 0, 100, 1 );
                if( !b )
                {
                    fprintf( stderr, "\tMultiple read locks on same object that has been write locked first (illegal)...FAIL\r\n" );
                    break;
                }
                rv_system_rwlock_holder_multiple.clear( &lm );
                if( verbose )
                    fprintf( stdout, "\tMultiple read locks on same object that has been write locked first (illegal)...SUCCESS\r\n" );
            //multiple write locks on same object that has been read locked first
                if( verbose )
                    fprintf( stdout, "\tMultiple write locks on same object that has been read locked first (illegal)...\r\n" );
                b = rv_system_rwlock_holder_multiple.add( &lm, &l0, 0 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 1 );
                b &= !rv_system_rwlock_holder_multiple.lock( &lm, 0, 100, 1 );
                if( !b )
                {
                    fprintf( stderr, "\tMultiple write locks on same object that has been read locked first (illegal)...FAIL\r\n" );
                    break;
                }
                rv_system_rwlock_holder_multiple.clear( &lm );
                if( verbose )
                    fprintf( stdout, "\tMultiple write locks on same object that has been read locked first (illegal)...SUCCESS\r\n" );
            //using different holders, multiple read lock
                if( verbose )
                    fprintf( stdout, "\tMultiple containers, multiple read locks on same object...\r\n" );
                b = rv_system_rwlock_holder.add( &lh, &l0, 0 );
                b &= rv_system_rwlock_holder.lock( &lh, 0, 100, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 0 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 0 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 0 );
                b &= rv_system_rwlock_holder_multiple.lock( &lm, 0, 100, 1 );
                if( !b )
                {
                    fprintf( stderr, "\tMultiple containers, multiple read locks on same object...FAIL\r\n" );
                    break;
                }
                rv_system_rwlock_holder.clear( &lh );
                rv_system_rwlock_holder_multiple.clear( &lm );
                if( verbose )
                    fprintf( stdout, "\tMultiple containers, multiple read locks on same object...SUCCESS\r\n" );
            //using different holders, multiple write lock
                if( verbose )
                    fprintf( stdout, "\tMultiple containers, multiple write locks on same object (illegal)...\r\n" );
                b = rv_system_rwlock_holder.add( &lh, &l0, 1 );
                b &= rv_system_rwlock_holder.lock( &lh, 0, 100, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 1 );
                b &= !rv_system_rwlock_holder_multiple.lock( &lm, 0, 100, 1 );
                if( !b )
                {
                    fprintf( stderr, "\tMultiple containers, multiple write locks on same object (illegal)...FAIL\r\n" );
                    break;
                }
                rv_system_rwlock_holder.clear( &lh );
                rv_system_rwlock_holder_multiple.clear( &lm );
                if( verbose )
                    fprintf( stdout, "\tMultiple containers, multiple write locks on same object (illegal)...SUCCESS\r\n" );
            //using different holders, read lock on write locked object
                if( verbose )
                    fprintf( stdout, "\tMultiple containers, read lock on write locked object (illegal)...\r\n" );
                b = rv_system_rwlock_holder.add( &lh, &l0, 1 );
                b &= rv_system_rwlock_holder.lock( &lh, 0, 100, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 0 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 0 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 0 );
                b &= !rv_system_rwlock_holder_multiple.lock( &lm, 0, 100, 1 );
                if( !b )
                {
                    fprintf( stderr, "\tMultiple containers, read lock on write locked object (illegal)...FAIL\r\n" );
                    break;
                }
                rv_system_rwlock_holder.clear( &lh );
                rv_system_rwlock_holder_multiple.clear( &lm );
                if( verbose )
                    fprintf( stdout, "\tMultiple containers, read lock on write locked object (illegal)...SUCCESS\r\n" );
            //using different holders, write lock on read locked object
                if( verbose )
                    fprintf( stdout, "\tMultiple containers, write lock on read locked object (illegal)...\r\n" );
                b = rv_system_rwlock_holder.add( &lh, &l0, 0 );
                b &= rv_system_rwlock_holder.lock( &lh, 0, 100, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 1 );
                b &= rv_system_rwlock_holder_multiple.add( &lm, &l0, 1 );
                b &= !rv_system_rwlock_holder_multiple.lock( &lm, 0, 100, 1 );
                if( !b )
                {
                    fprintf( stderr, "\tMultiple containers, write lock on read locked object (illegal)...FAIL\r\n" );
                    break;
                }
                rv_system_rwlock_holder.clear( &lh );
                rv_system_rwlock_holder_multiple.clear( &lm );
                if( verbose )
                    fprintf( stdout, "\tMultiple containers, write lock on read locked object (illegal)...SUCCESS\r\n" );
            }
            while( 0 );
        //cleanup
            rv_system_rwlock_holder_multiple.destroy_static( &lm );
            rv_system_rwlock_holder.destroy_static( &lh );
            rv_system_rwlock.destroy_static( &l0 );
            rv_system_rwlock.destroy_static( &l1 );
            rv_system_rwlock.destroy_static( &l2 );
            rv_system_rwlock.destroy_static( &l3 );
        //print result
            if( !b )
            {
                fprintf( stderr, "=======Testing rv_system_rwlock FAILED =========\r\n" );
                return 0;
            }
            if( verbose )
                fprintf( stdout, "=======Testing rv_system_rwlock SUCCESS =========\r\n" );
            return 1;
        }

//header guard end
    #endif




