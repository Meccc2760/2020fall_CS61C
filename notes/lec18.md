


## R-type ADD Datapath
1. Sketch map:
    ```
                        +------+
                        | + 4  |
                        +--+---+
                        |
                        v
    +----+      +------+   |        +-------------+        +------+
    | PC | ---> | IMEM | --+------> | Register    | -----> | ALU  |
    +----+      +------+            | File        |        +--+---+
    ^                              +-------------+           |
    |                                     ^                 |
    |                                     |                 |
    +-------------------------------------+-----------------+
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