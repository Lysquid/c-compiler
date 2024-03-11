.text # declaration of ’text’ section (which means ’program’)
.globl main # entry point to the ELF linker or loader.
main:
    # prologue
    pushq %rbp # save %rbp on the stack
    movq %rsp, %rbp # define %rbp for the current function

    # body
    movl $44, %eax

    # epilogue
    popq %rbp # restore %rbp from the stack
    ret # return to the caller (here the shell)
