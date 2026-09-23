%include "io.inc"

section .data
    arr1 dw 1, 3, 5, 7, 9
    arr2 dw 2, 4, 6, 8, 10
    size equ 5

section .bss
    res_arr resw 10
    start_low resd 1
    start_high resd 1
    end_low resd 1
    end_high resd 1

section .text
    global main

main:
    ; Початок замірів
    rdtsc
    mov dword [start_low], eax
    mov dword [start_high], edx

    ; Ініціалізація
    mov ebp, esp       ; Ініціалізація стеку для дебагу
    mov eax, arr1    
    mov ebx, arr2    
    mov edx, res_arr 
    mov ecx, size      ; Лічильник елементів
    
    ; Виклик функції злиття масивів
    call Merge_arrays
    
    ; Виведення результатів
    mov ecx, 10        ; Лічильник елементів масиву (10 елементів)
    mov ebx, res_arr 
print_loop:
    mov ax, [ebx]      ; Завантаження елемента
    add ebx, 2         ; Переходимо до наступного елементу
    PRINT_DEC 1, ax
    NEWLINE
    dec ecx            ; Зменшуємо лічильник
    jnz print_loop     ; Якщо є ще елементи, продовжуємо

    ; Кінець замірів
    rdtsc
    mov dword [end_low], eax
    mov dword [end_high], edx

    ; Виведення значень start_low, start_high, end_low, end_high
    PRINT_STRING "Start low: "
    mov eax, [start_low]
    PRINT_UDEC 1, eax
    NEWLINE

    PRINT_STRING "Start high: "
    mov eax, [start_high]
    PRINT_UDEC 1, eax
    NEWLINE

    PRINT_STRING "End low: "
    mov eax, [end_low]
    PRINT_UDEC 1, eax
    NEWLINE

    PRINT_STRING "End high: "
    mov eax, [end_high]
    PRINT_UDEC 1, eax
    NEWLINE

    ; Завершення програми
    ret

Merge_arrays:
    ; Ініціалізація
    mov esi, eax       ; Початок першого масиву
    mov edi, ebx       ; Початок другого масиву
    mov ebp, edx       ; Початок результуючого масиву
    mov ecx, size      ; Лічильник елементів у масивах
    
merge_loop:
    ; Додавання парного елемента з arr1 у res_arr
    mov ax, [esi]
    mov [ebp], ax
    add esi, 2
    add ebp, 2

    ; Додавання непарного елемента з arr2 у res_arr
    mov ax, [edi]
    mov [ebp], ax
    add edi, 2
    add ebp, 2

    ; Зменшення лічильника
    dec ecx
    jnz merge_loop

    ret