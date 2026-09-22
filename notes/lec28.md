# Lec28: OS & Virtual Memory Intro
## Operating System Basics
1. Functions of OS:
    - OS is the first thing to run when computer starts.
    - Finds and controls all devices in the machine in a general way.
        - relying on hardware spcific device drivers.
    - Starts services:
        - file system
        - network stack
        - TTY (keyboard)
    - Loads, runs and manages programs:
        - Multiple programs at the same time,
        - Isolate programs from each other,
        - Multiplex resources between applications.
2. Core of OS:
    - Provide `Isolation` between running processes: each program runs in its own little world.
    - Provide `Interaction` with the outside world: interact with devices, disk, display, etc.
3. Need from hardware:
    - Memory translation:
        - Each running process has a mapping from `virtual` to `physical` addresses that are different for each process.
        - When you do a load or a store, the program issues a virtual address, but the acutal memory accessed is a physical address.
    - Protection and privilege:
        - Split the processor into at least two running modes: `user` and `supervisor`.
        - Lesser privilege can not change its memory mapping.
            - "supervisor" can change the mapping for any given program.
    - Traps and Interrupts
        - a way of going into supervisor mode on demand.
4. Booting (set up) issues:
    1. BIOS: find a storage device and load first sector.
    2. Bootloader: load the OS kernel from disk into a location in memory and jump into it.
    3. OS boot: initialize services, devices, etc.
    4. Init: launch an application that waits for input in loop. 
## Operating System Functions
1. Launching Applications:
    - Applications are called `processes` in most OS:
        - `Thread`: shared memory.
        - `Process`: separate memory.
        - Both threads and processes run simultaneously.
    - Apps are started by another process calling an OS routine (using `syscall`):
        - Depends on OS (Linux uses `fork` to create a new process, and `execve` to load application).
    - Loads executable file from disk and puts instructions & data into memory, prepares stack and heap.
    - Set argc and argv, jump to start of main.
    - Shell waits for main to return.
2. Supervisor Mode:
    1. The OS enforces resources contraints to applications, to avoid crashing the entire machine when something goes wrong.
    2. To help protect the OS from the application, CPUs have a supervisor mode.
        - A process can only access a subset of instructions and physical memory when not in supervisor mode.
        - Process can change out of supervisor mode using a special instruction, but not into it directly, only using an `interrupt`.
3. Syscall:
    - When we want to call an OS routine (read/write file, launch process, etc), we need to perform a syscall.
    - In this way, the OS can mediately access to all resources and devices.
4. Interruption & Exception
    - `Interrupt`: Something external to the running program, something happens from the outside world.
    - `Exception`: Something done by the running program. Accessing memory it isn't supposed to, executing an illegal instruction, reading a csr not supposed at that privilege.
    - `ECALL`: Trigger an exception to the higher privilege. Used to communicate with system.
    - `EBREAK`: Trigger an exception within the current privilege.
5. Precise Traps:
    - Trap handler's view of machine state is that every instruction prior to the trapped one has completed and no instruciton after the trap has executed.
    - Implies that handler can return from an interrupt by restoring iser registers and jumping back to interrupted instrucion.
        - Interrupt handler software doesn't need to understand the pipeline of the machien, or what program was doing.
        - More complex to handle trap caused by an exception than interrupt.
    - Providing precise traps is tricky in a pipelined superscalar out-of-order processor, but a requirement for things to actually work right.
6. Multiprogramming:
    - The OS runs multiple applications at the same time.
    - OS switches between processes very quickly, which is called `context switch`.
    - When jumping into process, set timer (which is called interrupt):
        - when it expires, store PC, registers and other process state.
        - pick a different process to run and load its state.
        - set timer, change to user mode, jump to the new PC.
7. Protection, Translation and Paging:
    - Supervisor mode alone is not sufficient to fully isolate applications from each other or from the OS.
        - Application could overwrite another application's memory.
        - Typically programs start at some fixed address.
        - Applications may want to address more memory than we actually have.
    - Solution: `Virtual Memory`.
        - Gives each process an illusion of a full memory address space that it has completely for itself.