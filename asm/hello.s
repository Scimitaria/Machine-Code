.global _main
.align 4

_main:
    // 1. Setup system call for write (syscall #4)
    mov x0, #1              // 1 = StdOut
    adr x1, hello_world     // Load address of our string
    mov x2, #13             // Length of the string
    mov x16, #4             // macOS 'write' system call
    svc #0x80               // Supervisor call to interrupt kernel

    // 2. Setup system call for exit (syscall #1)
    mov x0, #0              // Exit code 0 (Success)
    mov x16, #1             // macOS 'exit' system call
    svc #0x80               // Supervisor call

hello_world:
    .asciz "Hello, World!\n"
