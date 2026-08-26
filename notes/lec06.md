# Lec06: Binary Floating Point
## Basic
1. Representation of fractions:
    1. `Binary Point` like deciaml point, signifies boundary between integer and fraction parts
    2. e.g. $10.1010_2 = 1 \times 2^1 + 1\times 2^{-1} + 1\times 2^{-3} = 2.625$   
        -> 6bits float could represent 0-3.9375
2. Addition and multiplication: 
    - Addition:
        1. modify exponent
        2. add significand
        3. normalize
    - Multiplication:
        1. multiply significands
        2. add exponent
        3. nomalize

## FLoating point
1. the binary point if not fixed, but 'float'. we just need to keep track of the binary point.
2. Scientific notation: 
    - $1.01_2\times 2^{-1}$
    - $-1.1101_2\times 2^{8}$
    - which is: $-1^{sign}\times 1.significand_2\times 2^{exponent}$
3. 1bit: sign   
    8bit: exponent  
    23bit: significand  
    -> represent from $1.2\times 10^{-38}$ to $3.4\times 10^{38}$ for 32bit float   
4. If a number goes beyond $3.4\times 10^{38}$, it causes `overflow`    
    If a number is too small in $0~1.2\times 10^{-38}$,, it causes `underflow`

## Special numbers
1. In floating point, divided by 0 would produce $\pm\infty$, not overflow. when exponent is 255/8 1's and significand nonzero.
2. Two zeros: when exponent is 0 and significand is 0. so there would be $+0$ and $-0$, regarding $+\infty$ and $-\infty$.
3. if calculation wrong, it produces `NaN`: exponent is 255 and significand nonzero. hence for each significand, there exist corresponding `NaN`.
4. denormalized numbers：none-average accuracy
    - A gap between smallest representable FP number ($1.00..\times 2^{-126} = 2^{-126}$) and zero is $2^{-126}$
    - but the gap between the smallest and second smallest ($1.00..01 \times 2^{-126} = 2^{-126}+2^{-149}$) is $2^{-149}$ 
    - so there is 8million times different gap, causes great accuracy error.
    - Solution: when exponent is 0, assume its -126 and don't imply the leading `1`, so the smallest representable number would be: $0.00..01\times 2^{-126} = 2^{-149}$, the following would be $2^{-148}$, $2^{-147}$ ... $2^{-126}$ and normal number.
5. Summary:     
    |Exponent|Significand|Meaning|
    |-|-|-|
    |0|0|±0|
    |0|nonzero|Denormalized number|
    |1~254|anything|Normal floating point number|
    |255|0|±Infinity|
    |255|nonzero|NaN|