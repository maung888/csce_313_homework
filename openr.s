.section .data

.section .text
.global openr

openr:
    
    mov $2, %rax            
    mov $0, %rsi           
    xor %rdx, %rdx          
    syscall                
    ret
