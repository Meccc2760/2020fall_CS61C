# Lec18: Single-Cycle CPU Datapath Ⅰ
## CPU Construction
- Processor: the active part of the computer that does all the work (data manipulation and decision making).
- Datapath: portion of the processor that contains hardware necessary to perform operations.
- Control: portion of the processor (also in hardware) that tells the datapath what needs to be controled.

## Building a RISC-V Processor
1. One-Instruction-Per-Cycle RISC-V Machine:
    - On every tick of the clock, the computer executes one instruction.
    - Current state outputs drive the inputs to the combinational logic, whose outputs settles at the values of the state before the next clock edge.
    - At the rising of the clock edge, all the state elements are updated with teh combinational logic outputs, and execution moves to the next clock cycle.
2. Stages of datapath:
    1. `Instruction Fetch`(IF)
    2. `Instruction Decode`(ID)
    3. `Execute`(EX)-ALU
    4. `Memory Access`(MEM)
    5. `Write Back to Reigster`(WB)
3. Datapath components:
    - Combinational blocks
    - Register: Write when `Write Enable` is asserted. Get updated at the rising edge of the clock.
    - Register file: Consists of 32 registers, together with read&write selection logic module.
        - Two 32-bit output buses: `busA` and `busB`.
        - One 32-bit input bus: `busW`.
        - RA selects the register to put on busA(data).
        - RB selects the register to put on busB(data).
        - RW selects the register to be written via busW(data) when `Write Enable` is 1.
    - Memory: 
        - One input bus: Data In.
        - One output bus: Data Out.
        - For read: Address selects the word to put on Data Out.
        - For write: Set `Write Enable` = 1, address selects the memory word to be written via the Data In bus.

4. Required States:
    - Register: Hold values
    - Program Counter: Hold address of current instruction.
    - Memory: Hold instructions and data, respectively `IMEM` and `DMEM`.

## R-type ADD Datapath
1. Sketch map: Use an `Adder` to move PC: +4 for each instruction in IMEM.
    ```
                +------+
                | + 4  |
                +--+---+
                |
                v
    +----+      +------+            +-------------+        +------+
    | PC | ---> | IMEM | --+------> | Register    | -----> | ALU  |
    +----+      +------+            | File        |        +--+---+
    ^                               +-------------+           |
    |                                     ^                   |
    |                                     |                   |
    +-------------------------------------+-------------------+
                            result / next state
    ```

2. For 32-bit instruction mapping into register file:
    ```
    PC
    → IMEM address
    → Inst[31:0]

    Inst[19:15] → rs1 → Register File → DataA
    Inst[24:20] → rs2 → Register File → DataB
    Inst[11:7]  → rd  → Register File write address

    DataA + DataB
    → ALU result
    → Register File write data

    PC + 4
    → next PC
    ```
- e.g. 
    ```
    PC
    → fetch instruction

    rs1 = x6
    rs2 = x7
    rd  = x5

    Reg[x6] ──┐
              ├─→ ALU(add) → Reg[x5]
    Reg[x7] ──┘

    PC → PC + 4
    ```

## Datapath with Immediates
1. Use a multiplexor to switch between immediate and reg2 value.
2. `Imm Gen` will read the 12-bit immediate value in the 32-bit instruction, and sign-extend it to 32-bit.