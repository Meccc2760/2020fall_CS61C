# Lec24: Caches Ⅰ
## Binary Prefix
1. For an exponent of 2, write the exponent as $10X+Y$, which is $2^{XY}$:

    | X | Binary Prefix | Approx. Decimal | Y | $2^Y$ |
    |---:|---|---:|---:|---:|
    | 0 | — | $10^0$ | 0 | $1$ |
    | 1 | Ki (kibi) | $\approx 10^3$ | 1 | $2$ |
    | 2 | Mi (mebi) | $\approx 10^6$ | 2 | $4$ |
    | 3 | Gi (gibi) | $\approx 10^9$ | 3 | $8$ |
    | 4 | Ti (tebi) | $\approx 10^{12}$ | 4 | $16$ |
    | 5 | Pi (pebi) | $\approx 10^{15}$ | 5 | $32$ |
    | 6 | Ei (exbi) | $\approx 10^{18}$ | 6 | $64$ |
    | 7 | Zi (zebi) | $\approx 10^{21}$ | 7 | $128$ |
    | 8 | Yi (yobi) | $\approx 10^{24}$ | 8 | $256$ |
    | — | — | — | 9 | $512$ |

- Example: $2^{34}=2^{30}\times2^4=16\text{ Gi}$
- General rule: $2^{10X+Y}=2^Y\times 2^{10X}$

## Library Analogy
1. Why are large memories slow:
    - Analogue with library: need round-trip to walk the stack and retrive the desired book.
2. The entire goal is to optimize the performance accessing memory.

## Memory Hierachy
1. Cache is a copy of a subset of main memory.
2. Cache is implemented with same IC processing technology as the CPU.
3. Most processors have separate caches for instructions and data.
4. Memory hierachy represents the processor an illusion that it has as much memory as is available in the cheapest technology at the speed offered by the fastest technology.

## Locality, Design, Management
1. Memory hierachy basis:
    - Cache contains copies of data in memory that are being used.
    - Memory contains copies of data on disk that are being used.
    - Caches work on the principles of temporal and spatial locality.
2. Locality of Cache:
    - `Temporal locality`: if a memory location is referenced then it will tend to be referenced again soon.
    - `Spatial locality`: if a memory location is referenced, the lications with nearby addresses will tend to be referenced soon.
3. Cache Design and Hierachy Management:
    - register <-> memory: By compiler or assembly level programmer.
    - cache <-> main memory: By the cache controller hardware.
    - main memory <-> disks: By the operating system(virtual memory).