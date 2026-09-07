# Lec19: Single-Cycle CPU Datapath Ⅱ
## Supporting Loads
1. For instructions like $lw\space x5, 8(x6)$, the address in DMEN is also computed by ALU through simple `reg[x6]+8`, and send the result to DMEM accessor.
2. DMEM has the ability to access, read&write data with a given address.

## Datapath for Stores
1. Just need a 5-bit mux to select between two positions where low five bits of immediate can reside in instruction. Other bits in immediate care wired to fixed positions in instruction.
2. For a 12-bit immediate doing immGen, its `imm[11:5]` are fixed to `inst[31:25]`, but its `imm[4:0]` will alter between `inst[24:20]`(I-type, immediate) and `inst[11:7]`(S-type, store).

## Implementing Branches
1. Need to compute `PC+imm` and compare `rs1` and `rs2`, but there's only one ALU.
2. A new hardware: `Branch Comparator`, it accepts the values of reg1 and reg2, then output their equality relation. Control logic decides `PC+4` or `branch target` according to the output.

## Add JALR to Datapath
1. Instruction: $JALR\space rd, rs, immediate$
2. Two changes to the state:
    - Writes `PC+4` to rd
    - Sets `PC = rs1 + immediate`
3. It needs a path to write the result of `PC+4` to rd.

## Adding JAL (J-format)
1. Two changes to the state:
    - `jal` saves `PC+4` in register `rd`
    - Set `PC = PC + offset`(PC-relative jump)
2. Target somewhere within $\pm 2^{19}$ locations, 2 bytes apart.
3. Immediate encodeing optimized similarly to branch instruction to reduce hardware cost.

## Adding U-types
1. Has 20-bit immediate in upper 20 bits of 32-bit instruction word.
2. One destination register `rd`.
3. Used for two instructions:
    - `lui`: load upper immediate
    - `auipc`: add upper immediate to PC

## Conclusion
1. We have designed a complete datapath:
    - Capable of executing all RISC-V instructions in one cycle path each.
    - Not all units used by all instructions.
2. 5 phases of execution:
    - `IF, ID, EX, MEM, WB`
    - Not all instructions are active in all phases.
3. Controller specifies how to execute instructions.