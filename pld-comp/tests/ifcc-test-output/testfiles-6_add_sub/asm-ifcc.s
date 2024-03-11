.globl main
 main: 
    pushq %rbp
    movq %rsp, %rbp
    movl $10, -36(%rbp)
    movl -36(%rbp), %eax
    movl %eax, -32(%rbp)
    movl $10, -40(%rbp)
    movl -40(%rbp), %eax
    movl %eax, -16(%rbp)
    movl $5, -44(%rbp)
    movl -44(%rbp), %eax
    movl %eax, -20(%rbp)
    movl -32(%rbp), %eax
    addl -16(%rbp), %eax
    movl %eax, -48(%rbp)
    movl -48(%rbp), %eax
    addl -20(%rbp), %eax
    movl %eax, -52(%rbp)
    movl -16(%rbp), %eax
    addl -20(%rbp), %eax
    movl %eax, -56(%rbp)
    movl -56(%rbp), %eax
    addl -32(%rbp), %eax
    movl %eax, -60(%rbp)
    movl -52(%rbp), %eax
    subl -60(%rbp), %eax
    movl %eax, -64(%rbp)
    movl $10, -68(%rbp)
    movl -64(%rbp), %eax
    addl -68(%rbp), %eax
    movl %eax, -72(%rbp)
    movl $23, -76(%rbp)
    movl -72(%rbp), %eax
    subl -76(%rbp), %eax
    movl %eax, -80(%rbp)
    movl -80(%rbp), %eax
    addl -32(%rbp), %eax
    movl %eax, -84(%rbp)
    movl -84(%rbp), %eax
    movl %eax, -24(%rbp)
    movl -32(%rbp), %eax
    cltd
    idivl -20(%rbp)
    movl %eax, -88(%rbp)
    movl -88(%rbp), %eax
    imull -16(%rbp), %eax
    movl %eax, -92(%rbp)
    movl -32(%rbp), %eax
    imull -16(%rbp), %eax
    movl %eax, -96(%rbp)
    movl -96(%rbp), %eax
    cltd
    idivl -20(%rbp)
    movl %eax, -100(%rbp)
    movl -100(%rbp), %eax
    imull -32(%rbp), %eax
    movl %eax, -104(%rbp)
    movl -92(%rbp), %eax
    addl -104(%rbp), %eax
    movl %eax, -108(%rbp)
    movl -32(%rbp), %eax
    addl -16(%rbp), %eax
    movl %eax, -112(%rbp)
    movl -112(%rbp), %eax
    addl -20(%rbp), %eax
    movl %eax, -116(%rbp)
    movl -116(%rbp), %eax
    subl -24(%rbp), %eax
    movl %eax, -120(%rbp)
    movl -120(%rbp), %eax
    imull -32(%rbp), %eax
    movl %eax, -124(%rbp)
    movl -108(%rbp), %eax
    addl -124(%rbp), %eax
    movl %eax, -128(%rbp)
    movl -128(%rbp), %eax
    movl %eax, -28(%rbp)
    movl -28(%rbp), %eax
    popq %rbp
    ret
