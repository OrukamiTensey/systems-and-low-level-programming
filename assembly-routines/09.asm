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
    mov ebp, esp

    mov eax, arr1              
    mov ebx, arr2              
    mov edx, res_arr           
    mov ecx, size              

    call Merge_arrays

    mov ecx, 10               
    mov ebx, res_arr          
print_loop:
    mov ax, [ebx]              
    add ebx, 2                
    PRINT_DEC 1, ax            
    NEWLINE
    dec ecx                    
    jnz print_loop             

    ret                        
Merge_arrays:
    push ebp                   
    mov ebp, esp              

    mov esi, eax               
    mov edi, ebx               
    mov ebp, edx              
    mov ecx, size             
merge_loop:
    mov ax, [esi]              
    mov [ebp], ax             
    add esi, 2                 
    add ebp, 2                
    
    mov ax, [edi]             
    mov [ebp], ax              
    add edi, 2                
    add ebp, 2                 

    dec ecx                    
    jnz merge_loop             

    pop ebp                    
    ret                        