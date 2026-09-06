# Lec13: Compiling, Assembling, Linking and Loading
## Interpretation and Translation
1. Difference on how to run code:
    - Interpreter: Directly executes a program in the source language.
    - Translator: Converts a program from the source language to an equivalent program in another language.

## Compiler
1. Input: High-level Language Code.
2. Output: Assembly Language Code.

## Assembler
1. Input: Assembly Language Code.
2. Output: Object Code, information table.
3. Process:
    - Reads and uses directives.
    - Replace Pseudo-instructions.
    - Produce Machine Language.
    - Create Object File.
4. Directives: Give directions to assembler, but don't produce machine code.
    | Directive | Description |
    | :--- | :--- |
    | `.text` | Subsequent items put in user text segment (machine code) |
    | `.data` | Subsequent items put in user data segment (source file data in binary) |
    | `.globl sym` | Declares `sym` global and can be referenced from other files |
    | `.string str` | Store the string `str` in memory and null-terminate it |
    | `.word w1...wn` | Store the $n$ 32-bit quantities in successive memory words |
5. Pseudo-Instruction Replacement:
    | Pseudo-instruction | Replacement |
    |---|---|
    | `mv t0, t1` | `addi t0, t1, 0` |
    | `neg t0, t1` | `sub t0, zero, t1` |
    | `li t0, imm` | `addi t0, zero, imm` |
    | `not t0, t1` | `xori t0, t1, -1` |
    | `beqz t0, loop` | `beq t0, zero, loop` |
    | `la t0, str` | `lui t0, str[31:12]` + `addi t0, t0, str[11:0]` |
    | `la t0, str` | `auipc t0, str[31:12]` + `addi t0, t0, str[11:0]` |
6. Produce Machine Code:
    - Take two passes over the program. First notes the labels, second compute all offsets and produces `Symbol Table` and `Relocation Table`, which are stored in `.o files`.
    - Symbol table contains function labels and their addresses and other information.
    - Relocation table stores the functions  whose addresses are not determined. The variables may be in other segments or files and need to be linked.

## Linker
1. Input: Object code files, Information tables.
2. Output: Executable code. Combines several object files into single executable.
3. Enable separate compilation of files. Changing one file do not require recompilation of whole program.
4. Four Types of Addresses:
    | Address Type | Typical Instructions | Main Idea | Relocation |
    |---|---|---|---|
    | **PC-Relative Addressing** | `beq`, `bne`, `jal`, `auipc + addi` | Target is represented as an offset from the current `PC`. If code moves as a whole, the relative distance stays the same. | Usually **no relocation needed** for local targets; supports PIC |
    | **Absolute Function Address** | `auipc + jalr` | Construct the address of a function and jump to it when a direct `jal` cannot encode the target directly. | **Relocation needed** |
    | **External Function Reference** | `auipc + jalr` | Call a function defined outside the current object file; its final address is unknown during assembly. | **Relocation needed** |
    | **Static Data Reference** | often `lui + addi` | Construct the address of global/static data whose final memory location is determined later. | **Relocation needed** |

## Loader
1. Input: Executable code.
2. Output: Running program.
3. Process:
    - Reads executable file's header to determine size of text and data segments.
    - Creates new address space for program large enough to hold text and data segments, along with a stack segment.
    - Copies instructions + data from executable files into the new address space.
    - Copies arguments passed to the program onto the stack.
    - Initializes machine registers.
    - Jumps to start-up routine that copies program's arguments from stack to registers and sets the PC.

## Example Process
C Source → Assembly → Object Code → Linked Executable

### C source: `Hello.c`

```c
#include <stdio.h>

int main()
{
    printf("Hello, %s\n", "world");
    return 0;
}
```
↓
### Compiled assembly: `Hello.s`

```asm
.text
.align 2
.globl main

main:
    addi sp, sp, -16
    sw   ra, 12(sp)

    lui  a0, %hi(string1)
    addi a0, a0, %lo(string1)

    lui  a1, %hi(string2)
    addi a1, a1, %lo(string2)

    call printf

    lw   ra, 12(sp)
    addi sp, sp, 16
    li   a0, 0
    ret

.section .rodata
.balign 4

string1:
    .string "Hello, %s\n"

string2:
    .string "world"
```

Here, `a0` receives the address of `"Hello, %s\n"` and `a1` receives the address of `"world"` according to the RISC-V calling convention.
↓
### Assembled object file: `Hello.o`

At this stage, addresses of static data and external functions are not fully known, so the assembler leaves placeholders and relocation information.

```asm
00000000 <main>:

0:   ff010113    addi  sp, sp, -16
4:   00112623    sw    ra, 12(sp)

8:   00000537    lui   a0, 0x0
c:   00050513    addi  a0, a0, 0

10:  000005b7    lui   a1, 0x0
14:  00058593    addi  a1, a1, 0

18:  00000097    auipc ra, 0x0
1c:  000080e7    jalr  ra

20:  00c12083    lw    ra, 12(sp)
24:  01010113    addi  sp, sp, 16
28:  00000513    addi  a0, a0, 0
2c:  00008067    jalr  zero, 0(ra)
```

The zero immediates are address placeholders. The object file also contains the symbol table and relocation table so the linker knows what must be fixed later.
↓
### Linked executable: `a.out`

After linking, the linker knows the final addresses of `string1`, `string2`, and `printf`, so it patches the corresponding instructions.

```asm
000101b0 <main>:

101b0: ff010113    addi  sp, sp, -16
101b4: 00112623    sw    ra, 12(sp)

101b8: 00021537    lui   a0, 0x21
101bc: a1050513    addi  a0, a0, -1520

101c0: 000215b7    lui   a1, 0x21
101c4: a1c58593    addi  a1, a1, -1508

101c8: 288000ef    jal   ra, 10450

101cc: 00c12083    lw    ra, 12(sp)
101d0: 01010113    addi  sp, sp, 16
101d4: 00000513    addi  a0, a0, 0
101d8: 00008067    jalr  zero, 0(ra)
```
### Compilation pipeline

`Hello.c` → **Compiler** → `Hello.s` → **Assembler** → `Hello.o` → **Linker** → `a.out`

The essential idea is that the compiler generates assembly, the assembler converts it into machine instructions while leaving unresolved addresses as placeholders, and the linker combines object files and libraries, resolves symbols, performs relocation, and produces the final executable.