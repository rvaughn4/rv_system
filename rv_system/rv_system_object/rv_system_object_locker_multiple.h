
/* ============================ rv_system_object_locker_multiple.h ===================================== //

    rv_system_object_locker_multiple.h

    maintains the lifecycle of one or more rwlocked objects

// ============================ rv_system_object_locker_multiple.h ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_object_SLASH_rv_system_object_locker_multiple_DOT_h
    #define rv_system_SLASH_rv_system_object_SLASH_rv_system_object_locker_multiple_DOT_h

/* ------------------- included headers --------------------------------------- */

    //include super
        #include "rv_system_object_locker.h"
        #include "../rv_system_rwlock/rv_system_rwlock_holder_multiple.h"

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
        struct rv_system_object_locker_multiple_s;

/* ----------- virtual function/method stubs and typedefs -------------------- */

    //none

/* ------------------- structure definition ---------------------------------- */

    //handles locking objects
        #define rv_system_object_locker_multiple_entry_max 20
        struct rv_system_object_locker_multiple_s
        {
        //super
            struct rv_system_object_locker_s  super;
        //lock holder
            struct rv_system_rwlock_holder_multiple_s    slh;
        //entries
            struct rv_system_object_entry_s   entries[ rv_system_object_locker_multiple_entry_max ];
        };

/* ------------------- static function stubs --------------------------------- */

    //rv_system_object_locker_multiple_create_static() initiates struct in externally allocated memory
    //returns true when successful
        bool rv_system_object_locker_multiple_create_static
        (
        //pointer to memory holding struct
            struct rv_system_object_locker_multiple_s    *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                                     sz
        );
        typedef bool (* rv_system_object_locker_multiple_create_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_object_locker_multiple_s    *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                                     sz
        );

    //rv_system_object_locker_multiple_destroy_static() releases resources in struct in externally allocated memory
        void rv_system_object_locker_multiple_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_object_locker_multiple_s     *t
        );
        typedef void (* rv_system_object_locker_multiple_destroy_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_object_locker_multiple_s     *t
        );

    //rv_system_object_locker_multiple_add() add rwlock to holder collection
        bool rv_system_object_locker_multiple_add
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s           *t,
        //pointer to object to add
            struct rv_system_object_base_s                      *o,
        //pointer to lock to add (optional)
            struct rv_system_object_base_s                      **l_optional,
        //type of locking to perform, read or write
            bool                                                is_write
        );
        typedef bool (* rv_system_object_locker_multiple_add_ptr)
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s           *t,
        //pointer to object to add
            struct rv_system_object_base_s                      *o,
        //pointer to lock to add (optional)
            struct rv_system_object_base_s                      **l_optional,
        //type of locking to perform, read or write
            bool                                                is_write
        );

    //rv_system_object_locker_multiple_add_read() add rwlock to holder collection
        bool rv_system_object_locker_multiple_add_read
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s           *t,
        //pointer to object to add
            struct rv_system_object_base_s                      *o,
        //pointer to lock to add (optional)
            struct rv_system_object_readlock_s                  **l_optional
        );
        typedef bool (* rv_system_object_locker_multiple_add_read_ptr)
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s           *t,
        //pointer to object to add
            struct rv_system_object_base_s                      *o,
        //pointer to lock to add (optional)
            struct rv_system_object_readlock_s                  **l_optional
        );

    //rv_system_object_locker_multiple_add_write() add rwlock to holder collection
        bool rv_system_object_locker_multiple_add_write
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s           *t,
        //pointer to object to add
            struct rv_system_object_base_s                      *o,
        //pointer to lock to add (optional)
            struct rv_system_object_writelock_s                  **l_optional
        );
        typedef bool (* rv_system_object_locker_multiple_add_write_ptr)
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s           *t,
        //pointer to object to add
            struct rv_system_object_base_s                      *o,
        //pointer to lock to add (optional)
            struct rv_system_object_writelock_s                  **l_optional
        );

    //rv_system_object_locker_multiple_clear() clear all mutexes (will unlock them)
        void rv_system_object_locker_multiple_clear
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s     *t
        );
        typedef void (* rv_system_object_locker_multiple_clear_ptr)
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s     *t
        );

    //rv_system_object_locker_multiple_lock() lock add mutexes
        bool rv_system_object_locker_multiple_lock
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s       *t,
        //wait forever if true
            bool                                            is_blocking,
        //timeout in milliseconds
            uint64_t                                        timeout_ms,
        //all must be locked or else fail and unlock those already locked
            bool                                            all_must_lock_or_fail
        );
        typedef bool (* rv_system_object_locker_multiple_lock_ptr)
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s       *t,
        //wait forever if true
            bool                                            is_blocking,
        //timeout in milliseconds
            uint64_t                                        timeout_ms,
        //all must be locked or else fail and unlock those already locked
            bool                                            all_must_lock_or_fail
        );

    //rv_system_object_locker_multiple_unlock() unlock all mutexes
        void rv_system_object_locker_multiple_unlock
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s     *t
        );
        typedef void (* rv_system_object_locker_multiple_unlock_ptr)
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s     *t
        );

    //rv_system_object_locker_multiple_contains() returns true if collection contains object
        bool rv_system_object_locker_multiple_contains
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s       *t,
        //pointer to object to test
            struct rv_system_object_base_s                  *o
        );
        typedef bool (* rv_system_object_locker_multiple_contains_ptr)
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s       *t,
        //pointer to object to test
            struct rv_system_object_base_s                  *o
        );

    //rv_system_object_locker_multiple_is_locked() returns true if object is in the collection and locked
        bool rv_system_object_locker_multiple_is_locked
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s       *t,
        //pointer to lock to test
            struct rv_system_object_base_s                  *o
        );
        typedef bool (* rv_system_object_locker_multiple_is_locked_ptr)
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s       *t,
        //pointer to object to test
            struct rv_system_object_base_s                  *o
        );

    //rv_system_object_locker_multiple_get_locked() returns true if object is in the collection and locked,
    //      fetches pointer to lock of specified type
        bool rv_system_object_locker_multiple_get_locked
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s       *t,
        //pointer to object to test
            struct rv_system_object_base_s                  *o,
        //type of lock to fetch
            char                                            *ctype,
        //pointer to receive pointer to lock
            void                                            **pl
        );
        typedef bool (* rv_system_object_locker_multiple_get_locked_ptr)
        (
        //pointer to struct
            struct rv_system_object_locker_multiple_s       *t,
        //pointer to object to test
            struct rv_system_object_base_s                  *o,
        //type of lock to fetch
            char                                            *ctype,
        //pointer to receive pointer to lock
            void                                            **pl
        );

/* -- virtual method corresponding static function stubs --------------------- */

    //none

/* -------- structures containing easy function pointers --------------------- */

    //contains struct methods
        struct rv_system_object_locker_multiple_ptr_s
        {
        //create static
            rv_system_object_locker_multiple_create_static_ptr     create_static;
        //destroy static
            rv_system_object_locker_multiple_destroy_static_ptr    destroy_static;
        //add
            rv_system_object_locker_multiple_add_ptr               add;
        //add_read
            rv_system_object_locker_multiple_add_read_ptr          add_read;
        //add_write
            rv_system_object_locker_multiple_add_write_ptr         add_write;
        //clear
            rv_system_object_locker_multiple_clear_ptr             clear;
        //lock
            rv_system_object_locker_multiple_lock_ptr              lock;
        //unlock
            rv_system_object_locker_multiple_unlock_ptr            unlock;
        //contains
            rv_system_object_locker_multiple_contains_ptr          contains;
        //is_locked
            rv_system_object_locker_multiple_is_locked_ptr         is_locked;
        };
        struct rv_system_object_locker_multiple_ptr_s rv_system_object_locker_multiple;

//header guard end
    #endif





