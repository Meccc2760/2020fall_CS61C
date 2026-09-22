# Lec22: Pipelining Ⅱ
## Pipelining RISC-V
1. Single-cycle: Instruction Fetch -> Reg Read -> ALU -> MEN Access -> Reg Write
2. FOr an instruction sequence, insert `pipeline register`s into every two stages, to hold output of each stage.
3. We set clock frequency slower to match the longet single stage, hence we lose the latency of single instruction, but dramatically gain higher throughput.
4. Comparison: sequential for a single instruction, and simultaneous for a series of instructions flowing through pipeline.

    | Structure | Single Cycle | Pipelined |
    |---|---|---|
    | Timing | `t_step = 100 ~ 200 ps` | `t_cycle = 200 ps` |
    | Feature | Register access only `100 ps` | All cycles same length |
    | Instruction time, `t_instruction` | `= t_cycle = 800 ps` | `1000 ps` |
    | CPI (Cycles Per Instruction) | `~1` (ideal) | `~1` (ideal), `<1` (actual) |
    | Clock rate, `f_s` | `1 / 800 ps = 1.25 GHz` | `1 / 200 ps = 5 GHz` |
    | Relative speed | `1×` | `4×` |

## Pipeline Hazards
1. A hazard is a situation that prevents starting the next instruction in the net clock cycle.
    - `Structual hazard`: a required resource is busy.
    - `Data hazard`: data has dependency relation among them, and need to wait for previous instructions to complete its data read/write.
    - `Control hazard`: Flow of execution depends on previous instruction.
2. Structual Hazard:
    - Problem: Two or more instructions in the pipeline compete for access to a single physical resource.
    - Solution1: Instructions take it in turns to use resource, some instructions have to stall.
    - Solution2: Add more hardware to machine, which can always solve a structure hazard.
- `Regfile Structual Hazards`:
    - Each instruction can read up to two oprands in decode stage, and can write one value in writeback stage.
    - Avoid structual hazard by having separate `ports`: two independent read ports and one independent write port. 
    - Three accesses per cycle can happen simultaneously.
- `Memory Structual Hazards`:
    - Compete for the access to hardware memory.
    - Solution: use `cache` which is fast, on-chip memory, separated for instructions for instructions and data.
- Structual Hazards Conclusion:
    - Conflict for using a resource.
    - In RISC-V pipeline with a single memory:
        - `load`&`store` requires data access.
        - without separate memories, instruction fetch would have to stall for that cycle.
    - Pipelined datapaths require separate instruction/data memories/caches.

## Pipelining Datapath
1. Insert registers into pipeline datapath.

```text
          IF                ID                 EX                 MA                 WB
   ┌────────────┐    ┌────────────┐    ┌────────────┐    ┌────────────┐    ┌────────────┐
PC→│   IMEM     │ →  │ Register   │ →  │   ALU /    │ →  │   DMEM     │ →  │ Register   │
   │ fetch inst │    │ File + Imm │    │ Branch Comp│    │  access    │    │ write back │
   └────────────┘    └────────────┘    └────────────┘    └────────────┘    └────────────┘
                  │                  │                 │                 │
                  │                  │                 │                 │
              ┌───────┐          ┌───────┐         ┌───────┐         ┌───────┐
              │ IF/ID │          │ ID/EX │         │ EX/MA │         │ MA/WB │
              │  Reg  │          │  Reg  │         │  Reg  │         │  Reg  │
              └───────┘          └───────┘         └───────┘         └───────┘
```
2. Pipeline control (in Control Logic)
    - Control signals derived from instruction:
        - As in single-cycle implementation.
        - information is stored in pipeline registers for use by later stages.
    - Control bits stored in pipeline registers and carried forward.

```text
instruction
    │
    ▼
 Control
    │
    ├──── EX control ───────► used in EX
    │
    ├──── MA control ───────► carried ─► used in MA
    │
    └──── WB control ───────► carried ─► carried ─► used in WB


        ID/EX             EX/MA             MA/WB
      ┌────────┐        ┌────────┐        ┌────────┐
      │ EX     │        │        │        │        │
      │ MA     │ ─────► │ MA     │ ─────► │        │
      │ WB     │        │ WB     │ ─────► │ WB     │
      └────────┘        └────────┘        └────────┘
```

## Data Hazards
1. Register Access:
    - In an 200ps clock cycle, the pipeline register enable write from the previous combinational logic output in the first half period, and in the remaining 100ps, it allows read from the next component.
    - Hence the next combinational logic can read the correct new value generated from previous line.
    - However, when a dependent instruction needs a result before it has been written back to register file(not pipeline reg), data hazard occurs.
    - `Forwarding` solves this by sending the result directly from a latter pipeline stage to the consumer.
2. Solution
    1. Stalling:
        - Problem: Instruction depends on result from previous instruction.
        - e.g.
        ```text
        add s0, t0, t1
        sub t2, s0, t3 # `s0` needs to be computed by `add` 
        ```
        - Action: Insert two `bubble` instructions (doing nothing) into the two instructions. `Bubble` helps align the register `write-back` stage with `reg-read` stage.
        - Drawback: Stalls reduce performance. Compilers would arrange the order instruction to make best effort to avoid stalls.
    2. Forwarding:
        - Transimit (Bypass) the desired value directly from its generating place to the wating input.
        - Requires extra connections in the datapath.
        - Forward from the producer which is nearest to consumer.