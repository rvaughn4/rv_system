
/* ============================ os_define.h ===================================== //

    os_define.h

    contains macro definitions that tell which operating system and hardware to compile for

// ============================ os_define.h ===================================== */

//header guard begin
    #ifndef os_define_DOT_h
    #define os_define_DOT_h

//include os_define.h from parent directory, only file that changes from system to system
//everything else is the same regardless of operating system or platform
//copy os and cpu sections into upper level os_define.h and uncomment the correct values for that system
    //#include "../os_define.h"

/* ------------------- operating system definitions --------------------------- //

    copy this into the base directory's os_define.h and uncomment out the correct value
    this defines determine which operating system you are compiling on

// ------------------- operating system definitions --------------------------- */

//windows 95, 98, me
    //#define rv_system_os_is_windows9x
//windows nt, 2000, xp, vista, 8, 10
    //#define rv_system_os_is_windowsnt
//linux ( kernel 2.0+ )
    #define rv_system_os_is_linux
//freebsd
    //#define rv_system_os_is_freebsd
//openbsd
    //#define rv_system_os_is_openbsd
//mac osx
    //#define rv_system_os_is_macosx

/* ------------------- cpu/hardware definitions --------------------------- //

    copy this into the base directory's os_define.h and uncomment out the correct value
    this defines determine which cpu you are compiling on

// ------------------- cpu/hardware definitions --------------------------- */

//amd64 based cpu
    #define rv_system_cpu_is_amd64
//intel386 based cpu
    //#define rv_system_cpu_is_intel386
//intel686 based cpu
    //#define rv_system_cpu_is_intel686
//arm64 based cpu
    //#define rv_system_cpu_is_arm64

//header guard end
    #endif

