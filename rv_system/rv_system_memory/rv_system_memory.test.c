
/* ============================ rv_system_memory.test.c ===================================== //

    rv_system_memory.test.c

    tests memory lib

// ============================ rv_system_memory.test.c ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_memory_SLASH_rv_system_memory_test_DOT_c
    #define rv_system_SLASH_rv_system_memory_SLASH_rv_system_memory_test_DOT_c

/* ------------------- included headers --------------------------------------- */

    //header
        #include "rv_system_memory.test.h"
        #include "rv_system_memory.h"
        #include "rv_system_memory_lock.h"
    //stdout
        #include <stdio.h>
        #include <stdlib.h>

/* ------------------- static function definitions --------------------------------- */

    //rv_system_memory_test() test memory
    //returns true when successful
        bool rv_system_memory_test
        (
        //do print out everything
            bool    verbose
        )
        {
            struct rv_system_memory_s m;
            struct rv_system_memory_stats_s s;
            struct rv_system_memory_lock_s l;
            void *p0, *p1, *p2;
            bool r = 1;
        //header
            if( verbose )
                fprintf( stdout, "====== Memory Test ======\n" );
        //creating memory
            if( verbose )
                fprintf( stdout, "\tCreating memory...\n" );
            if( !rv_system_memory_create_static( &m, sizeof( m ) ) )
            {
                fprintf( stderr, "\tCreating memory...FAILED\n" );
                fprintf( stderr, "====== Memory Test - FAILED ======\n" );
                return 0;
            }
            if( verbose )
                fprintf( stdout, "\tCreating memory...SUCCESS\n" );
        //detroy loop hack
            do
            {
            //create lock
                if( verbose )
                    fprintf( stdout, "\tCreating memory lock...\n" );
                if( !rv_system_memory_lock_create_static( &l, sizeof( l ) ) )
                {
                    fprintf( stderr, "\tCreating memory lock...FAILED\n" );
                    r = 0;
                    continue;
                }
                if( verbose )
                    fprintf( stdout, "\tCreating memory lock...SUCCESS\n" );
            //lock destroy hack
                do
                {
                //lock memory
                    if( verbose )
                        fprintf( stdout, "\tLocking memory...\n" );
                    if( !rv_system_memory_lock_lock( &l, &m ) )
                    {
                        fprintf( stderr, "\tLocking memory...SUCCESS\n" );
                        r = 0;
                        continue;
                    }
                    if( verbose )
                        fprintf( stdout, "\tLocking memory...SUCCESS\n" );
                //lock memory loop hack
                    do
                    {
                    //allocate 3 allocations
                        if( verbose )
                            fprintf( stdout, "\tAllocating memory...\n" );
                        r &= rv_system_memory_lock_allocate( &l, 1000, &p0 );
                        r &= rv_system_memory_lock_allocate( &l, 10000, &p1 );
                        r &= rv_system_memory_lock_allocate( &l, 100000, &p2 );
                        rv_system_memory_lock_get_stats( &l, &s );
                        if( verbose )
                            rv_system_memory_lock_print( &l );
                        if( verbose )
                            rv_system_memory_lock_print_stats( &l, &s );
                        r &= ( s.allocation_used == 111000 );
                        rv_system_memory_lock_release( &l, p0 );
                        rv_system_memory_lock_release( &l, p1 );
                        rv_system_memory_lock_release( &l, p2 );
                        if( verbose )
                            rv_system_memory_lock_print( &l );
                        if( !r )
                            fprintf( stderr, "\tAllocating memory...FAILED\n" );
                        else
                        {
                            if( verbose )
                                fprintf( stdout, "\tAllocating memory...SUCCESS\n" );
                        }
                    }
                    while( 0 );
                }
                while( 0 );
            //destroy lock
                if( verbose )
                    fprintf( stdout, "\tDestroying memory lock...\n" );
                rv_system_memory_lock_destroy_static( &l );
                if( verbose )
                    fprintf( stdout, "\tDestroying memory lock...SUCCESS\n" );
            }
            while( 0 );
        //destroy memory
            if( verbose )
                fprintf( stdout, "\tDestroying memory...\n" );
            rv_system_memory_destroy_static( &m );
            if( verbose )
                fprintf( stdout, "\tDestroying memory...SUCCESS\n" );
        //return status
            if( r )
            {
                if( verbose )
                    fprintf( stdout, "====== Memory Test - SUCCESS ======\n" );
            }
            else
                fprintf( stderr, "====== Memory Test - FAILED ======\n" );
            return r;
        }

//header guard end
    #endif



