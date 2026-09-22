# Lec30: Virtual Memory Ⅱ

## Hierarchical Page Table
1. Split the virtual address into: `p1 | p2 | offset`
  - `p1`: index into the Level-1 page table
  - `p2`: index into a Level-2 page table
  - `offset`: byte position inside the final page
2. The Level-1 page table points to Level-2 page tables.
3. Each Level-2 entry points to a physical page.
4. Only needed Level-2 page tables are created, so unused virtual address regions do not waste page-table space.
5. Main idea: use extra levels of lookup to save memory.

## Translation Lookaside Buffers
1. Every instruction and data access needs address translation and protection checks.
2. Address translation is expensive. To solve, we cache some translations in the buffer.
3. `TLB` Designs:
  - Typically 32-128 entries, usually fully associative.
    - Each entry maps a large page, hence less spatial locality across pages. (two entries are more likely to conflict)
    - Sometimes larger TLBs (256-512 entries) are 4-8 way set-associative.
    - Larger systems sometimes have multi-level TLBs.
  - RANDOM or FIFO replacement policy.
  - `TLB reach`: Size of largest virtual address space that can be simultaneously mapped by TLB.
4. TLB: For a certain address, we check TLB first, and if the physical address is in cache, we turn to cache.

## VM Performance
1. Virtual Memory is the level of the memory hierachy that sits below main memory.
  - TLB comes before cache, but affects transfer of data from disk to main memory.
  - Previously we assumed main memory was lowest level, now we just have to account for disk accesses.
2. Same CPI, AMAT(average memory access time) quations apply, but now trat main memory like a mid-level cache.
3. Average Memory Access Time (with paging) = 5.5 + 5% * 40% * (1-HR) * 20000000
  - Hit Rate should be extremely high to void dramatic miss penalty.