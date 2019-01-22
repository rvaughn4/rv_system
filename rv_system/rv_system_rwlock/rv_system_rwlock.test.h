
/* ============================ rv_system_rwlock_test.h ===================================== //

    rv_system_rwlock_test.h

    handles mutual exclusions
    wrapper for system primitive

// ============================ rv_system_rwlock_test.h ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_rwlock_SLASH_rv_system_rwlock_test_DOT_h
    #define rv_system_SLASH_rv_system_rwlock_SLASH_rv_system_rwlock_test_DOT_h

/* ------------------- included headers --------------------------------------- */

    //headers
        #include <stdbool.h>

/* ------------------- static function stubs --------------------------------- */

    //rv_system_rwlock_test() test lock functionality
    //returns true when successful
        bool rv_system_rwlock_test
        (
        //verbose output, else just print errors
            bool    verbose,
        //prepended to every line
            char    *pref
        );

//header guard end
    #endif



