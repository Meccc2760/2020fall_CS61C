# Lec07: RISC-V Introduction
## Assembly Language
1. Basic job of CPU: execute `instructions`.
2. Instructions are primitive operations that the CPU may execute.
3. Different CPUs implements different sets of instructions. The set of instructions a particular CPU implement is an `Instruction Set Architecture`(ISA).
- e.g. ARM, x86, IBM-power, RISC-V
4. RISC-V Architecture: simple, elegant. don't want to get bogged down in gritty details.

## Element of Architecture: Register
1. Assenmbly cannot use variables (to keep hardware simple)
2. Assembly oprands are `register`s, which are limited number of special locations built directly into hardware. Hence it is incredibly fast to operate. Registers have no type.
3. Process read and write address from memory.
4. The number of registers is pre-determined. (32 registers in RISC-V, each 32-but wide)
5. Registers are numbered from 0-31, noted `x0`-`x31`. `x0` always holds value `0`.
6. Each line contains one instruction, and instructions are related to operations.

## RISC-V Add/Sub Instructions
1. Syntax of Instructions: "one two three four". Rigid syntax to keep hardware simple via regularity.
    - one: operation by name("add", "sub")
    - two: oprand getting result("destination")
    - three & four: 1st and 2nd oprand("source1", "source2")
    - e.g. $ add \space x1, x2, x3 \iff x1 = x2 + x3$

## RISC-V Immediates
1. `Immediate`s are numeral constants, instruction is `addi` (add immediate).
- e.g. $addi\space x2, x1, 10 \iff x2 = x1 + 10$
2. `x0` is hard-wired to value 0, so can be used as immediates:     
    $addi\space x2, x1, x0 \iff x2 = x1 + x0 \iff x2 = x1 + 0$
3. immediates can't be destinations. $add \space x0, x1, x2$ would do nothing.