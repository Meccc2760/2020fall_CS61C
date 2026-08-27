# Lec08: RISC-V lw, sw, Decisions

## Store Data in memories
- Load from and store into memory, and processor do the processing.
- bit stored in little endian.

## Data transfer Instructions
1. Register are greatly faster than memory (500 times).

### Load Word
2. Instruction: `lw` (load words), which goes to memory and loads data to register.
- e.g. $lw\space x10, 12(x15)$, where $x10$ is destination, $x15$ is base register and $12$ is offset in bytes.
- If x15 stores `int`, then 12 bytes would be 4`int`s.
- Notice: in this case, $x15$ stores not value, but address, so that $12(x15)$ is an address in memory. $\iff x10 = memory[(x15 + 12)/ sizeof(type)-1]$

### Store Word
3. Instruction: `sw` (store word).
- e.g. $sw\space x10, 40(x15) \iff$ store $x10$ value to $x15 + 40$ memory.
- offset should be multiple of 4 to make bits aligned.

### Load&Store Byte
4. `load byte` and `store byte` has intruction: `lb` and `sb`, load or store the most significant byte in the given memory location.
- difference: `lw` and `lb` both have a destination address, `lb` only reads one byte, but `lw` reads the following 4 bytes.
- different instructions perform same functions, but different accuracy.
- we keep the highest bit of the value (sign representation) and extend it, so in a 32bit register, number $10110110$ would be $111...11\underbrace{10110110}_{origin}$.

## Decision Making
1. `If-statement` instruction: `beq` (branch if equal)
- e.g. $beq reg1, reg2, L1 \iff$ go to statement labeled $L1$ if (value in reg1) == (value reg2).
2. other branching instructions:
    - `beq`: branch if equal
    - `bne`: branch if not equal
    - `blt`: branch if less than
    - `bge`: branch if greater than or equal
    - `j`: jump, unconditionally jump to certain label statement.
3. Value comparison: `blt` and `bltu`(branch if less than)
- e.g. $blt reg1, reg2, L \iff$ go to L if (reg1 < reg2). 
- `bltu` compares unsigned int.
4. Loops: set a Label called `Loop`, and `j`(jump) to it at the end of the loop body. (programmer's design)
