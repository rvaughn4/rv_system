
/* ============================ rv_system_object_test.h ===================================== //

    rv_system_object_test.h

    handles mutual exclusions
    wrapper for system primitive

// ============================ rv_system_object_test.h ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_object_SLASH_rv_system_object_test_DOT_h
    #define rv_system_SLASH_rv_system_object_SLASH_rv_system_object_test_DOT_h

/* ------------------- included headers --------------------------------------- */

    //headers
        #include <stdbool.h>
    struct rv_system_object_base_s;
    struct rv_system_memory_s;
    struct rv_system_memory_lock_s;
    //#define rv_system_object_test_print_memory_enabled

/* ------------------- static function stubs --------------------------------- */

    //rv_system_object_test() test object functionality
    //returns true when successful
        bool rv_system_object_test
        (
            bool verbose
        );

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
        );

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
        );

    //prints memory contents
        void rv_system_object_test_print_memory
        (
        //memory
            struct rv_system_memory_s *mem
        );

//header guard end
    #endif




