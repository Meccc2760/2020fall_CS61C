

## Accumulator revisited
1. Reset signal: When `reset` is asserted, the register is forced to `0`, regardless of the adder output.
2. Accumulation relation: The register stores the previous partial sum $S_{i-1}$, while the adder computes the new value $S_i = S_{i-1} + X_i$.
3. Clock-to-Q delay (`t_clk-to-q`): After a clock edge, the register output does not change instantly; it takes a small amount of time before the new stored value appears at `Q`.
4. Adder delay (`t_add`): After $S_{i-1}$ or $X_i$ changes, the adder also needs some time before $S_i$ becomes stable.
5. Temporary instability is normal: $X_i$ and $S_{i-1}$ may arrive at slightly different times, so the adder output $S_i$ can temporarily be incorrect or unstable.
6. Correct sampling: As long as $S_i$ becomes stable before the next active clock edge, the register captures the correct value.
7. Timing principle: A synchronous circuit only requires signals to be stable around the clock edge when the register samples them; temporary changes between clock edges are acceptable.




| Term | Meaning | When / What it describes |
|---|---|---|
| **Clock (CLK)** | A steady square-wave signal used to synchronize the system. | Provides the reference timing for state updates. |
| **Setup Time** | The minimum time that the input must remain stable **before** the active clock edge. | Ensures the register/flip-flop can correctly sample the input. |
| **Hold Time** | The minimum time that the input must remain stable **after** the active clock edge. | Prevents the sampled value from changing too soon after capture. |
| **CLK-to-Q Delay** | The delay from the active clock edge until the new value appears at output `Q`. | After sampling at the rising edge, `Q` does not change instantly. |
| **Flip-Flop** | Stores **one bit** of state and samples its input on the active clock edge. | Basic 1-bit state-storage element. |
| **Register** | Stores **multiple bits** of state, typically built from multiple flip-flops. | Captures and holds multi-bit data across clock cycles. |