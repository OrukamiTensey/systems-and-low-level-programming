%include "io.inc"
section .data
    ; Оголошення констант
    A EQU 217        ; 16-бітне число (11011001)
    B EQU -89        ; 16-бітне число (11111001)
    C EQU 50         ; 16-бітне число (50)
    D EQU 100        ; 16-бітне число (100)

section .text
global main
main:
    mov ebp, esp; for correct debugging
    mov ax, A        ; Завантажуємо A в регістр AX
    mov bx, B        ; Завантажуємо B в регістр BX
    mov cx, C        ; Завантажуємо C в регістр CX
    mov dx, D        ; Завантажуємо D в регістр DX
    
    ; Виконання операції AND
    and ax, bx       ; AX = A AND B
    PRINT_STRING 'AND (A AND B): '
    PRINT_DEC 1, ax  ; Виведення результату AND
    NEWLINE

    ; Виконання операції OR
    mov ax, A        ; Завантажуємо A знову в AX
    or ax, cx        ; AX = A OR C
    PRINT_STRING 'OR (A OR C): '
    PRINT_DEC 1, ax  ; Виведення результату OR
    NEWLINE

    ; Виконання операції XOR
    mov ax, A        ; Завантажуємо A знову в AX
    xor ax, dx       ; AX = A XOR D
    PRINT_STRING 'XOR (A XOR D): '
    PRINT_DEC 1, ax  ; Виведення результату XOR
    NEWLINE

    ; Завершення програми
    xor eax, eax     ; Завершуємо програму
    ret