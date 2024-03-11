.globl main
 main: 
    pushq %rbp
    movq %rsp, %rbp
    movl $10, -36(%rbp)
    movl -36(%rbp), %eax
    negl %eax
    movl %eax, -40(%rbp)
    movl -40(%rbp), %eax
    movl %eax, -32(%rbp)
    movl $10, -44(%rbp)
    movl -44(%rbp), %eax
    movl %eax, -16(%rbp)
    movl $5, -48(%rbp)
    movl -48(%rbp), %eax
    negl %eax
    movl %eax, -52(%rbp)
    movl -52(%rbp), %eax
    movl %eax, -20(%rbp)
    movl -32(%rbp), %eax
    negl %eax
    movl %eax, -56(%rbp)
    movl -56(%rbp), %eax
    addl -16(%rbp), %eax
    movl %eax, -60(%rbp)
    movl -20(%rbp), %eax
    negl %eax
    movl %eax, -64(%rbp)
    movl -60(%rbp), %eax
    addl -64(%rbp), %eax
    movl %eax, -68(%rbp)
    movl -16(%rbp), %eax
    addl -20(%rbp), %eax
    movl %eax, -72(%rbp)
    movl -72(%rbp), %eax
    addl -32(%rbp), %eax
    movl %eax, -76(%rbp)
    movl -68(%rbp), %eax
    subl -76(%rbp), %eax
    movl %eax, -80(%rbp)
    movl $10, -84(%rbp)
    movl -84(%rbp), %eax
    negl %eax
    movl %eax, -88(%rbp)
    movl -80(%rbp), %eax
    addl -88(%rbp), %eax
    movl %eax, -92(%rbp)
    movl $23, -96(%rbp)
    movl -92(%rbp), %eax
    subl -96(%rbp), %eax
    movl %eax, -100(%rbp)
    movl -100(%rbp), %eax
    addl -32(%rbp), %eax
    movl %eax, -104(%rbp)
    movl -104(%rbp), %eax
    movl %eax, -24(%rbp)
    movl -20(%rbp), %eax
    negl %eax
    movl %eax, -108(%rbp)
    movl -32(%rbp), %eax
    cltd
    idivl -108(%rbp)
    movl %eax, -112(%rbp)
    movl -112(%rbp), %eax
    imull -16(%rbp), %eax
    movl %eax, -116(%rbp)
    movl -32(%rbp), %eax
    imull -16(%rbp), %eax
    movl %eax, -120(%rbp)
    movl -120(%rbp), %eax
    cltd
    idivl -20(%rbp)
    movl %eax, -124(%rbp)
    movl -124(%rbp), %eax
    imull -32(%rbp), %eax
    movl %eax, -128(%rbp)
    movl -116(%rbp), %eax
    addl -128(%rbp), %eax
    movl %eax, -132(%rbp)
    movl -16(%rbp), %eax
    negl %eax
    movl %eax, -136(%rbp)
    movl -32(%rbp), %eax
    addl -136(%rbp), %eax
    movl %eax, -140(%rbp)
    movl -140(%rbp), %eax
    addl -20(%rbp), %eax
    movl %eax, -144(%rbp)
    movl -144(%rbp), %eax
    subl -24(%rbp), %eax
    movl %eax, -148(%rbp)
    movl -32(%rbp), %eax
    negl %eax
    movl %eax, -152(%rbp)
    movl -148(%rbp), %eax
    imull -152(%rbp), %eax
    movl %eax, -156(%rbp)
    movl -132(%rbp), %eax
    addl -156(%rbp), %eax
    movl %eax, -160(%rbp)
    movl -160(%rbp), %eax
    movl %eax, -28(%rbp)
    movl -28(%rbp), %eax
    popq %rbp
    ret
