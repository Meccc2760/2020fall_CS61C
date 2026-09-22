# Lec25: Caches Ⅱ
## Direct Mapped Cache
1. Each memory address is associated with one possible block within cache.
    - Block is the unit of transfer between cache and memory. Block size can be 1byte/4byte ...
2. Issue: Multiple memory addresses map to same cache index.
    - Solution: divide memory address to three fields to identify them. All fields are read as unsigned integers:
        - Index: specifies the cache index (which row/block of the cache we look in).
        - Offset: once we've found the correct block, spcifies which byte within the block we want.
        - Tag: the remaining bits after offset and index are determined, these are used to distinguish between all the memory addresses that map to the same location.

## Direct Map Example
1. With datasize, block size given, we can get the number of blocks.
2. Index: Describe the place in cache, derived from memory block address.
3. Tag: Remaining bits of metadata are tags. Used to identify exact data.
- For the instruction: $lw\space t0, 0(t1)$, t1 contains $1022_{ten}$, MEM[1022] = 99:
    - Process without cache:
        1. Processor issues address 1022 to memory,
        2. Memory reads word at address 1022 (99),
        3. Memory sends 99 to processor,
        4. Processor loads 99 into register t0.
    - Process with cache:
        1. Processor issues address 1022 to cache,
        2. Cache checks to see if has copy of data at address 1022:
            - If finds a match address (cache hit), sends to processor.
            - If not match (cache miss):    
                - Cache sends 1022 to memory,
                - Memory reads 99 at address 1022,
                - Memory sends 99 to cache,
                - Cache replaces word with new 99,
                - Cache sends 99 to processor.
        3. Processor loads 99 into register t0.

## Cache Terminology
1. When reading memory, three things may happen:
    - `cache hit`: cache blocks is valid and contains proper address, so read desired word.
    - `cache miss`: nothing in cache in appropriate block, so fetch from memory.
    - `cache miss, block replacement`: wrong data is in cache at appropriate block, so discard it and fetch desired data from memory.
2. Cache temperature: how successful cache is improving performance.
    - cold: cache empty
    - warming: cache filling with values you'll hopefully be accessing again soon
    - warm: cache is doing its job, fair percentage of hits
    - hot: cache is doing very well, high percentage of hits
3. Cache terms:
    - `hit rate`: fraction of access that hit in the cache.
    - `miss rate`: 1 - hit rate
    - `miss penalty`: time to replace a block from lower level in memory hierachy to cache.
    - `hit time`: time to access cache memory (including tag comparison).
4. Valid bit:
    - When start a new program, cache does not have valid information for this program.
    - Need an indicator whether this tag entry is valid for this program.
    - Add a "valid" bit to the cache tag entry.