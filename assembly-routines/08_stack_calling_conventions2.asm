%include "io.inc"
section .data
    arr1 dw 1, 3, 5, 7, 9
    arr2 dw 2, 4, 6, 8, 10
    size equ 5

section .bss
    res_arr resw 10

section .text
    global main
main:
    mov ebp, esp   ; Ініціалізація стеку для дебагу
    
    mov eax, arr1    
    mov ebx, arr2    
    mov edx, res_arr 
    
    mov ecx, size   ; Лічильник елементів
    
    call Merge_arrays
    
    mov ecx, 10    ; Лічильник елементів масиву (10 елементів)
    mov ebx, res_arr 
    print_loop:
    
    mov al, [ebx]          
    add ebx, 2   ; Переходимо до наступного елементу масиву

    PRINT_DEC 1, al
    NEWLINE

    dec ecx                
    jnz print_loop 
    
    ret
Merge_arrays:   
    mov esi, eax                
    mov edi, ebx                
    mov ebp, edx                
    
    mov ecx, size  ; Лічильник елементів в масивах
    
    merge_loop:
    ; Записуємо парний елемент з arr1 в res_arr
    mov ax, [esi]               
    mov [ebp], ax               
    add esi, 2                  
    add ebp, 2                  

    ; Записуємо непарний елемент з arr2 в res_arr
    mov ax, [edi]               
    mov [ebp], ax               
    add edi, 2                  
    add ebp, 2                  

    dec ecx   ; Зменшуємо лічильник
    jnz merge_loop  ; Якщо ще є елементи, повторюємо

    ret
    

   
    