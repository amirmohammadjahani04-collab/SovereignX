
global context_switch


section .text


context_switch:


    mov [rdi], rsp

    mov rsp, [rsi]


    ret


