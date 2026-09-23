%include "io.inc"
section .data
   A EQU 217
   B EQU -89
section .text
global main
main:
    mov ebp, esp; for correct debugging
    mov eax, A
    shl eax, 1
    PRINT_STRING 'shl: '
    PRINT_DEC 1, eax
    NEWLINE
    
    mov eax, B
    shr eax, 1
    PRINT_STRING 'shr: '
    PRINT_DEC 1, eax
    NEWLINE
    
    xor eax, eax
    ret