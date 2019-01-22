
/* ============================ rv_system_object_test.c ===================================== //

    rv_system_object_test.c

    handles mutual exclusions
    wrapper for system primitive

// ============================ rv_system_object_test.c ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_object_SLASH_rv_system_object_test_DOT_c
    #define rv_system_SLASH_rv_system_object_SLASH_rv_system_object_test_DOT_c

/* ------------------- included headers --------------------------------------- */

    //stdout
        #include <stdio.h>
        #include <stdlib.h>
        #include "rv_system_object.test.h"
    //object
        #include "rv_system_object_base.h"
        #include "rv_system_object.h"
        #include "rv_system_object_ref.h"
        #include "rv_system_object_readlock.h"
        #include "rv_system_object_writelock.h"
        #include "rv_system_object_locker.h"
        #include "rv_system_object_locker_multiple.h"
    //memory
        #include "../rv_system_memory/rv_system_memory.h"
        #include "../rv_system_memory/rv_system_memory_lock.h"

#include "../rv_system_thread/rv_system_thread.h"

/* ------------------- static function stubs --------------------------------- */

    //rv_system_object_test() test object functionality
    //returns true when successful
        bool rv_system_object_test
        (
            bool verbose
        )
        {
            bool b;
            struct rv_system_object_s /*sobj,*/ *obj;
            struct rv_system_memory_s m;
        //header
            if( verbose )
                fprintf( stdout, "=======Testing rv_system_object =========\r\n" );
        //init memory
            if( verbose )
                fprintf( stdout, "\tCreating memory...\r\n" );
            b = rv_system_memory_create_static( &m, sizeof( m ) );
            if( !b )
            {
                fprintf( stderr, "\tCreating memory...FAILED\r\n" );
                fprintf( stderr, "=======Testing rv_system_object FAILED =========\r\n" );
                return 0;
            }
            if( verbose )
                fprintf( stdout, "\tCreating memory...SUCCEDED\r\n" );
        //memory loop
            do
            {
            //create object
                if( verbose )
                    fprintf( stdout, "\tCreating object...\r\n" );
obj = rv_system_thread_create( &m, 0 );
                b = obj != 0;
                if( !b )
                {
                    fprintf( stderr, "\tCreating object...FAILED\r\n" );
                    continue;
                }
                if( verbose )
                    fprintf( stdout, "\tCreating object...SUCCEDED\r\n" );
            //object loop
                do
                {
                //test object
                    b = rv_system_object_test_object( verbose, 0, &obj->base, &m );
                    if( !b )
                        continue;
                    b = rv_system_object_test_object( verbose, 1, &obj->base, &m );
                    if( !b )
                        continue;
                }
                while( 0 );
                rv_system_object_base_destroy( &obj->base );
            }
            while( 0 );
            rv_system_memory_destroy_static( &m );
            if( !b )
            {
                fprintf( stderr, "=======Testing rv_system_object FAILED =========\r\n" );
                return 0;
            }
            if( verbose )
                fprintf( stderr, "=======Testing rv_system_object SUCCEDED =========\r\n" );
            return 1;
        }

    //rv_system_object_test_locking uses object to create readlocks and writelocks
    //      can allocate locks from memory or statically
        bool rv_system_object_test_locking
        (
            bool verbose,
        //when false, will use local stack allocated locks, when true object will generate locks
            bool useGenLocks,
        //object to run tests on
            struct rv_system_object_base_s *obj,
        //memory
            struct rv_system_memory_s *mem
        )
        {
            bool b = 0;
            struct rv_system_object_locker_multiple_s lhm;
            struct rv_system_object_locker_s lh;
            struct rv_system_object_writelock_s swl0, swl1, *wl0, *wl1;
            struct rv_system_object_readlock_s srl0, srl1, srl2, srl3, *rl0, *rl1, *rl2, *rl3;
        //header
            if( verbose )
                fprintf( stdout, "\tTesting object by locking...\r\n" );
        //create lock holders
            do
            {
                b = rv_system_object_locker_multiple_create_static( &lhm, sizeof( lhm ) );
                if( !b )
                    continue;
                b = rv_system_object_locker_create_static( &lh, sizeof( lh ) );
                if( !b )
                {
                    rv_system_object_locker_multiple_destroy_static( &lhm );
                    continue;
                }
            }
            while( 0 );
            if( !b )
            {
                fprintf( stderr, "\tTesting object by locking...FAILED\r\n" );
                return 0;
            }
            do
            {
            //create locks
                do
                {
                    if( !useGenLocks )
                    {
                        b = rv_system_object_writelock_create_static( &swl0, sizeof( swl0 ), mem );
                        wl0 = &swl0;
                        b &= rv_system_object_writelock_create_static( &swl1, sizeof( swl1 ), mem );
                        wl1 = &swl1;
                        b &= rv_system_object_readlock_create_static( &srl0, sizeof( srl0 ), mem );
                        rl0 = &srl0;
                        b &= rv_system_object_readlock_create_static( &srl1, sizeof( srl1 ), mem );
                        rl1 = &srl1;
                        b &= rv_system_object_readlock_create_static( &srl2, sizeof( srl2 ), mem );
                        rl2 = &srl2;
                        b &= rv_system_object_readlock_create_static( &srl3, sizeof( srl3 ), mem );
                        rl3 = &srl3;
                        if( !b )
                            continue;
                    }
                //multiple readlocks
                    if( verbose )
                        fprintf( stdout, "\t\tMultiple readlocks...\r\n" );
                    if( useGenLocks )
                    {
                        rl0 = 0;
                        rl1 = 0;
                        rl2 = 0;
                        rl3 = 0;
                    }
                    b = rv_system_object_locker_multiple_add_read( &lhm, obj, &rl0 );
                    b &= rv_system_object_locker_multiple_add_read( &lhm, obj, &rl1 );
                    b &= rv_system_object_locker_multiple_add_read( &lhm, obj, &rl2 );
                    b &= rv_system_object_locker_add_read( &lh, obj, &rl3 );
                    b &= rv_system_object_locker_multiple_lock( &lhm, 0, 100, 1 );
                    b &= rv_system_object_locker_lock( &lh, 0, 100, 1 );
                    rv_system_object_locker_multiple_unlock( &lhm );
                    rv_system_object_locker_unlock( &lh );
                    rv_system_object_locker_multiple_clear( &lhm );
                    rv_system_object_locker_clear( &lh );
                    if( !b )
                    {
                        fprintf( stdout, "\t\tMultiple readlocks...FAILED\r\n" );
                        continue;
                    }
                    if( verbose )
                        fprintf( stdout, "\t\tMultiple readlocks...SUCCESS\r\n" );
                //multiple writelocks (not legal)
                    if( verbose )
                        fprintf( stdout, "\t\tMultiple writelocks (illegal)...\r\n" );
                    if( useGenLocks )
                    {
                        wl0 = 0;
                        wl1 = 0;
                    }
                    b = rv_system_object_locker_multiple_add_write( &lhm, obj, &wl0 );
                    b &= rv_system_object_locker_add_write( &lh, obj, &wl1 );
                    b &= rv_system_object_locker_multiple_lock( &lhm, 0, 100, 1 );
                    b &= !rv_system_object_locker_lock( &lh, 0, 100, 1 );
                    rv_system_object_locker_multiple_unlock( &lhm );
                    rv_system_object_locker_unlock( &lh );
                    rv_system_object_locker_multiple_clear( &lhm );
                    rv_system_object_locker_clear( &lh );
                    if( !b )
                    {
                        fprintf( stdout, "\t\tMultiple writelocks (illegal)...FAILED\r\n" );
                        continue;
                    }
                    if( verbose )
                        fprintf( stdout, "\t\tMultiple writelocks (illegal)...SUCCESS\r\n" );
                //readlock during writelock
                    if( verbose )
                        fprintf( stdout, "\t\tReadlock during writelock (illegal)...\r\n" );
                    if( useGenLocks )
                    {
                        wl0 = 0;
                        rl0 = 0;
                    }
                    b = rv_system_object_locker_multiple_add_write( &lhm, obj, &wl0 );
                    b &= rv_system_object_locker_add_read( &lh, obj, &rl0 );
                    b &= rv_system_object_locker_multiple_lock( &lhm, 0, 100, 1 );
                    b &= !rv_system_object_locker_lock( &lh, 0, 100, 1 );
                    rv_system_object_locker_multiple_unlock( &lhm );
                    rv_system_object_locker_unlock( &lh );
                    rv_system_object_locker_multiple_clear( &lhm );
                    rv_system_object_locker_clear( &lh );
                    if( !b )
                    {
                        fprintf( stdout, "\t\tReadlock during writelock (illegal)...FAILED\r\n" );
                        continue;
                    }
                    if( verbose )
                        fprintf( stdout, "\t\tReadlock during writelock (illegal)...SUCCESS\r\n" );
                //writelock during readlock
                    if( verbose )
                        fprintf( stdout, "\t\tWritelock during readlock (illegal)...\r\n" );
                    if( useGenLocks )
                    {
                        wl0 = 0;
                        rl0 = 0;
                    }
                    b = rv_system_object_locker_multiple_add_read( &lhm, obj, &rl0 );
                    b &= rv_system_object_locker_add_write( &lh, obj, &wl0 );
                    b &= rv_system_object_locker_multiple_lock( &lhm, 0, 100, 1 );
                    b &= !rv_system_object_locker_lock( &lh, 0, 100, 1 );
                    rv_system_object_locker_multiple_unlock( &lhm );
                    rv_system_object_locker_unlock( &lh );
                    rv_system_object_locker_multiple_clear( &lhm );
                    rv_system_object_locker_clear( &lh );
                    if( !b )
                    {
                        fprintf( stdout, "\t\tWritelock during readlock (illegal)...FAILED\r\n" );
                        continue;
                    }
                    if( verbose )
                        fprintf( stdout, "\t\tWritelock during readlock (illegal)...SUCCESS\r\n" );
                }
                while( 0 );
            //destroy locks
                if( !useGenLocks )
                {
                    rv_system_object_base_destroy( &swl0.base );
                    rv_system_object_base_destroy( &swl1.base );
                    rv_system_object_base_destroy( &srl0.base );
                    rv_system_object_base_destroy( &srl1.base );
                    rv_system_object_base_destroy( &srl2.base );
                    rv_system_object_base_destroy( &srl3.base );
                }
            }
            while( 0 );
        //destroy lock holders
            rv_system_object_locker_destroy_static( &lh );
            rv_system_object_locker_multiple_destroy_static( &lhm );
        //results
            if( b )
            {
                if( verbose )
                    fprintf( stdout, "\tTesting object by locking...SUCCESS\r\n" );
            }
            else
                fprintf( stderr, "\tTesting object by locking...FAILED\r\n" );
        //return status
            return b;
        }

    //rv_system_object_test_object will test locking on object provided, then will create refs and test those
    //      can allocate locks from memory or statically
        bool rv_system_object_test_object
        (
            bool verbose,
        //when false, will use local stack allocated locks, when true object will generate locks
            bool useGenLocks,
        //object to run tests on
            struct rv_system_object_base_s *obj,
        //memory
            struct rv_system_memory_s *mem
        )
        {
            bool b;
            struct rv_system_object_ref_s sr0, sr1, sr2;
            struct rv_system_object_ref_s *r0, *r1, *r2;
        //header
            if( verbose )
                fprintf( stdout, "\tTesting object by locking and creating refs...\r\n" );
        //run locking test on object itself
            if( !rv_system_object_test_locking( 1, useGenLocks, obj, mem ) )
            {
                fprintf( stderr, "\tTesting object by locking and creating refs...FAILED\r\n" );
                return 0;
            }
        //handle memory
            if( useGenLocks )
            {
                r0 = 0;
                r1 = 0;
                r2 = 0;
            }
            else
            {
                r0 = &sr0;
                r1 = &sr1;
                r2 = &sr2;
                b = rv_system_object_ref_create_static( r0, sizeof( sr0 ), 0 );
                if( !b )
                    return 0;
                b = rv_system_object_ref_create_static( r1, sizeof( sr1 ), 0 );
                if( !b )
                {
                    rv_system_object_base_destroy( &r0->base );
                    return 0;
                }
                b = rv_system_object_ref_create_static( r2, sizeof( sr2 ), 0 );
                if( !b )
                {
                    rv_system_object_base_destroy( &r0->base );
                    rv_system_object_base_destroy( &r1->base );
                    return 0;
                }
            }
        //create 3 refs
            if( verbose )
                fprintf( stdout, "\t\tCreating refs...\r\n" );
            b = rv_system_object_base_get_ref( obj, &r0 );
            b &= rv_system_object_base_get_ref( obj, &r1 );
            b &= rv_system_object_base_get_ref( obj, &r2 );
            do
            {
            //failed
                if( !b )
                {
                    fprintf( stderr, "\t\tCreating refs...FAILED\r\n" );
                    continue;
                }
                if( verbose )
                    fprintf( stdout, "\t\tCreating refs...SUCCEEDED\r\n" );
            //test locking on ref
                if( verbose )
                    fprintf( stdout, "\t\tTesting refs...\r\n" );
                b = rv_system_object_test_locking( 1, useGenLocks, &r0->base, mem );
                if( !b )
                {
                    fprintf( stderr, "\t\tTesting refs...FAILED\r\n" );
                    continue;
                }
                if( verbose )
                    fprintf( stdout, "\t\tTesting refs...SUCCEEDED\r\n" );
            }
            while( 0 );
        //destroy refs
            if( r0 )
                rv_system_object_base_destroy( &r0->base );
            if( r1 )
                rv_system_object_base_destroy( &r1->base );
            if( r2 )
                rv_system_object_base_destroy( &r2->base );
            if( !b )
            {
                fprintf( stderr, "\tTesting object by locking and creating refs...FAILED\r\n" );
                return 0;
            }
            fprintf( stderr, "\tTesting object by locking and creating refs...SUCCEEDED\r\n" );
            return 1;
        }

//header guard end
    #endif





