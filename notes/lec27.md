# Lec27: Caches Ⅳ
## Set-Associative Cache
1. N-way Set Associative Cache:
    1. For memory address field: same tag and offset, the index points to the correct row.
    2. Each set contains multiple blocks, once we find corect set, must compare with all tags in the set to confirm.
    3. Basic idea:
        - cache is directed mapped with respect to sets.
        - each set is fully associative with N blocks in it.
    4. Given memory address:
        - find correct set using index value.
        - compare tag with all tag values in that set.
        - if a match occurs, then hit, otherwise miss.
        - finally, use the offset field as usual to find the desired data within the block.
2. What's great about this:
        - even a 2-way set associative cache avoids a lot of conflict misses.
        - hardware cost isn't that bad, which only need N comparators.
3. In fact, for a cache with M blocks:
    - it's direct-mapped if it's 1-way set associative.
    - it's fully associative if it's M-way associative.
    - these two are just special cases of the more general set associative design.

## Block Replacement with Example
1. Current block replacement:
    - Direct-mapped cache: index completely specifies position which position a block can go in on a miss.
    - N-way set associative: index specifies a set, but block can occupy any position within the set on a miss.
    - Fully associative: block can be written into any position.
2. Block replacement policy:
    - `LRU` (Least Recently Used):
        - Idea: cache out block which has been accessed least recently.
        - Pro: temporal locality -> recent past use implies likely future use.
        - Con: with 2-way set associativity, easy to keep track. for 4-way or greater, needs complicated hardware to track this.
    - `FIFO`: first in first out. ignore accesses, just tracks initial order.
    - `Random`: works for low temporal locality of workload.

## Average Memory Access Time
1. To choose between associativity, block size, replacement and writing policy:
    - Design against a performance model:
        - Minimize: Average memory access time = Hit time + Miss penalty * Miss rate.
        - Influenced by technology and program behavior.
2. Analyze Multi-level cache hierachy:
    - Average Mem Access Time = L1 Hit Time + L1 Miss Rate * L1 Miss Penalty
    - L1 Miss Penalty = L2 Hit Time + L2 Miss Rate * L2 Miss Penalty
3. Ways to reduce miss rate:
    - Larger cache:
        - limited by cost and technology.
        - his time of first level cache < cycle time, because bigger cache is slower.
    - More places in the cache to put each block of memory: associativity.
4. Typical scale:
    - L1:
        - size: tens of KB
        - hit time: complete in one clock cycle
        - miss rate: 1-5%
    - L2:
        - size: hundreds of KB
        - hit time: few clock cycles
        - miss rate: 10-20%
    - L2 miss rate is fraction of L1 misses that also miss in L2

## Actual CPUs
1. Early CPU:
    - Cache:
        - 32KiB Instructions & 32KiB Data L1 Caches
        - External L2 Cache interface with integrated controller and cache tags, supports up to 1 MiB external L2 cache.
        - Dual Memory Management Units with Translation Lookaside Buffers.
    - Pipelining:
        - Uperscalar
        - 6 execution units

## Conclusion
1. Caching in general shows up over and over in computer systems:
    - Filesystem cache, Web page cache, Game databases, Software memorization, etc.
2. If something is expensive but we want to do it repeatedly, do it once and cache the result.
3. Cache design choices:
    - Size of cache: speed & capacity trade off.
    - Block size.
    - Write Policy (write through & write back)
    - Associativity choice of N
    - Block replacement policy
    - 2nd & 3rd level cache.