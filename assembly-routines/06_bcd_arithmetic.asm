%include "io.inc"
section .data
    A DB 25          ; Значення A (BCD - 0x25)
    B DB 19          ; Значення B (BCD - 0x19)
    result DB 0      

section .text
global main
main:
    mov ebp, esp     ; Для коректного дебагу

    ; Перший варіант: Додавання двійково-десяткових чисел без корекції
    mov al, [A]      ; Завантажуємо A в AL
    add al, [B]      ; Додаємо B до AL (AL = 25 + 19)
    PRINT_STRING "Addition without correction (A + B): "
    PRINT_DEC 1, al  ; Виводимо результат
    NEWLINE

    ; Додавання з корекцією (DAA)
    mov al, [A]      ; Завантажуємо A в AL
    add al, [B]      ; Додаємо B до AL (AL = 25 + 19)
    daa              ; Корекція результату у BCD
    PRINT_STRING "Addition with DAA (A + B): "
    PRINT_DEC 1, al  ; Виводимо коригований результат
    NEWLINE

    ; Тепер виконаємо віднімання без корекції
    mov al, [A]      ; Завантажуємо A в AL
    sub al, [B]      ; Віднімаємо B від A (AL = 25 - 19)
    PRINT_STRING "Subtraction without correction (A - B): "
    PRINT_DEC 1, al  ; Виводимо результат
    NEWLINE

    ; Віднімання з корекцією (DAS)
    mov al, [A]      ; Завантажуємо A в AL
    sub al, [B]      ; Віднімаємо B від A (AL = 25 - 19)
    das              ; Корекція результату у BCD
    PRINT_STRING "Subtraction with DAS (A - B): "
    PRINT_DEC 1, al  ; Виводимо коригований результат
    NEWLINE

    ; Завершення програми
    xor eax, eax     ; Очищуємо регістр EAX
    ret