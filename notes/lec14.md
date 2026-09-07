# Lec14: Synchronous Digital System
## Switches
1. `Synchonous digital system` is hardware of a processor.
2. Synchronous: All operations coordinated by a central clock.
3. Digital: All values represented by discrete values.
4. Switch: Basic element of physical circuit. Two switches can build `AND` and `OR` gates(serial/parallel), and implement boolean logic.

## Transistors
1. Semiconductor device to amplify or switch signals.
2. Voltage on `gate` terminal is some amount ($\epsilon$) higher/lower than `source` terminal, then conducting path established between `drain` and `source` terminals.
    - `n-channel`: conduct when $voltage(G) > voltage(S) + \epsilon$
    - `p-channel`: conduct when $voltage(G) \leq voltage(S) + \epsilon$

## Signals and Waveframes
1. Signals:
    - When digital is only treated as 1 or 0.
    - Is transmitted over wires continuously.
    - Implies that a wire contains 1 value at a time.
2. Circuit exist delay: propagation delay (time delay from stable input to generating correct output).
3. Type of circuits:
    1. `Combinational Logic Circuits`: output is a function of the inputs only. Used to compute and do logic.
    2. `State Elements`: circuits that store information. Used to hold state, values and control.
    - Use a clock pulse on register, so that it regularly renew its holding value.

## Conclusion
1. Clocks control pulse of circuits.
2. Voltages are analog, quantized to 0/1.
3. Circuit delays are fact of life.
4. Two types of circuits:
    - Stateless `Combinational Logic`
    - State circuits.(e.g. registers)