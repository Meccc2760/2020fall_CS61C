# Lec05: Memory
## Dynamic Memory Allocation
1. Allocate room for something new to point to, use `malloc(sizeof(type)*n)` with type declared ahead.
2. `realloc(ptr, sizeof(type)*n)` can reallocate memory for an existing pointer.

## Linked list
- implementation of `malloc()` in data structure.

## Memory Location
-  C has 3 pools of memory:
    1. Static Storage: gloabl variable storage, basically permanent, entire program run.
    2. Stack: local variable storage, parameters, return address.
    3. Heap: dynamic malloc storage, data lives until deallocated by programmer.

## Memory bugs
1. Using/reading malloc pointer before initializing/assigning it.
2. Returning pointers into the stack.(local/in-function variable address)  
    Solution: use malloc in Heap
3. Usage after `free()`.