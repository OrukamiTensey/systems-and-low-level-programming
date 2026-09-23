%include "io.inc"
section .data
    A DW 217         ; Значення A
    B DW -89         ; Значення B
    result DW 0      ; Для результату

section .text
global main
main:
    mov ebp, esp     ; Для коректного дебагу

    ; Представимо A/B як 16-бітове число з фіксованою комою
    mov ax, [A]      ; Завантажуємо A в регістр AX
    cwd              ; Розширення знаку для 32-бітного ділення
    imul ax, 256     ; Множимо A на 256, щоб отримати значимі дроби
    idiv word [B]    ; AX = A * 256 / B, DX = A * 256 % B
    mov cx, ax       ; Зберігаємо результат A/B в CX (ціле число)

    ; Тепер множимо результат на 256 (для фіксованої коми)
    PRINT_STRING "A/B as fixed-point: "
    PRINT_DEC 1, cx
    NEWLINE

    ; Представимо B/A як 16-бітове число з фіксованою комою
    mov ax, [B]      ; Завантажуємо B в регістр AX
    cwd              ; Розширення знаку для 32-бітного ділення
    imul ax, 256     ; Множимо B на 256
    idiv word [A]    ; AX = B * 256 / A, DX = B * 256 % A
    mov bx, ax       ; Зберігаємо результат B/A в BX (ціле число)

    ; Тепер множимо результат на 256 (для фіксованої коми)
    PRINT_STRING "B/A as fixed-point: "
    PRINT_DEC 1, bx
    NEWLINE

    ; Тепер виконуємо додавання (A/B + B/A)
    add cx, bx       ; Додаємо A/B та B/A
    PRINT_STRING "Addition result (A/B + B/A): "
    PRINT_DEC 1, cx  ; Виводимо результат
    NEWLINE

    ; Тепер виконуємо множення (A/B * B/A)
    imul cx, bx      ; Множимо A/B на B/A (результат у CX)
    PRINT_STRING "Multiplication result (A/B * B/A): "
    PRINT_DEC 1, cx  ; Виводимо результат
    NEWLINE

    ; Завершення програми
    xor eax, eax     ; Очищуємо регістр EAX
    ret