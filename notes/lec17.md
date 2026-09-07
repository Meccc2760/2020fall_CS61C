# Lec17: Combinational Logic Blocks
## Data Multiplexors
1. `MUX`: Direct which lane of data could pass.
2. 1-bit-wide mux: $y = \bar{s}\cdot a + sb$, which is:
$$
\begin{array}{c|c}
a & y\\
\hline
0 & b\\
1 & \bar b
\end{array}
$$
3. 4-to-1 Mutiplexor: separate $s$ to $\overline{s_0s_1}$, and construct 2 layers of 1-bit mux.
$$
\begin{array}{c|c}
\overline{s_0s_1} & y\\
\hline
00 & a\\
01 & b\\
10 & c\\
11 & d\\
\end{array}
$$

## Arithmetic Logic Unit (ALU)
1. Most processors conatin a special logic block called `Alrithmetic and Logic Unit`.
2. Simple ALU:
```
                  A[31:0]        B[31:0]
                    |              |
          +---------+------+-------+---------+
          |                |                 |
          v                v                 v
   +-------------+      +------+          +------+
   | Add/Subtract|      | AND  |          |  OR  |
   +-------------+      +------+          +------+
          |                |                 |
          |                +------┐   ┌------+
          |                       v   v
          |                    +-------+
          |                    |  MUX  | <- S0
          |                    +-------+
          |                        |
          +-----------┐            |
                      v            v
                    +---------------+
                    |      MUX      | <- S1
                    +---------------+
                            |
                            v
                         R[31:0]
```

## Adder/Subtractor
1. 
$$
\begin{aligned}
&a_0 + b_0 = s_0 + c_0(carry)\\
\rightarrow &s_i = XOR(a_i, b_i, c_i)\\
&c_{i+1} = MAJ(a_i, b_i, c_i) = a_ib_i+a_ic_i+b_ic_i\\
\end{aligned}
$$
2. Parallel n 1-bit adder, then get a n-bit adder.
3. Sum of two 2-bit number may occur overflow:  
  - No $C_{out}$ or $C_{in}$: No overflow.
  - Both $C_{out}$ and $C_{in}$: No overflow.
  - Either $C_{out}$ or $C_{in}$: Occur overflow.
  - Conclusion: overflow = $C_{out}\space XOR\space C_{in}$ (the most and second highest carry).

## Subtractor Design
1. $A-B = A + (-B)$
2. To negate a 2's complement number: inverse each bit and add one.

## Conclusion
- Use muxes to select among input
- Can implement muxes hierarchically.
- ALU can be implemented using a mux
- N-bit adder-subtracotr done using N 1-bit adders with XOR gates on input.