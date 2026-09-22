# Lec31: I/O
## I/O Device
1. Use standard interfaces to connect I/O device.
2. Instruction Set Architecture for I/O:
    - Interface options:
        1. Special input/output instructions & hardware.
        2. Memory mapped I/O:
            - portion of address space dedicated to I/O.
            - I/O device registers there.
            - Use normal load/store instructions.

## I/O Polling
1. Polling: Processor checks status, then acts.
    - Device registers generally serve two functions:
        - `Control register`, says it's ok to read/write.
        - `Data register`, contains data.
    - Processor reads from Control register in loop:
        - Waiting for device to set `ready bit` in `Control register`.
        - Indicates `data available` or `ready to accept data`.
    - Processor then loads from input or writes to output data register.

    ```risc-v
    # I/O Example (Polling)

    # Input: Read from keyboard into a0

    lui   t0, 0x7ffff        # t0 = 0x7ffff000 (I/O base address)

    Waitloop:
    lw    t1, 0(t0)          # read input control register
    andi  t1, t1, 0x1        # check ready bit
    beq   t1, zero, Waitloop # if not ready, keep polling
    lw    a0, 4(t0)          # read input data


    # Output: Write to display from a1

    lui   t0, 0x7ffff        # t0 = 0x7ffff000 (I/O base address)

    Waitloop:
    lw    t1, 8(t0)          # read output control register
    andi  t1, t1, 0x1        # check ready bit
    beq   t1, zero, Waitloop # if not ready, keep polling
    sw    a1, 12(t0)         # write output data
    ```

    ```binary
    Memory Map

    0x7ffff000    input control register
    0x7ffff004    input data register
    0x7ffff008    output control register
    0x7ffff00c    output data register
    ```
## I/O Inrterrupts
1. Alternative for polling: `Interrupt`.
    - Polling wastes processor resources.
    - Interrupts:
        - No I/O activity: noting to do
        - Lots of I/O: expensive thrashing caches, VM, saving states.
    
## Direct-Memory Access
1. DMA info:
    - Allows I/O devices to directly read/write main memory.
    - New hardware: the `DMA` engine.
    - DMA engine contains registers writeen by CPU:
        - memory address to place data
        - number of bytes
        - I/O device number, direction of transfer
        - unit of transfer, amount to transfer per burst
2. Incoming data;
    1. Receive interrput form device.
    2. CPU takes interrupt, initiates transfer. Instructs DMA engine to place data at certain address.
    3. Device/DMA engine handle the transfer: CPU is free to execute other things.
    4. Upon completion, device/DMA engine interrupt the CPU again.
3. Outgoing data: 
    1. CPU decides to initiate transfer, confirms that external device is ready.
    2. CPU begins transfer, instructs DMA engine that data is available at certain address.
    3. Device/DMA engine handle the transfer, CPU is free to execute other things.
    4. Device/DMA engine interrupt the CPU again to signal completion.

## Networking
1. Software Protocol to send and receive:
    - SW Send steps:
        1. Application copies data to OS buffer, 
        2. OS calculates checksum, starts timer,
        3. OS sends data to network interface HW and start.
    - SW Receive steps:
        3. OS copies data from network interface HW to OS buffer, 
        2. OS calculates checksum, if OK, sends ACK, if not, delete message and wait for sender to resend when the timer expires,
        1. If OK, OS copies data to user address space, and signals application to continue.
2. Requirement: a Network Interface Card.