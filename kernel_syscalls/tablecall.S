#define L(_Name) \
    .L##_Name

.macro PUBLIC name
    .global \name
.endm

.macro EXTERN name
    .extern \name
.endm

.macro WEAK name
    .weak \name
.endm

.macro ROUTINE_ENTRY name
    .section .text.\name
    .type \name, %function
    .balign 16
    \name:
.endm

.macro ROUTINE_END name
    .size \name, . - \name
.endm

.macro DATA_ENTRY name
    .section .data
    .type \name, %object
    \name:
.endm

.macro DATA_END name
    .size \name, . - \name
.endm


#define STATUS_INVALID_SYSTEM_SERVICE       0xC000004C


//
// This macro defines stub for service call
//

.macro DEFINE_CALL name index

    PUBLIC \name
    ROUTINE_ENTRY \name

        //
        // SysV x86-64 ABI defines that rax and r10 registers are temporary across function call.
        // Use it to pass system service number.
        //
        // Note that real intel syscall will place next instruction address after syscall in rcx,
        // along with rflags moved to r11. So we use r10 to pass rcx register in this stub.
        //

        movq        $\index, %rax
        movq        %rcx, %r10


        //
        // In real kernel, this would be just regular syscall / svc instruction. But here, we do
        // call to user mode function in order to emulate that behavior in host environment.
        //

        jmp        ke_dispatch_system_service


        //
        // Return from this stub.
        //

        retq

    ROUTINE_END \name

.endm


//
// Define handled system service stubs.
//

DEFINE_CALL         call_syscall_foobar     0
DEFINE_CALL         call_syscall_unknown    1

#define SYSTEM_CALLS_NUMBER 1



.macro SYSCALL_TABLE_ENTRY name
    .extern \name
    .quad \name
.endm

PUBLIC kep_system_service_table
DATA_ENTRY kep_system_service_table
    SYSCALL_TABLE_ENTRY syscall_foobar
DATA_END kep_system_service_table

PUBLIC ke_dispatch_system_service
ROUTINE_ENTRY ke_dispatch_system_service

    //
    // Check whether this service call is supported.
    // Note: this may be changed as mask+test to regular stub which will return fail status.
    //

    cmpq    $SYSTEM_CALLS_NUMBER, %rax


    //
    // This was invalid service call index - to failure area.
    //

    jae     1f


    //
    // Restore original argument passed in rcx.
    //

    movq    %r10, %rcx


    //
    // This was valid service call index - load address of dispatch table.
    //

    leaq    kep_system_service_table(%rip), %r10


    //
    // Jump to system service entry specified with service call index.
    //

    jmp    *(%r10,%rax,8)

1:
    //
    // Tried to invoke invalid system service. Report that to caller.
    //

    movq    $STATUS_INVALID_SYSTEM_SERVICE, %rax


    //
    // Return from dispatcher.
    //
    retq

ROUTINE_END ke_dispatch_system_service


//
// This stub initializes every entry in table which isn't supported.
//
// os_status_t svc_not_supported_system_service(void);
//

ROUTINE_ENTRY svc_not_supported_system_service

    //
    // Return status.
    //

    movq $STATUS_INVALID_SYSTEM_SERVICE, %rax

    retq

ROUTINE_END svc_not_supported_system_service
