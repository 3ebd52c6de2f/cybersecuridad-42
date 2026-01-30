BITS 64
DEFAULT REL

section .text
global _start
; default conf para x86_64

_start:

    ; guardar registros

    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11

    mov rdi, [rel + TEXT_ADDR]   ; buffer (initialPtr)
    mov rsi, [rel + TEXT_SIZE]   ; size
    mov rdx, [rel + KEY_ADDR]    ; key
    mov rcx, [rel + KEY_LEN]     ; keylen

    xor r8, r8                   ; i = 0

.init_s:
    cmp r8, 256
    je .ksa
    mov byte [s_array + r8], r8b
    inc r8
    jmp .init_s

.ksa:
    xor r8, r8                   ; i = 0
    xor r9, r9                   ; j = 0

.ksa_loop:

    ; loop de aplicacion de secretKey inverso

    cmp r8, 256
    je .prga
    mov al, [s_array + r8]
    add r9b, al

    mov rax, r8
    xor rdx, rdx
    div rcx
    mov bl, [KEY_ADDR + rdx]
    add r9b, bl

    mov al, [s_array + r8]
    mov bl, [s_array + r9]
    mov [s_array + r8], bl
    mov [s_array + r9], al

    inc r8
    jmp .ksa_loop

.prga:

    ; idx init

    xor r8, r8                   ; i = 0
    xor r9, r9                   ; j = 0
    xor r10, r10                 ; k = 0

.prga_loop:

    ; loop de decrypt

    cmp r10, rsi
    je .done

    inc r8
    mov al, [s_array + r8]
    add r9b, al

    mov al, [s_array + r8]
    mov bl, [s_array + r9]
    mov [s_array + r8], bl
    mov [s_array + r9], al

    mov al, [s_array + r8]
    add al, [s_array + r9]
    movzx rax, al
    mov bl, [s_array + rax]

    xor byte [rdi + r10], bl

    inc r10
    jmp .prga_loop

.done:
    
    ; printeo de ....WOODY....

    mov rax, 1
    mov rdi, 1
    lea rsi, [rel msg]
    mov rdx, msg_len
    syscall

    ; restaurar registros

    pop r11
    pop r10
    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    ; salto al entrypoint original

    mov rax, [OGENTRYPOINT]
    jmp rax

; variables

section .rodata
msg db "....WOODY....", 10
msg_len equ $ - msg

section .bss
s_array resb 256

section .data
TEXT_ADDR    dq 0xAAAAAAAAAAAAAAAA
TEXT_SIZE    dq 0xBBBBBBBBBBBBBBBB
KEY_ADDR     dq 0xCCCCCCCCCCCCCCCC
KEY_LEN      dq 0xDDDDDDDDDDDDDDDD
OGENTRYPOINT dq 0xEEEEEEEEEEEEEEEE

; flageadas para poder hardcodearlas