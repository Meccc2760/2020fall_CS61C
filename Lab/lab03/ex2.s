.globl main

.data
source:
    .word   3
    .word   1
    .word   4
    .word   1
    .word   5
    .word   9
    .word   0
dest:
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0

.text
fun:
    addi t0, a0, 1
    sub t1, x0, a0
    mul a0, t0, t1
    jr ra

main:
    # BEGIN PROLOGUE
    addi sp, sp, -20 # init stack for main
    sw s0, 0(sp) # sp would hold the address of s0-s3 and ra
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw ra, 16(sp)
    # END PROLOGUE
    addi t0, x0, 0 # t0 = 0
    addi s0, x0, 0 # s0 = 0
    la s1, source # s1 = &source
    la s2, dest # s2 = &dest
loop:
    slli s3, t0, 2 # s3 += t0*4
    add t1, s1, s3 # t1 = s1 + t0*4 (move next), t1 is an address
    lw t2, 0(t1) # t2 = *t1
    beq t2, x0, exit 
    add a0, x0, t2 # a0 = t2
    addi sp, sp, -8 # init stack for func
    sw t0, 0(sp)
    sw t2, 4(sp)
    jal fun
    lw t0, 0(sp) # clear func frame
    lw t2, 4(sp)
    addi sp, sp, 8 
    add t2, x0, a0 # t2 = a0 (new a0)
    add t3, s2, s3
    sw t2, 0(t3)
    add s0, s0, t2
    addi t0, t0, 1
    jal x0, loop
exit:
    add a0, x0, s0
    # BEGIN EPILOGUE
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw ra, 16(sp)
    addi sp, sp, 20
    # END EPILOGUE
    jr ra
