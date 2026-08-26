# Lec02: Number Representation
## Data input
- real world is analog, so we sample it, then quantize it.

## Big IDEA: Bits can represent everything
- characters: 
    - 26 letters -> 5bits (2^5 = 32)
    - ASCII -> upper/lower case + punction, 7 bits
    - Unicode
- logical value: 0&1
- color&location&memorize

## Number expression
### Decimals: Base 10
- digits: 0, 1, ..., 8, 9
- e.g.: 3271 = $3271_{10}$
### Binary: Base 2
- digits: 0, 1
- e.g.: $1101_{2}$ = 1 + 4 + 8 = 13
### Hexadecimal: Base 16
- digits: 0, 1, 2, ..., 9, A, B, C, D, E, F
- e.g.: $A5_{16}$ = 5 + 10 * 16 = 165
- algorithm: 
    1. hex->decimal:
    ```C
    void dec2hex(unsigned int val, char *buf) {
        // `buf` is used to store result, needed to be defined ahead and passed in.
        static const char hex_table[] = "0123456789ABCDEF";
        
        char *p = buf + 8; 
        *p = '\0'; 

        do {
            *(--p) = hex_table[val & 0x0F]; 
            val >>= 4;                  
        } while (val > 0);

        char *src = p;
        while ((*buf++ = *src++));
    }
    ```
    2. hex <-> binary:  
    for binary bits, every four digits compose a group, called a `nibble`, and each nibble has a responding hex digit (because 2^4 = 16). if binary strings is not a multiple of 4, left-pad it to fill $0$ on the left side of the string to make it 4-dividable.

- Implementation: color representation:   
    `#D0A528` is an `RGB` code, which means red takes D0, green takes A5, blue takes 28. it turns out a bit yellow.

### Auto conversion 
```C
printf("0x4d2 = %d(hex)\n", 0x4d2);
printf("0b10011010010 = %d(binary)\n", 0b10011010010);
printf("02322 = %d(octal)\n", 02322);
```
### Complement
- leading 0 -> positive; leading 1 -> negative 
- for unsigned int, e.g.`1101` which is `13`, flip all bits to `0010` then add 1, so get `0011` which is `3`, a complement in `16`(all four bits)
- algorithm would be: flip bitwise, then plus 1.

## Summary
- we represent things in computers as particular bit patterns: N bits -> $2^N$ things
- 5 interger encodings, 3 important:
    - unsigned int
    - two's complement
    - bias