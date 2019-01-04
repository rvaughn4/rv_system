
/* ============================ rv_system_lock.h ===================================== //

    rv_system_lock.h

    handles mutual exclusions
    wrapper for system primitive

// ============================ rv_system_lock.h ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_lock_SLASH_rv_system_lock_DOT_h
    #define rv_system_SLASH_rv_system_lock_SLASH_rv_system_lock_DOT_h

/* ------------------- included headers --------------------------------------- */

    //os and hw defines
        #include "../os_define.h"
    //standard int size types
        #include <stdint.h>
    //standard boolean type
        #include <stdbool.h>
    //posix thread lib
        #ifdef rv_system_os_is_posix
            #include <pthread.h>
        #endif

/* ------------------- structure stubs --------------------------------------- */

    //mutual exclusion
        struct rv_system_lock_s;

/* ----------- virtual function/method stubs and typedefs -------------------- */

    //none

/* ------------------- structure definition ---------------------------------- */

    //mutual exclusion
        struct rv_system_lock_s
        {
        #ifdef rv_system_os_is_posix
            pthread_mutex_t mtx;
        #endif
        };

/* ------------------- static function stubs --------------------------------- */

    //rv_system_lock_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_lock_create_static
        (
        //pointer to memory holding struct
            struct rv_system_lock_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        );
        typedef bool (* rv_system_lock_create_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_lock_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        );

    //rv_system_time_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_lock_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_lock_s     *t
        );
        typedef void (* rv_system_lock_destroy_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_lock_s     *t
        );

    //__rv_system_lock_lock() attempts to lock mutex before timeout
        bool __rv_system_lock_lock
        (
        //pointer to struct
            struct rv_system_lock_s *t,
        //true if should wait forever for lock
            bool is_blocking,
        //timeout in milliseconds, returns sooner if lock acquired
            uint64_t timeout_ms
        );
        typedef bool (* __rv_system_lock_lock_ptr)
        (
        //pointer to struct
            struct rv_system_lock_s *t,
        //true if should wait forever for lock
            bool is_blocking,
        //timeout in milliseconds, returns sooner if lock acquired
            uint64_t timeout_ms
        );

    //__rv_system_lock_unlock() unlock mutex
        void __rv_system_lock_unlock
        (
        //pointer to struct
            struct rv_system_lock_s *t
        );
        typedef void (* __rv_system_lock_unlock_ptr)
        (
        //pointer to struct
            struct rv_system_lock_s *t
        );

/* -- virtual method corresponding static function stubs --------------------- */

    //none

/* -------- structures containing easy function pointers --------------------- */

    //contains time struct methods
        struct rv_system_lock_ptr_s
        {
        //create static
            rv_system_lock_create_static_ptr    create_static;
        //destroy static
            rv_system_lock_destroy_static_ptr   destroy_static;
        };
        struct rv_system_lock_ptr_s rv_system_lock;
        struct __rv_system_lock_ptr_s
        {
        //public functions
            struct rv_system_lock_ptr_s *pub;
        //lock mutex
            __rv_system_lock_lock_ptr   lock;
        //unlock mutex
            __rv_system_lock_unlock_ptr unlock;
        };
        struct __rv_system_lock_ptr_s __rv_system_lock;

//header guard end
    #endif

