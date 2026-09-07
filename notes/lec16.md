# Lec16: Combinational Logic
## Truth Tables
1. iff one:
$$
\begin{array}{c|c|c}
a & b & y\\
\hline
0 & 0 & 0\\
0 & 1 & 1\\
1 & 0 & 1\\
1 & 1 & 0
\end{array}
\qquad\Longleftrightarrow\qquad
\begin{array}{c|c}
a & y\\
\hline
0 & b\\
1 & \bar b
\end{array}
$$

2. 2-bit adder: 16 outputs.

## Logic Gates
- `AND`, `OR`, `NOT` gates, proceed 0 and 1 inputs.
- `XOR`: output true when $a\neq b$ (counting the number of `1`s, true when it's odd).
- `NAND`: output true unless $a = b = 1$.
- `NOR`: output true when $a = b =0$.

## Boolean Algebra
- `AND`: $\cdot$
- `OR`: +
- `NOT`: $\bar{x}$
- e.g. $y = a\cdot b + a + c \iff a\cdot (b+1)+c = a\cdot 1 + c = a+c$

- Laws of Boolean Algebra

    | Law | AND form | OR form |
    |---|---|---|
    | Complementarity | $x\cdot\bar{x}=0$ | $x+\bar{x}=1$ |
    | Laws of 0's and 1's | $x\cdot0=0$ | $x+1=1$ |
    | Identities | $x\cdot1=x$ | $x+0=x$ |
    | Idempotent Law | $x\cdot x=x$ | $x+x=x$ |
    | Commutative Law | $x\cdot y=y\cdot x$ | $x+y=y+x$ |
    | Associativity | $(xy)z=x(yz)$ | $(x+y)+z=x+(y+z)$ |
    | Distribution | $x(y+z)=xy+xz$ | $x+yz=(x+y)(x+z)$ |
    | Uniting Theorem | $xy+x=x$ | $(x+y)x=x$ |
    | DeMorgan's Law | $\overline{x\cdot y}=\bar{x}+\bar{y}$ | $\overline{(x+y)}=\bar{x}\cdot\bar{y}$ |

## Conclusion
- Pipeline big-delay Combinational Logic for faster clock frequency.
- Finite State Machine extremely useful.
- Use the boolean algrebra table to tranform `1` to other expressions.