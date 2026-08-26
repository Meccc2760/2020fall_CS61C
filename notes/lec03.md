# Lec03: C Introduction
## Compilation & Interpretation
1. C-compilers map C programs directly into architecture-specific machine code (1&0). For C, generally a two part process of compiling `.c files` to `.o files`(which is machine code), then linking `.o files` into excutables. (Assembling is also done but hidden)

2. Advantage:
    - Reasonable compilation time: enhancements in compilation procedure (`Makefiles`) allow only modified files to be recompiled.
    - Excellent run-time performance: generally much faster than scheme or Java for comparable code because it optimises for a given architecture.

3. Disadvantage:
    - Low portability: need to be re-compiled for different processor or system.
    - re-compile for each modification.

4. `Macro`: not actual functions, junst change the text of the program. (what `# define` do is just string replacement)

## C vs Java
- C is function oriented, Java is object oriented.

## C syntax
1. NULL/0
2. Typed variables
3. const & enum{}: make a group related to numbers
4. Typed functions
5. Struct