# Lec11: Instruction Formats Ⅰ
## Instruction as Numbers
1. One word is 32 bits, so divide instruction into `fields`.
2. Each field tells the processor what the instruction is.

## R-Format Layout (Register)
1. 32 bit instruction word divided into six fields of varying numbers of bits.
2. `opcode`: operation code, partially specify the instruction.
3. `funct3`&`funct7`: respectively 3-bit and 7-bit, combined with opcode to describe what operation to perform.
4. `rd`, `rs1`, `rs2`: destination and source registers, each size 5 bit(0-31, to represent 32 registers).
- e.g. $add\space x18, x19, x10\rightarrow$
    |funct7|rs2|rs1|funct3|rd|opcode|
    |---|---|---|---|---|---|
    |0000000|01010|10011|000|10010|0110011|

## I-Format Layout (Immediate)
1. Replace funct7 and rs2 with 12-bit immediates itself.
2. Most funct3 code are teh same as R-format, like `add` and `addi`.

## RISC-V Loads
1. Load instruction is alse I-Format, with different opcodes.
2. `Offset` is deemed as an immediate, stored in the highest 12-bit space (used to be funct7 and rs2).

## S-Format Layout (Store)
1. Store read two registers, and immediate offset.
2. The immediate offset is split into 7 bits and 5 bits at high and low position.
- e.g. $sw\space x14, 8(x2)\rightarrow$ 
    |7-bit offset|rs2|rs1|funct3|5-bit offset|opcode|
    |---|---|---|---|---|---|
    |0000000|01110|00010|010|01000|0100011|