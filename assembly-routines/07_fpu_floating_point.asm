section .data
    num1 dd 217.0         ; Перша константа
    num2 dd -89.0         ; Друга константа
    res_add dd 0.0        ; Результат додавання
    res_sub dd 0.0        ; Результат віднімання
    res_mul dd 0.0        ; Результат множення
    res_div dd 0.0        ; Результат ділення
    res_int dd 0          ; Результат перетворення у ціле число

section .text
global main
main:
    mov ebp, esp          ; Стандартна підготовка стеку
    xor eax, eax

    finit                 ; Ініціалізація FPU

    ; Додавання
    fld dword [num1]      ; Завантажуємо num1 у FPU
    fld dword [num2]      ; Завантажуємо num2 у FPU
    fadd                  ; num1 + num2
    fst dword [res_add]   ; Зберігаємо результат у пам'ять

    ; Віднімання
    fld dword [num1]      
    fld dword [num2]      
    fsub                  ; num1 - num2
    fst dword [res_sub]   

    ; Множення
    fld dword [num1]      
    fld dword [num2]      
    fmul                  ; num1 * num2
    fst dword [res_mul]   

    ; Ділення
    fld dword [num1]      
    fld dword [num2]      
    fdiv                  ; num1 / num2
    fst dword [res_div]   

    ; Перетворення типу (до цілого числа)
    fld dword [num1]      ; Завантажуємо num1 у FPU
    fist dword [res_int]  ; Перетворюємо у ціле число та зберігаємо у пам'ять

    ; Завершення програми
    mov eax, 1            
    xor ebx, ebx          
    int 0x80              
