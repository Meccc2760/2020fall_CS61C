# Lec09: Decisions
## Logical Instructions
1. bitwise &: $and \space x1, x2, x3$
2. no `not` in RISC-V.
3. Shifts: `sll` (shift left logical), equals multiple $2^n$.
- e.g. $sll\space x11, x12, 2 \iff x11 = x12 << 2 \iff x11 = x12 \times 2^2$
4. Arithmetic shift: `sra` (shift right aarithmetic), moves `n` bits to right and insert high-order siign bit into empty bits

## Machine Program
1. Program Counter: `Program Counter` is a special register internal to the processor that holds btye address of next instruction to be executed.
2. Program executions are stored in memory. 
    - PC(program counter) fetch instruction, 
    - Control decode it, 
    - Register load/store data, 
    - ALU computes.
3. Features:
    1. Symbolic register names: 11th-17th register are named a0-a7 for function calls.
    2. Shorthand syntax: 
        - $mv\space rd\space rs \iff addi\space rd, rs, 0$, 
        - $nop \iff addi\space x0, x0, 0$, 
        - hence more readable

## Function Calls
1. Six Fundamental Steps in Calling Function:
    - pass arguments
    - transfer control to function
    - allocate local resources
    - execute function
    - save return value and store stage
    - return control to caller
2. All instrucions are stored in memory, sized 4 bytes.
3. Instruction: `jal`(jump and link), go to target function label, and store the address what originally was the next instruction to `ra`(a register spefically store `return address`, essentially a process holder). 
4. Instruction: `jr`(jump return), return to the address in `ra`.