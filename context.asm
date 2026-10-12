global switch_context


section .text


switch_context:


    ; ذخیره Task فعلی

    mov [rdi+0],  r15
    mov [rdi+8],  r14
    mov [rdi+16], r13
    mov [rdi+24], r12

    mov [rdi+32], r11
    mov [rdi+40], r10
    mov [rdi+48], r9
    mov [rdi+56], r8

    mov [rdi+64], rsi
    mov [rdi+72], rdi

    mov [rdi+80], rbp
    mov [rdi+88], rdx
    mov [rdi+96], rcx
    mov [rdi+104],rbx
    mov [rdi+112],rax


    mov [rdi+120], rsp


    ; برگشت به Task جدید

    mov rsp,[rsi+120]

    mov r15,[rsi+0]
    mov r14,[rsi+8]
    mov r13,[rsi+16]
    mov r12,[rsi+24]

    mov rax,[rsi+112]

    ret

