# Lec26: Caches Ⅲ
## Writes, Block, Sizes, Misses
1. Only have a hit when the address in cache is valid and tag is matched.
2. What to do on a write hit:
    1. Write through: Update both cache and memory.
    2. Write back: Update word in cache block. Allow memory word to be stable add dirty bit block.
    - MEM and cache become inconsistent, needs to be updated when block is placed.
3. Block size Tradeoff:
    - Benefits of larger block size:
        - Spatial locality: if we access a given word, we're likely to access other nearby word soon.
        - Very applicable with stored-program concept.
        - Works well for sequential array access.
    - Drawbacks of larger block size:
        - Larger block size means larger miss penalty.
        - if block size is too big relative to cache size, then there are too few blocks, hence miss rate goes up.
4. Types of Cache Misses
    1. `Compulsory misses`:
        - occur when a program is first started.
        - cache does not contain any of that program's data yet, so misses are bounded to occur.
        - every block of memory will have one compulsory miss.
    2. `Conflict misses`:
        - miss that occurs because two distinct memory addresses map to the same cache location.
        - two blocks can keep writing each other.
        - Solution: make cache bigger / associative caches.
    3. `Capacity misses`:
        - miss that occurs because the cache has a limited size.
        - miss that would not occur if we increase the size of cache. 
        - primary type of miss for `fully associative caches`.

## Fully Associative Caches
1. Fully associative cache: Cancel `conflict misses`.
    - Keep the same Tag and Offset.
    - Index don't exist.
    - Any block can go anywhere in cache.
    - Must compare with all tags in entire cache to see if data is there.
2. Compare tags in parallel.
3. Need hardware comparator for every single entry. If there is 64KB of data in cache with 4B entries, we need 16K comparators, which is infeasible.
4. How to catagorize misses: Run an address trace against a set of caches.
    - First, consider an infinite-size, fully-associative cache. For every miss that occurs now, consider it `compulsory miss`.
    - Next, consider a finite-sized cache with full-associativity. Every miss that is not in the first stage is a `capacity miss`.
    - Finally, consider a finite-size cache with finite-associativity. All of the remaining misses that are not the previous two are `conflict miss`.