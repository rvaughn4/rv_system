
/* ============================ rv_system_rwlock.h ===================================== //

    rv_system_rwlock.h

    handles reader writer locking

// ============================ rv_system_rwlock.h ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_rwlock_SLASH_rv_system_rwlock_DOT_h
    #define rv_system_SLASH_rv_system_rwlock_SLASH_rv_system_rwlock_DOT_h

/* ------------------- included headers --------------------------------------- */

    //standard int size types
        #include <stdint.h>
    //standard boolean type
        #include <stdbool.h>
    //mutex
        #include "../rv_system_lock/rv_system_lock.h"

/* ------------------- structure stubs --------------------------------------- */

    //reader writer lock
        struct rv_system_rwlock_s;

/* ----------- virtual function/method stubs and typedefs -------------------- */

    //none

/* ------------------- structure definition ---------------------------------- */

    //reader writer lock
        struct rv_system_rwlock_s
        {
        //mutex
            struct rv_system_lock_s     lk;
        //counters
            uint16_t                    rd_cnt, wr_cnt;
        };

/* ------------------- static function stubs --------------------------------- */

    //rv_system_rwlock_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_rwlock_create_static
        (
        //pointer to memory holding struct
            struct rv_system_rwlock_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        );
        typedef bool (* rv_system_rwlock_create_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_rwlock_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        );

    //rv_system_time_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_rwlock_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_rwlock_s     *t
        );
        typedef void (* rv_system_rwlock_destroy_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_rwlock_s     *t
        );

/* -- virtual method corresponding static function stubs --------------------- */

    //none

/* -------- structures containing easy function pointers --------------------- */

    //contains time struct methods
        struct rv_system_rwlock_ptr_s
        {
        //create static
            rv_system_rwlock_create_static_ptr    create_static;
        //destroy static
            rv_system_rwlock_destroy_static_ptr   destroy_static;
        };
        struct rv_system_rwlock_ptr_s rv_system_rwlock;

//header guard end
    #endif


