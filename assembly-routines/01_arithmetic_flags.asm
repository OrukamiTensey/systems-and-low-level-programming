%include "io.inc"
section .data
    ; Оголошення констант
    A EQU 217 ; 16-бітне число
    B EQU -89 ; 16-бітне число

section .text
global main
main:    
    mov ebp, esp ; Зберігаємо стековий кадр для дебагу
    
     ; Ініціалізація регістрів
    mov ax, A    ; Завантажуємо A в регістр AX
    mov bx, B    ; Завантажуємо B в регістр BX
    
    add ax, bx  ; Додавання A + B, результат в AX
    PRINT_STRING 'add: -89 + 217 ='
    PRINT_DEC 1, ax
    NEWLINE
    
    mov ax, A   ; Завантажуємо A знову в AX
    mov bx, B   ; Завантажуємо B знову в BX
    adc ax, bx  ; Додавання з урахуванням прапора переносу
    PRINT_STRING 'adc: -89 + 217 ='
    PRINT_DEC 1, ax
    NEWLINE

    mov ax, A
    mov bx, B
    sub ax, bx  ; Віднімання A - B, результат в AX
    PRINT_STRING 'sub: -89 - 217 ='
    PRINT_DEC 1, ax
    NEWLINE
    
    mov ax, A
    mov bx, B
    sbb ax, bx  ; Віднімання з урахуванням прапора позики
    PRINT_STRING 'sbb: -89 - 217 ='
    PRINT_DEC 1, ax
    NEWLINE
    
    mov ax, A
    mov bx, B
    imul ax, bx ; Множення A * B, результат в AX
    PRINT_STRING 'imul: -89 * 217 ='
    PRINT_DEC 1, ax
    NEWLINE
    
    xor edx, edx ; Очищаємо регістр EDX, щоб підготувати до ділення
    mov ax, A
    cwd     ; Розширення знаку AX в DX:AX
    idiv bx     ; Ділення 32-бітного числа DX:AX на BX, результат в AX
    PRINT_STRING 'idiv: 217 / -89 ='
    PRINT_DEC 1, ax
    NEWLINE
    
    mov ax, A
    neg ax  ; Зміна знаку A
    PRINT_STRING 'neg A = '
    PRINT_DEC 1, ax
    NEWLINE
    
    mov ax, A
    inc ax  ; Інкремент (A + 1)
    PRINT_STRING 'inc A = '
    PRINT_DEC 1, ax
    NEWLINE
    
    mov ax, A
    dec ax  ; Декремент (A - 1)
    PRINT_STRING 'dec A = '
    PRINT_DEC 1, ax
    NEWLINE
    ; Завершення програми
    xor eax, eax   ; Очищаємо регістр EAX для завершення
    ret   ; Повернення з main
    
     