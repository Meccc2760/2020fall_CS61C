# Lec12: Instruction Formats Ⅱ
## B-Format Layout (Branch)
1. Branches read two registers but don't write. But we need to encode a `Label`.
2. Based on Program Counter to jump to label:
    1. If don't take branch, $PC = PC + 4$(next instruction).
    2. If do take branch, $Pc = PC + Immediate\times 2$(12-bit immediate), hence jump to the label.
3. The immediate offset is determined at compilation, because every `label` would be assigned unique address.
- e.g. $beq\space x19, x10, L(offset = 16bytes, 000000001000\underbrace{0}_{discarded})$
    |imm[12]|imm[10:5]|rs2|rs1|funct3|imm[4:1]|imm[11]|opcode|
    |---|---|---|---|---|---|---|---|
    |0|000000|01010|10011|000|1000|0|1100011|
4. The wierd layout of immediate in B-format, aims to hold a format similar with S-format as much as possible. Most bits are wired the same as S-format, because immediate in B-format is actually 13 bits with tail bit being default 0, not 12 bits.

## Long Immediates
1. U-Format: stands for Upper-Immediate, has 20-bit immediate in upper 20 bits of 32-bit instruction word, and store it in destination register.
    - e.g.  
        |imm[31:12]|rd|opcode|
        |---|---|---|
        |20 bit|5 bit|7 bit|
2. Instruction: `lui`, writes the upper 20-bits of the destination with the immediate value, and clears the lower 12 bits.
    - Together with `addi` to set lower 12 bits, can create any 32-bit value in a register using two instructions.
3. Instruction: `li`, pre-increment calue placed in upper 20 bits, if sign bit will be set on immediate in lower 12 bits, assembler will handle all these.
    - If $lower 12-bit \geq 0x800_{hex}$, it would be interpreted as negative, so increment the upper 20-bit by 1.
4. Instruction: `AUIPC`, adds upper immediate value to PC and places result in destination register. Used for PC-relative addressing.
    - $L: AUIPC\space x10, 0\iff x10 = current PC value + 0$, hence record the address of `label L`

## J-Format Layout (Jump)
1. `jal` saves $PC + 4$ in register `rd`.
    - |imm[20]|imm[10:1]|imm[11]|imm[19:12]|rd|opcode|
      |---|---|---|---|---|---|
      |1 bit|10 bit|1 bit|8 bit|5 bit|7 bit|
2. `j` which jumps to Label would set `rd` as `x0`, hence no return.
3. Call of Function: $jal\space ra, FuncName$, jumps to function and return to `ra` when function finishes.

## Conclusion
All Learned Formats with coresponding bit layouts:
| Type | `31:25` | `24:20` | `19:15` | `14:12` | `11:7` | `6:0` |
|---|---|---|---|---|---|---|
| **R-type** | `funct7` | `rs2` | `rs1` | `funct3` | `rd` | `opcode` |
| **I-type** | `imm[11:5]` | `imm[4:0]` | `rs1` | `funct3` | `rd` | `opcode` |
| **S-type** | `imm[11:5]` | `rs2` | `rs1` | `funct3` | `imm[4:0]` | `opcode` |
| **B-type** | `imm[12\|10:5]` | `rs2` | `rs1` | `funct3` | `imm[4:1\|11]` | `opcode` |
| **U-type** | `imm[31:12]` | colspan | colspan | colspan | `rd` | `opcode` |
| **J-type** | `imm[20\|10:1\|11\|19:12]` | colspan | colspan | colspan | `rd` | `opcode` |
