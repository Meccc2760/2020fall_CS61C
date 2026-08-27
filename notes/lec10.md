# Lec10: Procedures
## Stack
1. We need to save old values before calling function, restore them when return and delete.
2. We use `stack`: stack holds temporary values.
3. Stack is in memory, needs a register to point to it, which is `sp`(stack pointer), usually $x2$ register.
4. Each function has a set of data that needs to be put on stack, which is called `stack frame`, essentially a period of memory with special structure formats, assigned through moving `sp`. Stack frame includes:
    - return `instruction` address
    - parameters
    - space for other local variables
5. Stack pointer points to the bottom of the stack frame, and loads data from stack frame with `sp + offset`. When procedure ends, stack frame is tossed off the stack and frees memory for future stack frames, implemented by moving stack pointer backward.

## Register Conventions
1. Recursive Function Calls: only one place to store return address.
2. FUnction Caller can rely on values being unchanged: `sp`, `gp`, `tp`(pointers). But `a0`-`a7`, `ra` that stores temporary values would be changed.

## Memory Allocation
1. Allocating space on stack: `Procedure Frame` is a segment of stack with saved registers(ra, sp...) and local variables.
2. `sp` always points to the last used space in stack. To use stack, we decrement the pointer by the amount of space we need and fill it with information.
- e.g.  
    ```
    sumSquare:
        # push: create stack frame and save registers
        addi sp, sp, -8        # allocate 8 bytes on stack
        sw   ra, 4(sp)         # save return address
        sw   a1, 0(sp)         # save y

        mv   a1, a0            # prepare second argument: mul(x, x)
        jal  mul               # call mul(x, x)

        lw   a1, 0(sp)         # restore y
        add  a0, a0, a1        # result = mul(x, x) + y

        # pop: restore registers and stack
        lw   ra, 4(sp)         # restore return address
        addi sp, sp, 8         # deallocate stack space
        jr   ra                # return to caller
    ```

## Conclusion
- All instructions learned so far.
    ```
    # Arithmetic / Logic
    add  rd, rs1, rs2
    sub  rd, rs1, rs2
    and  rd, rs1, rs2
    or   rd, rs1, rs2
    xor  rd, rs1, rs2
    sll  rd, rs1, rs2
    srl  rd, rs1, rs2
    sra  rd, rs1, rs2

    # Immediate
    addi rd, rs1, imm
    subi rd, rs1, imm
    andi rd, rs1, imm
    ori  rd, rs1, imm
    xori rd, rs1, imm
    slli rd, rs1, imm
    srli rd, rs1, imm
    srai rd, rs1, imm

    # Load / Store
    lw   rd, offset(rs1)
    lb   rd, offset(rs1)
    lbu  rd, offset(rs1)
    sw   rs2, offset(rs1)
    sb   rs2, offset(rs1)

    # Branch / Jump
    beq  rs1, rs2, label
    bne  rs1, rs2, label
    bge  rs1, rs2, label
    blt  rs1, rs2, label
    bgeu rs1, rs2, label
    bltu rs1, rs2, label

    jal  rd, label
    jalr rd, rs1, imm
    ```