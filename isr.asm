global isr0
extern interrupt_handler

section .text

isr0:

    push rax
    push rbx
    push rcx
    push rdx

    call interrupt_handler

    pop rdx
    pop rcx
    pop rbx
    pop rax

    iretq
