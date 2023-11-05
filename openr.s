.globl openr
.type openr, @function

openr:
    # System call number for open
    movq $2, %rax  # sys_open

    # First argument: pathname (already in %rdi)
    # No need to move it.

    # Second argument: flags
    movq $0, %rsi  # O_RDONLY

    # Invoke syscall
    syscall

    # Return the result
    ret
