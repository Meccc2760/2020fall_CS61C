# Lec15: State & State Machines
## Accumulator
1. Uses of `State Elements`:
    - As a place to store values for some indeterminate amount of time:
        - `Register files`
        - `Memory`
    - Help control the flow of information between combinational logic blocks:
        - hold the movement of information at the inputs to combinational logic blocks and allow for orderly ussage.
2. Accumulator example: Use register to hold up the transfer of data to adder. Register is renewed at every clock edge and forward on to accumulation.

## Register Details: Flip-Flops
1. An n-bit register contains n instances of `Flip-flop`(FF), which earned its name from the behavior of flipping between 0 and 1.
2. `D` is data, `Q` is output. Here's `D-type flip-flop`.
3. Edge-triggered d-type flip-flop: 
    - On the rising edge of the clock, the input `d` is sampled and transferred to the output. At all other times, input `d` is ignored. So only clock edge and data together can generate output.
    - When input `d` is going to be loaded to register (a negative time before the rising clock edge), `d` should be stable.

## Accumulator revisited
1. Reset signal: When `reset` is asserted, the register is forced to `0`, regardless of the adder output.
2. Accumulation relation: The register stores the previous partial sum $S_{i-1}$, while the adder computes the new value $S_i = S_{i-1} + X_i$.
3. Clock-to-Q delay (`t_clk-to-q`): After a clock edge, the register output does not change instantly; it takes a small amount of time before the new stored value appears at `Q`.
4. Adder delay (`t_add`): After $S_{i-1}$ or $X_i$ changes, the adder also needs some time before $S_i$ becomes stable.
5. Temporary instability is normal: $X_i$ and $S_{i-1}$ may arrive at slightly different times, so the adder output $S_i$ can temporarily be incorrect or unstable.
6. Correct sampling: As long as $S_i$ becomes stable before the next active clock edge, the register captures the correct value.
7. Timing principle: A synchronous circuit only requires signals to be stable around the clock edge when the register samples them; temporary changes between clock edges are acceptable.

## Pipeline for performance
1. Maximum Clock Frequency: $Max Delay = CLK\text{-}to\text{-}Q\space Delay + Combinational\text{-}Logic\text{-}Delay + Setup\text{-}time$
2. Pipeline to improve performance:
    - Previous line: for the original `reg1 -> adder -> shifter -> reg2` line, a clock period must cover both adder and shifter's combinational-logic delay (to assure data flows from reg1 to reg2).
    - Insertation of regiser allows higher clock frequency: `reg1 -> adder -> reg2 -> shifter -> reg3`.
    - Hence the Max Delay is declined to a lower routine time of two neighbour registers.
3. Recapture of `Time Terms`:

    | Term | Meaning | When / What it describes |
    |---|---|---|
    | **Clock (CLK)** | A steady square-wave signal used to synchronize the system. | Provides the reference timing for state updates. |
    | **Setup Time** | The minimum time that the input must remain stable **before** the active clock edge. | Ensures the register/flip-flop can correctly sample the input. |
    | **Hold Time** | The minimum time that the input must remain stable **after** the active clock edge. | Prevents the sampled value from changing too soon after capture. |
    | **CLK-to-Q Delay** | The delay from the active clock edge until the new value appears at output `Q`. | After sampling at the rising edge, `Q` does not change instantly. |
    | **Flip-Flop** | Stores **one bit** of state and samples its input on the active clock edge. | Basic 1-bit state-storage element. |
    | **Register** | Stores **multiple bits** of state, typically built from multiple flip-flops. | Captures and holds multi-bit data across clock cycles. |

## Finite State Machines
1. Just... State machines.
2. Hardware implement of FSM:
    - A register is needed to hold the representation of which state the machine is in.
    - Combinational logic is used to implement a function, mapping the input and the presnet state input to the next state and output.