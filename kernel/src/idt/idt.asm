section .text
global interrupt_stub

interrupt_stub:
    cli
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    mov rdi, rsp
    call interrupt_dispatch
    mov rsp, rax

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    add rsp, 16
    sti
    iretq

extern interrupt_dispatch

; =============================
; Define macros for stubs
; =============================

%macro VECTOR_NOERR 1
    align 16
    global vector_%1_handler
vector_%1_handler:
    push 0          ; dummy error code
    push %1         ; vector number
    jmp interrupt_stub
%endmacro

%macro VECTOR_ERR 1
    align 16
    global vector_%1_handler
vector_%1_handler:
    push %1         ; vector number only (real error code already pushed)
    jmp interrupt_stub
%endmacro

; =============================
; Define first 32 entries
; =============================

VECTOR_NOERR 0
VECTOR_NOERR 1
VECTOR_NOERR 2
VECTOR_NOERR 3
VECTOR_NOERR 4
VECTOR_NOERR 5
VECTOR_NOERR 6
VECTOR_NOERR 7
VECTOR_ERR   8
VECTOR_NOERR 9
VECTOR_ERR  10
VECTOR_ERR  11
VECTOR_ERR  12
VECTOR_ERR  13
VECTOR_ERR  14
VECTOR_NOERR 15
VECTOR_NOERR 16
VECTOR_ERR  17
VECTOR_NOERR 18
VECTOR_NOERR 19
VECTOR_NOERR 20
VECTOR_NOERR 21
VECTOR_NOERR 22
VECTOR_NOERR 23
VECTOR_NOERR 24
VECTOR_NOERR 25
VECTOR_NOERR 26
VECTOR_NOERR 27
VECTOR_NOERR 28
VECTOR_NOERR 29
VECTOR_NOERR 30
VECTOR_NOERR 31

; =============================
; Auto-generate 32–255
; =============================

%assign i 32
%rep 224
    VECTOR_NOERR i
    %assign i i + 1
%endrep
