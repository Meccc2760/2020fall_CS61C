# Lec29: Virtual Memory Ⅰ
## Virtual Memory Conceptions
1. Virtual memory: next level in the memory hierachy.
    - Allows OS to share memory, protect programs form each other.
    - Each process thinks it has all the memory for itself.
    - More important for protection than just another level of memory hierachy.
2. Compare with Physical Addresses:
    1. Process use virtual addresses.
    2. Memory uses physical addresses.
3. Address Spaces
    - Address space = set of addresses for all available memory locations.
    - Memory manager maps between the two kinds of address spaces:
        - Virtual Address Space: set of addresses that the user program knows about.
        - Physical Address Space: Set of addresses that map to actual physical locations in memory, hidden from user applications.
4. Memory Hierachy Requirements:
    - Allow multiple processes to simultaneously occupy memory and provide protection (prevent one program form read/write from each other).
    - Address space (give each program the illusion that it has its own private memory).

## Memory Manager
1. Virtual Memory:
    1. In bare metal without OS, addresses issued with load/store are real physical addresses.
    2. In this mode, any process can issue any address, therefore can access any part of memory.
    3. We should send all addresses through a mechanism  that the OS controls, before they make it out to DRAM, a translation mechanism.
2. Responsibilities of Memory Manager:
    1. Map virtual to physical addresses.
    2. Protection:
        - Isolate memory between preocesses.
        - Each process gets dedicate private memory.
        - Errors in one program won't corrupt memory of other program.
        - Prevent user programs form messing with OS's memory.
    3. Swap memory to disk:
        - Give illusion of larger memory by storing some content on disk.
        - Disk is usually much larger and slower than DRAM.

## Paged Memory
1. Memory manager and paged memory:
    1. Concept of `paged memory` dominates:
        - Physical memory is broken into pages
        - Typical page size: 4KiB
    2. There are page tables managed by OS to map virtual to physical.
2. Paged Memory Address Translation:
    - OS keeps track of which preocess is active, and chooses the correct page table.
    - Memory manager extracts page number from virtual address, then looks up page address in page table.
    - Computes physical memory address from sum of page address and offset.
3. Protection:
    - Assigning different pages in DRAM to processes also keeps them from accessing each others memory.
        - Isolation
        - Page tables handled by OS
    - Sharing is also possible:
        - OS may assign same physical page to several processes.
4. Page Table Residence:
    - Store page tables in memory(DRAM):
        - Two slow memory accesses per lw/sw on cache miss
        - To minimize the performance penalty, we transfer blocks between DRAM and processor cache, and use a dedicated cache for frequently used page table entries.

## Page Faults 
1. Blocks & Pages:
    - In caches, we dealt with individual blocks.
    - In VM, we deal with individual pages.
    - Common point: bytes, words, blocks, pages are just different was of looking at memory.
2. Memory Access:
    - Check page table entry:
        - if valid:
            - if in DRAM: read/write data.
            - if on disk: allocate new page in DRAM.
                - if out of memory, evict a page from DRAM and store it to disk. then read page from disk into memory and read/write data.
        - if not valid:
            - allocate new page in DRAM.
            - if out of memory, similarly, evict a page from DRAM and store it to disk.
3. Page Fault:
    - Page faults are treated as exceptions.
        - page fault handler does the page table updates and initiates transfers.
        - updates status bits.
    - If page needs to be swapped from disk, perform context switch.
    - Following the page fault, the instruction is re-executed.