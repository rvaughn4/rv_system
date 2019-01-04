
/* ============================ rv_system_time.h ===================================== //

    rv_system_time.h

    wrapper for handling the querying of the epoch time and system tick count
    epoch time is the integer seconds elapsed since 1/1/1970
    tick count is the integer milliseconds elapsed since system boot

// ============================ rv_system_time.h ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_time_SLASH_rv_system_time_DOT_h
    #define rv_system_SLASH_rv_system_time_SLASH_rv_system_time_DOT_h

/* ------------------- included headers --------------------------------------- */

    //os and hw defines
        #include "../os_define.h"
    //standard int size types
        #include <stdint.h>
    //standard boolean type
        #include <stdbool.h>

/* ------------------- structure stubs --------------------------------------- */

    //used for querying time, contains time values
        struct rv_system_time_s;

/* ----------- virtual function/method stubs and typedefs -------------------- */

    //none

/* ------------------- structure definition ---------------------------------- */

    //used for querying time, contains time values
        struct rv_system_time_s
        {
        //epoch time since 1970 in seconds and milliseconds
            uint64_t    epoch_s, epoch_ms;
        //system tick count
            uint64_t    ticks_ms;
        };

/* ------------------- static function stubs --------------------------------- */

    //rv_system_time_create_static() initiates time struct in externally allocated memory
    //returns true when successful
        bool rv_system_time_create_static
        (
        //pointer to memory holding struct
            struct rv_system_time_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        );
        typedef bool (* rv_system_time_create_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_time_s     *t,
        //size of memory pointed to (must be equal or bigger than size of struct)
            uint64_t                    sz
        );

    //rv_system_time_destroy_static() releases resources in time struct in externally allocated memory
        void rv_system_time_destroy_static
        (
        //pointer to memory holding struct
            struct rv_system_time_s     *t
        );
        typedef void (* rv_system_time_destroy_static_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_time_s     *t
        );

    //rv_system_time_query() fetches time from system
    //returns true when successful
        bool rv_system_time_query
        (
        //pointer to memory holding struct
            struct rv_system_time_s    *t
        );
        typedef bool (* rv_system_time_query_ptr)
        (
        //pointer to memory holding struct
            struct rv_system_time_s    *t
        );

/* -- virtual method corresponding static function stubs --------------------- */

    //none

/* -------- structures containing easy function pointers --------------------- */

    //contains time struct methods
        struct rv_system_time_ptr_s
        {
        //create static
            rv_system_time_create_static_ptr    create_static;
        //destroy static
            rv_system_time_destroy_static_ptr   destroy_static;
        //query
            rv_system_time_query_ptr            query;
        };
        struct rv_system_time_ptr_s rv_system_time;

//header guard end
    #endif
