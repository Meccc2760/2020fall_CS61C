# Lec23: Pipelining Ⅲ
## Load Data Hazards
1. When we use `lw` to access data in MEM, the adjacent next instruction can not get the value by forwarding, because the value hasn't been stable at that time, unlike ALU in `add`. In this case, we have to stall.
2. All type of `load` instructions needs one cycle pipeline stall. But we won't know that is has to stall, until we have decoded the following instructions and knows it needs an output value. Hence we need a hardware to cancel the present instruction and postpone it to the next cycle.
3. Action:
    - Unable all relevant `Control Logic` to prevent reading new instructions and write/read reg/memory. Hence the present instructions would be repeated in the next cycle.
    - `Load delay slot`: to slot after a load. If the intruction uses the result of the load, then the hardware will stall for one cycle, which is equivalent to inseting an explicit `nop` in the slot. It will cause performance loss.
    - Idea: Put unrelated instruction into load delay slot.
    - e.g. Code scheduling to avoid stalls, done by compiler.

    ```risc-v
    # Original Order
    lw   t1, 0(t0)
    lw   t2, 4(t0)
    add  t3, t1, t2    # Stall: immediately uses t2 loaded by previous lw
    sw   t3, 12(t0)
    lw   t4, 8(t0)
    add  t5, t1, t4    # Stall: immediately uses t4 loaded by previous lw
    sw   t5, 16(t0)

    # Alternative
    lw   t1, 0(t0)
    lw   t2, 4(t0)
    lw   t4, 8(t0)     # Switched earlier to separate lw t2 from its dependent add
    add  t3, t1, t2
    sw   t3, 12(t0)
    add  t5, t1, t4
    sw   t5, 16(t0)
    ```

## Control Hazards
1. FOr a B-format instruction(branch), we don't know whether a branch is taken or not for two cycles, until it is determined by branch comparator.
    - Basic idea: stall for two cycles after branch.
2. Reduce Branch Penalties:
    - Every taken branch in simple pipeline costs 2 dead cycles.
    - To improve performance, use "branch prediction" to guess which way branch will go earlier in pipeline.
    - Only flush pipeline if branch prediction was incorrect.
    - Use a one-bit predictor to track whether the branch was taken last time or not.
　
## Superscalar Processors
1. Attempts on optimizing performance so far:
    1. Clock rate: limited by technology and power dissipatior.
    2. Pipelining:
        - Overlap instruction execution.
        - Deeper pipeline: shorter clock cycle, more potential for hazards.
2. SUperscalar processor:
    - Multiple issue `superscalar`:
        - Replicate pipeline stages
        - Start multiple instructions per clock cycle
        - CPI < 1
    - Out of order execution:
        - Reorder instructions dynamically in hardware to reduce impact of hazards.


