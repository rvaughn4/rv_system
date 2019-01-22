
/* ============================ rv_system_lock_test.h ===================================== //

    rv_system_lock_test.h

    handles mutual exclusions
    wrapper for system primitive

// ============================ rv_system_lock_test.h ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_lock_SLASH_rv_system_lock_test_DOT_h
    #define rv_system_SLASH_rv_system_lock_SLASH_rv_system_lock_test_DOT_h

/* ------------------- included headers --------------------------------------- */

    //headers
        #include <stdbool.h>

/* ------------------- static function stubs --------------------------------- */

    //rv_system_lock_test() test lock functionality
    //returns true when successful
        bool rv_system_lock_test
        (
        //verbose output, else just print errors
            bool    verbose,
        //prepended to every line
            char    *pref
        );

//header guard end
    #endif


