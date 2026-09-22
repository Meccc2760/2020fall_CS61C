# Lec21: Pipelining Ⅰ
## Pipelining 
1. Idea: Performance measurement & Improvement.
2. Instruction timing: only `lw` goes through the 5 phases of delay.
3. Performance measurement: Maximum time of a single cycle is `800ps`, where CPU executes at `1.25 GHz`.
4. Computer analog:
    - Program execution time: trip time
    - Throughput: time for 100 passengers
    - Energy per tast: gallons per passenger

## Processor Performance Iron Law
1. Law: $\frac{Time}{Program} = \frac{Instruction}{Program}\cdot \frac{Cycles}{Instruction} \cdot \frac{Time}{Cycle}$
-  Number of instructions per program is determined by: Task, Algorithm choice(time complexity), Program language, Compiler, Instruction Set Architecture(ISA).
- Clock cycles per instruction(`CPI`) is determined by: ISA, Processor implementation(single-cycle(CPI=1)/complex-instruction(CPI>1)/superscalar-processor(CPI<1)).
- Time per cycle is determined by: Processor microarchitecture, Technology, Power budget (which are mainly hardware capacity).

## Energy Efficiency
1. Energy flow in CMOS structure: Energy may leak or dissipate while charging.
2. Formula: $\frac{Energy}{Program} = \frac{Instruction}{Program}\cdot \frac{Energy}{Instruction}$
3. Transferred from boosting CPU frequency to developing better processor architecture, multi-core and specialized processor.
4. $Performance = Power\times Energy\space Efficiency$:
    - Energy efficiency is key metric in all computing devices
    - For power-constrained systems, need better energy efficiency to get more performance at same power and prolong battery life.

## Introduction to Pipeline
1. Intro:
    - Pipelining doesn't help latency of single tasks, it helps throughput of entire workload.
    - Multiple tasks operating simultaneously using different resources.
    - Potential speedup = Number of pipe stages.
    - Time to fill pipeline and time to drain it reduces speedup.
2. Pipeline rate is limited by slowest pipeline stage (bottleneck).