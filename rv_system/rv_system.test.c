
/* ============================ rv_system_test.c ===================================== //

    rv_system_test.c

    test rv_system lib

// ============================ rv_system_test.c ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_test_DOT_c
    #define rv_system_SLASH_rv_system_test_DOT_c

/* ------------------- included headers --------------------------------------- */

    //header
        #include "rv_system.test.h"
    //std out
        #include <stdio.h>
        #include <stdlib.h>
    //lock
        #include "rv_system_lock/rv_system_lock.test.h"
    //rwlock
        #include "rv_system_rwlock/rv_system_rwlock.test.h"
    //memory
        #include "rv_system_memory/rv_system_memory.test.h"
    //object
        #include "rv_system_object/rv_system_object.test.h"

/* ------------------- static function stubs --------------------------------- */

    //rv_system_lock_test() test lock functionality
    //returns true when successful
        bool rv_system_test
        (
            bool verbose
        )
        {
            bool b = 1;
        //header
            if( verbose )
                fprintf( stdout, "=======Testing rv_system =========\r\n" );
        //loop hax
            do
            {
            //lock
                b &= rv_system_lock_test( verbose, "\t" );
                if( !b )
                    continue;
            //rwlock
                b &= rv_system_rwlock_test( verbose, "\t" );
                if( !b )
                    continue;
            //memory
                b &= rv_system_memory_test( verbose, "\t" );
                if( !b )
                    continue;
            //object
                b &= rv_system_object_test( verbose );
                if( !b )
                    continue;
            }
            while( 0 );
        //print result
            if( !b )
            {
                fprintf( stderr, "=======Testing rv_system FAILED =========\r\n" );
                return 0;
            }
            if( verbose )
                fprintf( stdout, "=======Testing rv_system SUCCESS =========\r\n" );
            return 1;


            return 0;
        }

//header guard end
    #endif




