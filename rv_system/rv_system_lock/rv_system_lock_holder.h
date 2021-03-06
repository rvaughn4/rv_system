
/* ============================ rv_system_lock_holder.h ===================================== //

    rv_system_lock_holder.h

    maintains the lifecycle of one or more locks on a mutex

// ============================ rv_system_lock_holder.h ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_lock_SLASH_rv_system_lock_holder_DOT_h
    #define rv_system_SLASH_rv_system_lock_SLASH_rv_system_lock_holder_DOT_h

/* ------------------- included headers --------------------------------------- */

    //os and hw defines
        #include "../../os_define.h"
    //standard int size types
        #include <stdint.h>
    //standard boolean type
        #include <stdbool.h>

/* ------------------- structure stubs --------------------------------------- */

    //mutual exclusion
        struct rv_system_lock_s;
    //entires of owned mutexes
        struct rv_system_lock_entry_s;
    //handles ownership of mutex lock
        struct rv_system_lock_holder_s;

/* ----------- virtual function/method stubs and typedefs -------------------- */

    //none

/* ------------------- structure definition ---------------------------------- */

    //entires of owned mutexes
        struct rv_system_lock_entry_s
        {
        //pointer to locked mutex
            struct rv_system_lock_s *p;
        //lock status
            bool is_locked;
        };

    //handles ownership of one or more locks on a mutex
        struct rv_system_lock_holder_s
        {
        //pointer to entries
            struct rv_system_lock_entry_s   *entries;
        //first entry
            struct rv_system_lock_entry_s   first_entry;
        //entry count
            uint8_t                         entry_cnt;
        };

/* ------------------- static function stubs --------------------------------- */

    //rv_system_lock_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_lock_holder_create_static
        (
        //pointer to memory holding struct
            struct rv_system_lock_holder_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        );
        typedef bool (* rv_system_lock_holder_create_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_lock_holder_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        );

    //rv_system_time_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_lock_holder_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_lock_holder_s     *t
        );
        typedef void (* rv_system_lock_holder_destroy_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_lock_holder_s     *t
        );

    //rv_system_lock_holder_add() add mutex to holder collection
        bool rv_system_lock_holder_add
        (
        //pointer to struct
            struct rv_system_lock_holder_s     *t,
        //pointer to lock to add
            struct rv_system_lock_s            *l
        );
        typedef bool (* rv_system_lock_holder_add_ptr)
        (
        //pointer to struct
            struct rv_system_lock_holder_s     *t,
        //pointer to lock to add
            struct rv_system_lock_s            *l
        );

    //rv_system_lock_holder_contains() returns true if collection contains that mutex
        bool rv_system_lock_holder_contains
        (
        //pointer to struct
            struct rv_system_lock_holder_s     *t,
        //pointer to lock to add
            struct rv_system_lock_s            *l
        );
        typedef bool (* rv_system_lock_holder_contains_ptr)
        (
        //pointer to struct
            struct rv_system_lock_holder_s     *t,
        //pointer to lock to add
            struct rv_system_lock_s            *l
        );

    //rv_system_lock_holder_is_locked() returns true if collection contains that mutex and its locked
        bool rv_system_lock_holder_is_locked
        (
        //pointer to struct
            struct rv_system_lock_holder_s     *t,
        //pointer to lock to add
            struct rv_system_lock_s            *l
        );
        typedef bool (* rv_system_lock_holder_is_locked_ptr)
        (
        //pointer to struct
            struct rv_system_lock_holder_s     *t,
        //pointer to lock to add
            struct rv_system_lock_s            *l
        );

    //rv_system_lock_holder_clear() clear all mutexes (will unlock them)
        void rv_system_lock_holder_clear
        (
        //pointer to struct
            struct rv_system_lock_holder_s     *t
        );
        typedef void (* rv_system_lock_holder_clear_ptr)
        (
        //pointer to struct
            struct rv_system_lock_holder_s     *t
        );

    //rv_system_lock_holder_lock() lock add mutexes
        bool rv_system_lock_holder_lock
        (
        //pointer to struct
            struct rv_system_lock_holder_s     *t,
        //wait forever if true
            bool                                is_blocking,
        //timeout in milliseconds
            uint64_t                            timeout_ms,
        //all must be locked to succeed
            bool                                fail_when_any_not_locked
        );
        typedef bool (* rv_system_lock_holder_lock_ptr)
        (
        //pointer to struct
            struct rv_system_lock_holder_s     *t,
        //wait forever if true
            bool                                is_blocking,
        //timeout in milliseconds
            uint64_t                            timeout_ms,
        //all must be locked to succeed
            bool                                fail_when_any_not_locked
        );

    //rv_system_lock_holder_unlock() unlock all mutexes
        void rv_system_lock_holder_unlock
        (
        //pointer to struct
            struct rv_system_lock_holder_s     *t
        );
        typedef void (* rv_system_lock_holder_unlock_ptr)
        (
        //pointer to struct
            struct rv_system_lock_holder_s     *t
        );

/* -- virtual method corresponding static function stubs --------------------- */

    //none

/* -------- structures containing easy function pointers --------------------- */

    //contains time struct methods
        struct rv_system_lock_holder_ptr_s
        {
        //create static
            rv_system_lock_holder_create_static_ptr     create_static;
        //destroy static
            rv_system_lock_holder_destroy_static_ptr    destroy_static;
        //add
            rv_system_lock_holder_add_ptr               add;
        //contains
            rv_system_lock_holder_contains_ptr          contains;
        //is_locked
            rv_system_lock_holder_is_locked_ptr         is_locked;
        //clear
            rv_system_lock_holder_clear_ptr             clear;
        //lock
            rv_system_lock_holder_lock_ptr              lock;
        //unlock
            rv_system_lock_holder_unlock_ptr            unlock;
        };
        struct rv_system_lock_holder_ptr_s rv_system_lock_holder;

//header guard end
    #endif


