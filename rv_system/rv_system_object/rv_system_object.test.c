
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
    //memory
        #include "../rv_system_memory/rv_system_memory.h"
        #include "../rv_system_memory/rv_system_memory_lock.h"

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
            struct rv_system_memory_lock_s ml;
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
            b = rv_system_memory_lock_create_static( &ml, sizeof( ml ) );
            if( !b )
            {
                rv_system_memory_destroy_static( &m );
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
                obj = rv_system_object_create( &m, 0 );
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
                    b = rv_system_object_test_object( verbose, 0, &obj->base, &m, &ml );
                    if( !b )
                        continue;
                }
                while( 0 );
                rv_system_object_base_destroy( &obj->base );
            }
            while( 0 );

if( rv_system_memory_lock_lock( &ml, &m ) )
{
    rv_system_memory_lock_print( &ml );
    rv_system_memory_lock_unlock( &ml );
}

            rv_system_memory_lock_destroy_static( &ml );
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
            struct rv_system_memory_s *mem,
        //memory lock
            struct rv_system_memory_lock_s *meml
        )
        {
            return 1;
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
            struct rv_system_memory_s *mem,
        //memory lock
            struct rv_system_memory_lock_s *meml
        )
        {
            bool b;
            struct rv_system_object_ref_s sr0, sr1, sr2;
            struct rv_system_object_ref_s *r0, *r1, *r2;
        //header
            if( verbose )
                fprintf( stdout, "\tTesting object by locking and creating refs...\r\n" );
        //run locking test on object itself
            if( !rv_system_object_test_locking( 1, useGenLocks, obj, mem, meml ) )
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
            b = obj->vtble->gen_ref( obj, &r0 );
            b &= obj->vtble->gen_ref( obj, &r1 );
            b &= obj->vtble->gen_ref( obj, &r2 );
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

if( rv_system_memory_lock_lock( meml, mem ) )
{
    rv_system_memory_lock_print( meml );
    rv_system_memory_lock_unlock( meml );
}

            //test locking on ref
                if( verbose )
                    fprintf( stdout, "\t\tTesting refs...\r\n" );
                b = rv_system_object_test_locking( 1, useGenLocks, &r0->base, mem, meml );
                b &= rv_system_object_test_locking( 1, useGenLocks, &r1->base, mem, meml );
                b &= rv_system_object_test_locking( 1, useGenLocks, &r2->base, mem, meml );
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
if( rv_system_memory_lock_lock( meml, mem ) )
{
    rv_system_memory_lock_print( meml );
    rv_system_memory_lock_unlock( meml );
}

            fprintf( stderr, "\tTesting object by locking and creating refs...SUCCEEDED\r\n" );
            return 1;
        }

//header guard end
    #endif





