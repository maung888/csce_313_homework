.globl openr
.type openr, @function

openr:
    movq $2, %rax  # sys_open
    movq $0, %rsi  # O_RDONLY
    syscall
    ret
