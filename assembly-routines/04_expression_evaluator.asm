%include "io.inc"
section .data
    A DW 217     ; Значення A (217)
    B DW -89     ; Значення B (-89)
    result DW 0  ; Результат для C

section .text
global main
main:
    mov ebp, esp ; Для коректного дебагу

    ; Ініціалізація змінних
    mov ax, [A]   ; Завантажуємо A в AX
    mov bx, [B]   ; Завантажуємо B в BX

    ; Обчислення A / B
    cwd           ; Розширення знака для ділення (розширює AX у DX:AX для ділення)
    idiv bx       ; AX = A / B, DX = A % B
    mov cx, ax    ; Зберігаємо результат (A / B) в CX

    ; Обчислення (A % B) * (A % B)
    mov ax, dx    ; Завантажуємо A % B в AX (DX містить залишок після ділення)
    imul ax, dx   ; AX = (A % B) * (A % B)
    mov bx, 3     ; Завантажуємо 3 в BX
    cwd           ; Підготовка для ділення на 3 (розширює AX у DX:AX)
    idiv bx       ; AX = ((A % B) * (A % B)) / 3
    add cx, ax    ; Додаємо результат до (A / B)

    ; Обчислення A * B
    mov ax, [A]   ; Завантажуємо A в AX
    imul bx, ax   ; BX = A * B
    sub cx, bx    ; Віднімаємо (A * B) від результату

    ; Лівий зсув на 2 біта (<< 2)
    shl cx, 2     ; Зсуваємо результат вліво на 2 біти

    ; Збереження результату
    mov [result], cx

    ; Виведення результату
    PRINT_STRING 'Result C = '
    PRINT_DEC 1, cx  ; Виведення результату C
    NEWLINE

    ; Завершення програми
    xor eax, eax    ; Очищуємо регістр EAX
    ret