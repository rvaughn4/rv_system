
/* ============================ rv_system_thread_task.h ===================================== //

    rv_system_thread_task.h

    represents what a thread will run

// ============================ rv_system_thread_task.h ===================================== */

//header guard begin
    #ifndef rv_system_SLASH_rv_system_thread_SLASH_rv_system_thread_task_DOT_h
    #define rv_system_SLASH_rv_system_thread_SLASH_rv_system_thread_task_DOT_h

/* ------------------- included headers --------------------------------------- */

    //standard int size types
        #include <stdint.h>
    //standard boolean type
        #include <stdbool.h>

/* ------------------- structure stubs --------------------------------------- */

    //task
        struct rv_system_thread_task_s;
    //object
        struct rv_system_object_ref_s;
        struct rv_system_object_writelock_s;
        struct rv_system_object_readlock_s;
    //thread
        struct rv_system_thread_ref_s;

/* ----------- virtual function/method stubs and typedefs -------------------- */

    //none

/* ------------------- structure definition ---------------------------------- */

    //function called by thread
        typedef bool (* rv_system_thread_task_run_readlock_ptr)
        (
        //pointer to task struct
            struct rv_system_thread_task_s          *tsk,
        //readlock
            struct rv_system_object_readlock_s      *l,
        //thread
            struct rv_system_thread_ref_s           *thd
        );

    //function called by thread
        typedef bool (* rv_system_thread_task_run_writelock_ptr)
        (
        //pointer to task struct
            struct rv_system_thread_task_s          *tsk,
        //readlock
            struct rv_system_object_writelock_s     *l,
        //thread
            struct rv_system_thread_ref_s           *thd
        );

    //task ran by thread
        struct rv_system_thread_task_s
        {
        //ref to object
            struct rv_system_object_ref_s               *rf;
        //function to call after ref is locked
            rv_system_thread_task_run_readlock_ptr      callback_readlock_optional;
        //function to call after ref is locked
            rv_system_thread_task_run_writelock_ptr     callback_writelock_optional;
        };

/* ------------------- static function stubs --------------------------------- */

    //none

/* -- virtual method corresponding static function stubs --------------------- */

    //none

/* -------- structures containing easy function pointers --------------------- */

    //none

//header guard end
    #endif



