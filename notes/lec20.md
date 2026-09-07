# Lec20: Single-Cycle CPU Control
## Control and Status Registers
1. `CSR`s(control and status registers) are separate from the register file(x0-x31):
    - Used for monitoring the status and performance.
    - There can be up to 4096 CSRs. (it has 12-bit address field)
2. Not in the base ISA, but almost mandatory in every implementation:
    - ISA is modular.
    - Necessary for counters and timers, and communication with peripherals.
3. CSR instructions: Similar to I-format.

    |csr|rs1|funct3|rd|opcode|
    |---|---|---|---|---|
    |12bit|5bit|3bit|5bit|7bit|
    |source/dest|source uim[4:0]|instr|rd|1110011|

4. Instruction: The `CSRRW`(atomic read/write CSR) instruction atomically swaps values in the CSRs and integer registers. `CSRRW` reads the previous value of the CSR and writes it to integer register `rd`, then writes `rs1` to CSR.
- e.g. $csrw\space csr, rs1 \iff csrrw\space x0, csr, rs1$  
    (rd=x0, which would not write CSR to x0, and just write rs1 to CSR)

## Control Datapath
1. Control Logic in a Single-Cycle CPU
    - The `control logic` decodes the current instruction and generates control signals that configure the datapath.
    - Basic flow: `Instruction bits → Control Logic → Control Signals → Datapath Components`
    - The control signals are physical wires connected to components such as MUXes, the ALU, the register file, and data memory.

2. Control Signals

    | Signal | Function |
    |---|---|
    | `PCSel` | Selects the next PC: usually `PC + 4` or a branch/jump target |
    | `ImmSel` | Selects how the instruction bits are interpreted to generate the immediate |
    | `RegWEn` | Enables writing a value into `rd` in the register file |
    | `BrUn` | Selects signed or unsigned comparison in the branch comparator |
    | `BrEq` | Indicates whether `Reg[rs1] == Reg[rs2]` |
    | `BrLT` | Indicates whether `Reg[rs1] < Reg[rs2]` |
    | `ASel` | Selects ALU input A, usually `Reg[rs1]` or `PC` |
    | `BSel` | Selects ALU input B, usually `Reg[rs2]` or an immediate |
    | `ALUSel` | Selects the ALU operation, such as add, subtract, AND, OR, shift, etc. |
    | `MemRW` | Controls whether data memory is read or written |
    | `WBSel` | Selects the value written back to `rd`, such as ALU result, memory data, or `PC + 4` |

    - `BrEq` and `BrLT` are slightly different from the others: they are outputs from the branch comparator and are fed back into the control logic to help decide `PCSel`.

- e.g. `add x5, x6, x7`, which is `Reg[x5] = Reg[x6] + Reg[x7]`. 
    - Typical control settings:

        | Signal | Setting |
        |---|---|
        | `PCSel` | `PC + 4` |
        | `RegWEn` | `1` |
        | `ASel` | `Reg[rs1]` |
        | `BSel` | `Reg[rs2]` |
        | `ALUSel` | `ADD` |
        | `MemRW` | unused |
        | `WBSel` | ALU result |

    - Control flow: `Instruction decode → read x6 and x7 → ALU adds them → WBSel selects ALU result → write result into x5 → PC becomes PC + 4`
    - Data memory and the immediate generator are not needed for this instruction.

- e.g. `lw x5, 8(x6)`, which is `Reg[x5] = Memory[Reg[x6] + 8]`.
    - Typical control settings:

        | Signal | Setting |
        |---|---|
        | `PCSel` | `PC + 4` |
        | `ImmSel` | I-type |
        | `RegWEn` | `1` |
        | `ASel` | `Reg[rs1]` |
        | `BSel` | immediate |
        | `ALUSel` | `ADD` |
        | `MemRW` | `READ` |
        | `WBSel` | memory data |

    - Control flow: `Instruction decode → read x6 → ImmGen generates 8 → ALU computes Reg[x6] + 8 → DMEM reads from that address → WBSel selects memory data → write data into x5 → PC becomes PC + 4`
    - Here the ALU result is not the final value. It is used as the **memory address**.

3. Timing and Hardware Behavior:
    - The control logic is usually implemented as `combinational hardware`. Instruction bits such as `opcode`, `funct3`, and `funct7` pass through decoding logic, which produces the control signals. These signals travel through physical wires to the corresponding hardware components.
    - In a single-cycle CPU, one instruction takes one clock cycle: `clock edge → instruction propagates through datapath → result becomes stable → next clock edge commits the result`.
    - The second clock edge is not a second cycle for the same instruction. It marks the end of the current cycle and the beginning of the next one.
    - At that edge, the current instruction may update the register file and PC. Immediately after the edge, the next instruction starts using the new state, so it can read a register value that was just written by the previous instruction.

## Instruction timing
1. Instruction Timing Periods

    | Stage | Main Work | Typical Hardware | Delay |
    |---|---|---|---:|
    | `IF` | Fetch the instruction using `PC` | Instruction Memory (`IMEM`) | `200 ps` |
    | `ID` | Decode instruction and read source registers | Control Logic + Register File | `100 ps` |
    | `EX` | Perform arithmetic / logic or calculate address | ALU | `200 ps` |
    | `MEM` | Read or write data memory | Data Memory (`DMEM`) | `200 ps` |
    | `WB` | Write the final result back to `rd` | Register File write port | `100 ps` |

    - For a `lw` instruction, the full path is: `IF → ID → EX → MEM → WB = 200 + 100 + 200 + 200 + 100 = 800 ps`.

2. Reading the Timing Diagram
    - The first diagram shows how a new instruction gradually propagates through the datapath during one clock cycle. The important idea is that when the clock edge arrives, only the state elements such as `PC` update immediately in the architectural sense; the new values then need time to pass through combinational hardware. Therefore, the instruction, register outputs, ALU result, and memory data become valid one after another rather than at the same instant.
    - The timing chain is: `clock edge → PC changes → after tIF instruction becomes valid → after tID register outputs become valid → after tEX ALU result becomes valid → after tMEM memory data becomes valid → after tWB the result is ready for write-back`.

- An ASCII version of the timing relationship looks like this:

    ```text
    time  ───────────────────────────────────────────────────────────────→

    Clock      ↑                                                     ↑
            |<---------------- one clock cycle ------------------->|

    PC         old ──X────────────── PC ──────────────────────────X── PC+4
                    ^
                    clock edge updates PC

    Instr.     old ─────────X──────── instruction ───────────────────────
                            |
                            |<-- tIF -->

    Reg output old ─────────────────X──── Reg[rs1], Reg[rs2] ──────────
                                    |
                                    |<-- tID -->

    ALU result old ─────────────────────────X──── ALU result ───────────
                                                |
                                                |<-- tEX -->

    Memory     old ───────────────────────────────────X── memory data ──
                                                        |
                                                        |<-- tMEM -->

    Writeback                                              |<-- tWB -->|
                                                                    ↑
                                                            next clock edge
    ```

    - The `X` regions mean the signal is transitioning and should not yet be treated as a stable valid value. For example, when `PC` changes, `IMEM` still temporarily outputs the old instruction; only after `tIF` does the new instruction become valid.

3. The Main Timing Principle
    - These delays accumulate because each stage depends on the previous one. For `lw`: `PC → IMEM → Register File → ALU → DMEM → Write Back`. The ALU cannot calculate the address before the registers are read, and DMEM cannot read memory before the ALU has produced the address.
    - That is why a single-cycle CPU must choose a clock period long enough for the slowest instruction path. In this example, `lw` needs about `800 ps`, so the clock period must be at least roughly `800 ps`, even though simpler instructions such as `add` may finish their useful computation earlier.

## Control Logic Design
1. Essential decode process/control logic can be designed as `read only memory`/`combinational logic`.
2. ROM: Look up the truth table of control words.
3. Combinational logic: Decodes instructions through boolean expressions.