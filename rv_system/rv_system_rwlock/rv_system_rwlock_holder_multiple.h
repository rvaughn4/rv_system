
/* ============================ rv_system_rwlock_holder_multiple.h ===================================== //

    rv_system_rwlock_holder_multiple.h

    maintains the lifecycle of one or more rwlocks

// ============================ rv_system_rwlock_holder_multiple.h ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_rwlock_SLASH_rv_system_rwlock_holder_multiple_DOT_h
    #define rv_system_SLASH_rv_system_rwlock_SLASH_rv_system_rwlock_holder_multiple_DOT_h

/* ------------------- included headers --------------------------------------- */

    //header
        #include "rv_system_rwlock_holder.h"

/* ------------------- structure stubs --------------------------------------- */

    //handles ownership of mutex lock
        struct rv_system_rwlock_holder_multiple_s;

/* ----------- virtual function/method stubs and typedefs -------------------- */

    //none

/* ------------------- structure definition ---------------------------------- */

    //handles ownership of one or more locks on a mutex
        #define rv_system_rwlock_holder_multiple_entry_max 20
        struct rv_system_rwlock_holder_multiple_s
        {
        //super
            struct rv_system_rwlock_holder_s  super;
        //entries
            struct rv_system_rwlock_entry_s   entries[ rv_system_rwlock_holder_multiple_entry_max ];
        };

/* ------------------- static function stubs --------------------------------- */

    //rv_system_rwlock_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_rwlock_holder_multiple_create_static
        (
        //pointer to memory holding struct
            struct rv_system_rwlock_holder_multiple_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        );
        typedef bool (* rv_system_rwlock_holder_multiple_create_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_rwlock_holder_multiple_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        );

    //rv_system_rwlock_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_rwlock_holder_multiple_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_rwlock_holder_multiple_s     *t
        );
        typedef void (* rv_system_rwlock_holder_multiple_destroy_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_rwlock_holder_multiple_s     *t
        );

    //rv_system_rwlock_holder_add() add mutex to holder collection
        bool rv_system_rwlock_holder_multiple_add
        (
        //pointer to struct
            struct rv_system_rwlock_holder_multiple_s     *t,
        //pointer to lock to add
            struct rv_system_rwlock_s            *l,
        //locking mode, read or write
            bool                                is_write
        );
        typedef bool (* rv_system_rwlock_holder_multiple_add_ptr)
        (
        //pointer to struct
            struct rv_system_rwlock_holder_multiple_s     *t,
        //pointer to lock to add
            struct rv_system_rwlock_s            *l,
        //locking mode, read or write
            bool                                is_write
        );

    //rv_system_rwlock_holder_clear() clear all mutexes (will unlock them)
        void rv_system_rwlock_holder_multiple_clear
        (
        //pointer to struct
            struct rv_system_rwlock_holder_multiple_s     *t
        );
        typedef void (* rv_system_rwlock_holder_multiple_clear_ptr)
        (
        //pointer to struct
            struct rv_system_rwlock_holder_multiple_s     *t
        );

    //rv_system_rwlock_holder_lock() lock add mutexes
        bool rv_system_rwlock_holder_multiple_lock
        (
        //pointer to struct
            struct rv_system_rwlock_holder_multiple_s     *t,
        //wait forever if true
            bool                                is_blocking,
        //timeout in milliseconds
            uint64_t                            timeout_ms,
        //all must lock or fails, unlocks those that were locked
            bool                                all_must_lock_or_fail
        );
        typedef bool (* rv_system_rwlock_holder_multiple_lock_ptr)
        (
        //pointer to struct
            struct rv_system_rwlock_holder_multiple_s     *t,
        //wait forever if true
            bool                                is_blocking,
        //timeout in milliseconds
            uint64_t                            timeout_ms,
        //all must lock or fails, unlocks those that were locked
            bool                                all_must_lock_or_fail
        );

    //rv_system_rwlock_holder_unlock() unlock all mutexes
        void rv_system_rwlock_holder_multiple_unlock
        (
        //pointer to struct
            struct rv_system_rwlock_holder_multiple_s     *t
        );
        typedef void (* rv_system_rwlock_holder_multiple_unlock_ptr)
        (
        //pointer to struct
            struct rv_system_rwlock_holder_multiple_s     *t
        );

    //rv_system_rwlock_holder_multiple_contains() returns true if collection contains rwlock
        bool rv_system_rwlock_holder_multiple_contains
        (
        //pointer to struct
            struct rv_system_rwlock_holder_multiple_s     *t,
        //pointer to lock to add
            struct rv_system_rwlock_s            *l
        );
        typedef bool (* rv_system_rwlock_holder_multiple_contains_ptr)
        (
        //pointer to struct
            struct rv_system_rwlock_holder_multiple_s     *t,
        //pointer to lock to add
            struct rv_system_rwlock_s            *l
        );

    //rv_system_rwlock_holder_is_locked() returns true if rwlock is in the collection and locked
        bool rv_system_rwlock_holder_multiple_is_locked
        (
        //pointer to struct
            struct rv_system_rwlock_holder_multiple_s     *t,
        //pointer to lock to add
            struct rv_system_rwlock_s            *l
        );
        typedef bool (* rv_system_rwlock_holder_multiple_is_locked_ptr)
        (
        //pointer to struct
            struct rv_system_rwlock_holder_multiple_s     *t,
        //pointer to lock to add
            struct rv_system_rwlock_s            *l
        );

/* -- virtual method corresponding static function stubs --------------------- */

    //none

/* -------- structures containing easy function pointers --------------------- */

    //contains time struct methods
        struct rv_system_rwlock_holder_multiple_ptr_s
        {
        //create static
            rv_system_rwlock_holder_multiple_create_static_ptr     create_static;
        //destroy static
            rv_system_rwlock_holder_multiple_destroy_static_ptr    destroy_static;
        //add
            rv_system_rwlock_holder_multiple_add_ptr               add;
        //clear
            rv_system_rwlock_holder_multiple_clear_ptr             clear;
        //lock
            rv_system_rwlock_holder_multiple_lock_ptr              lock;
        //unlock
            rv_system_rwlock_holder_multiple_unlock_ptr            unlock;
        //contains
            rv_system_rwlock_holder_multiple_contains_ptr          contains;
        //is_locked
            rv_system_rwlock_holder_multiple_is_locked_ptr         is_locked;
        };
        struct rv_system_rwlock_holder_multiple_ptr_s rv_system_rwlock_holder_multiple;

//header guard end
    #endif




