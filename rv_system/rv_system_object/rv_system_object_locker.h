
/* ============================ rv_system_object_locker.h ===================================== //

    rv_system_object_locker.h

    maintains the lifecycle of one or more rwlocked objects

// ============================ rv_system_object_locker.h ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_object_SLASH_rv_system_object_locker_DOT_h
    #define rv_system_SLASH_rv_system_object_SLASH_rv_system_object_locker_DOT_h

/* ------------------- included headers --------------------------------------- */

    //standard int size types
        #include <stdint.h>
    //standard boolean type
        #include <stdbool.h>
    //rwlocker
        #include "../rv_system_rwlock/rv_system_rwlock_holder.h"

/* ------------------- structure stubs --------------------------------------- */

    //objects
        struct rv_system_object_s;
        struct rv_system_object_base_s;
        struct rv_system_object_ref_s;
        struct rv_system_object_readlock_s;
        struct rv_system_object_writelock_s;
    //entires of owned object locks
        struct rv_system_object_entry_s;
    //handles ownership of object lock
        struct rv_system_object_locker_s;

/* ----------- virtual function/method stubs and typedefs -------------------- */

    //none

/* ------------------- structure definition ---------------------------------- */

    //entires of owned locks
        struct rv_system_object_entry_s
        {
        //pointer to object
            struct rv_system_object_base_s *o;
        //lock status
            bool is_locked;
        //type of lock
            bool is_write;
        //pointer to lock
            struct rv_system_object_base_s *l, *d;
        };

    //handles locking objects
        struct rv_system_object_locker_s
        {
        //pointer to entries
            struct rv_system_object_entry_s     *entries;
        //first entry
            struct rv_system_object_entry_s     first_entry;
        //entry count
            uint8_t                             entry_cnt;
        //lock holder
            struct rv_system_rwlock_holder_s    *lh, slh;
        };

/* ------------------- static function stubs --------------------------------- */

    //rv_system_object_locker_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_object_locker_create_static
        (
        //pointer to memory holding struct
            struct rv_system_object_locker_s    *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                            sz
        );
        typedef bool (* rv_system_object_locker_create_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_object_locker_s    *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                            sz
        );

    //rv_system_object_locker_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_object_locker_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_object_locker_s     *t
        );
        typedef void (* rv_system_object_locker_destroy_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_object_locker_s     *t
        );

    //rv_system_object_locker_add() add rwlock to holder collection
        bool rv_system_object_locker_add
        (
        //pointer to struct
            struct rv_system_object_locker_s        *t,
        //pointer to object to add
            struct rv_system_object_base_s          *o,
        //pointer to lock to add (optional)
            struct rv_system_object_base_s          *l_optional,
        //type of locking to perform, read or write
            bool                                    is_write
        );
        typedef bool (* rv_system_object_locker_add_ptr)
        (
        //pointer to struct
            struct rv_system_object_locker_s        *t,
        //pointer to object to add
            struct rv_system_object_base_s          *o,
        //pointer to lock to add (optional)
            struct rv_system_object_base_s          *l_optional,
        //type of locking to perform, read or write
            bool                                    is_write
        );

    //rv_system_object_locker_clear() clear all mutexes (will unlock them)
        void rv_system_object_locker_clear
        (
        //pointer to struct
            struct rv_system_object_locker_s     *t
        );
        typedef void (* rv_system_object_locker_clear_ptr)
        (
        //pointer to struct
            struct rv_system_object_locker_s     *t
        );

    //rv_system_object_locker_lock() lock add mutexes
        bool rv_system_object_locker_lock
        (
        //pointer to struct
            struct rv_system_object_locker_s    *t,
        //wait forever if true
            bool                                is_blocking,
        //timeout in milliseconds
            uint64_t                            timeout_ms,
        //all must be locked or else fail and unlock those already locked
            bool                                all_must_lock_or_fail
        );
        typedef bool (* rv_system_object_locker_lock_ptr)
        (
        //pointer to struct
            struct rv_system_object_locker_s   *t,
        //wait forever if true
            bool                                is_blocking,
        //timeout in milliseconds
            uint64_t                            timeout_ms,
        //all must be locked or else fail and unlock those already locked
            bool                                all_must_lock_or_fail
        );

    //rv_system_object_locker_unlock() unlock all mutexes
        void rv_system_object_locker_unlock
        (
        //pointer to struct
            struct rv_system_object_locker_s     *t
        );
        typedef void (* rv_system_object_locker_unlock_ptr)
        (
        //pointer to struct
            struct rv_system_object_locker_s     *t
        );

    //rv_system_object_locker_contains() returns true if collection contains object
        bool rv_system_object_locker_contains
        (
        //pointer to struct
            struct rv_system_object_locker_s     *t,
        //pointer to object to test
            struct rv_system_object_base_s       *o
        );
        typedef bool (* rv_system_object_locker_contains_ptr)
        (
        //pointer to struct
            struct rv_system_object_locker_s     *t,
        //pointer to object to test
            struct rv_system_object_base_s       *o
        );

    //rv_system_object_locker_is_locked() returns true if object is in the collection and locked
        bool rv_system_object_locker_is_locked
        (
        //pointer to struct
            struct rv_system_object_locker_s     *t,
        //pointer to lock to test
            struct rv_system_object_base_s       *o
        );
        typedef bool (* rv_system_object_locker_is_locked_ptr)
        (
        //pointer to struct
            struct rv_system_object_locker_s     *t,
        //pointer to object to test
            struct rv_system_object_base_s       *o
        );

    //rv_system_object_locker_get_locked() returns true if object is in the collection and locked,
    //      fetches pointer to lock of specified type
        bool rv_system_object_locker_get_locked
        (
        //pointer to struct
            struct rv_system_object_locker_s     *t,
        //pointer to object to test
            struct rv_system_object_base_s       *o,
        //type of lock to fetch
            char                                 *ctype,
        //pointer to receive pointer to lock
            void                                 **pl
        );
        typedef bool (* rv_system_object_locker_get_locked_ptr)
        (
        //pointer to struct
            struct rv_system_object_locker_s     *t,
        //pointer to object to test
            struct rv_system_object_base_s       *o,
        //type of lock to fetch
            char                                 *ctype,
        //pointer to receive pointer to lock
            void                                 **pl
        );

/* -- virtual method corresponding static function stubs --------------------- */

    //none

/* -------- structures containing easy function pointers --------------------- */

    //contains struct methods
        struct rv_system_object_locker_ptr_s
        {
        //create static
            rv_system_object_locker_create_static_ptr     create_static;
        //destroy static
            rv_system_object_locker_destroy_static_ptr    destroy_static;
        //add
            rv_system_object_locker_add_ptr               add;
        //clear
            rv_system_object_locker_clear_ptr             clear;
        //lock
            rv_system_object_locker_lock_ptr              lock;
        //unlock
            rv_system_object_locker_unlock_ptr            unlock;
        //contains
            rv_system_object_locker_contains_ptr          contains;
        //is_locked
            rv_system_object_locker_is_locked_ptr         is_locked;
        };
        struct rv_system_object_locker_ptr_s rv_system_object_locker;

//header guard end
    #endif




