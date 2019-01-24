
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
            bool    verbose,
        //line prefix /indent
            char    *pref
        )
        {
            struct rv_system_memory_s m;
            struct rv_system_memory_stats_s s;
            struct rv_system_memory_lock_s l;
            void *p0, *p1, *p2;
            bool r = 1;
            char prefbuff[ 1024 ];
        //header
            if( verbose )
                fprintf( stdout, "%s====== Memory Test ======\n", pref );
        //creating memory
            if( verbose )
                fprintf( stdout, "%s\tCreating memory...\n", pref );
            if( !rv_system_memory_create_static( &m, sizeof( m ) ) )
            {
                fprintf( stderr, "%s\tCreating memory...FAILED\n", pref );
                fprintf( stderr, "%s====== Memory Test - FAILED ======\n", pref );
                return 0;
            }
            if( verbose )
                fprintf( stdout, "%s\tCreating memory...SUCCESS\n", pref );
        //detroy loop hack
            do
            {
            //create lock
                if( verbose )
                    fprintf( stdout, "%s\tCreating memory lock...\n", pref );
                if( !rv_system_memory_lock_create_static( &l, sizeof( l ) ) )
                {
                    fprintf( stderr, "%s\tCreating memory lock...FAILED\n", pref );
                    r = 0;
                    continue;
                }
                if( verbose )
                    fprintf( stdout, "%s\tCreating memory lock...SUCCESS\n", pref );
            //lock destroy hack
                do
                {
                //lock memory
                    if( verbose )
                        fprintf( stdout, "%s\tLocking memory...\n", pref );
                    if( !rv_system_memory_lock_lock( &l, &m ) )
                    {
                        fprintf( stderr, "%s\tLocking memory...SUCCESS\n", pref );
                        r = 0;
                        continue;
                    }
                    if( verbose )
                        fprintf( stdout, "%s\tLocking memory...SUCCESS\n", pref );
                //lock memory loop hack
                    do
                    {
                    //allocate 3 allocations
                        if( verbose )
                            fprintf( stdout, "%s\tAllocating memory...\n", pref );
                        r &= rv_system_memory_lock_allocate( &l, 1000, &p0 );
                        r &= rv_system_memory_lock_allocate( &l, 10000, &p1 );
                        r &= rv_system_memory_lock_allocate( &l, 100000, &p2 );
                        rv_system_memory_lock_get_stats( &l, &s );
                        if( verbose )
                        {
                            prefbuff[ 0 ] = 0;
                            snprintf( prefbuff, 1024, "%s%s", pref, "\t\t" );
                            rv_system_memory_lock_print( &l, prefbuff );
                            rv_system_memory_lock_print_stats( &l, &s, prefbuff );
                        }
                        r &= ( s.allocation_used == 111000 );
                        rv_system_memory_lock_release( &l, p0 );
                        rv_system_memory_lock_release( &l, p1 );
                        rv_system_memory_lock_release( &l, p2 );
                        if( verbose )
                            rv_system_memory_lock_print( &l, prefbuff );
                        if( !r )
                            fprintf( stderr, "%s\tAllocating memory...FAILED\n", pref );
                        else
                        {
                            if( verbose )
                                fprintf( stdout, "%s\tAllocating memory...SUCCESS\n", pref );
                        }
                    }
                    while( 0 );
                }
                while( 0 );
            //destroy lock
                if( verbose )
                    fprintf( stdout, "%s\tDestroying memory lock...\n", pref );
                rv_system_memory_lock_destroy_static( &l );
                if( verbose )
                    fprintf( stdout, "%s\tDestroying memory lock...SUCCESS\n", pref );
            }
            while( 0 );
        //destroy memory
            if( verbose )
                fprintf( stdout, "%s\tDestroying memory...\n", pref );
            rv_system_memory_destroy_static( &m );
            if( verbose )
                fprintf( stdout, "%s\tDestroying memory...SUCCESS\n", pref );
        //return status
            if( r )
            {
                if( verbose )
                    fprintf( stdout, "%s====== Memory Test - SUCCESS ======\n", pref );
            }
            else
                fprintf( stderr, "%s====== Memory Test - FAILED ======\n", pref );
            return r;
        }

//header guard end
    #endif



