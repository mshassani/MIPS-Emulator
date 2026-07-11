# MIPS32 Emulator

A modular implementation of a **MIPS32 Single-Cycle CPU Emulator** written in modern C++.

The goal of this project is to build a complete MIPS32 processor from scratch by implementing every hardware component as an independent C++ module and then integrating them into a working CPU.

This project follows the architecture presented in standard Computer Architecture courses (Patterson & Hennessy).

---

## Current Features

-  Byte-addressable Memory
-  Register File (32 General Purpose Registers)
-  Program Counter (PC)
-  Arithmetic Logic Unit (ALU)
-  Instruction Decoder
-  Control Unit
-  Single-Cycle CPU Core
-  Unit Tests for every module

---

## Implemented Architecture

<img width="1217" height="699" alt="image" src="https://github.com/user-attachments/assets/c37c012e-ce92-435e-b1e9-a15ee79cd9d4" />


---

## Implemented Instructions

### R-Type

- ADD
- SUB
- AND
- OR
- XOR
- NOR
- SLT
- SLL
- SRL
- SRA

### I-Type

- LW
- SW
- BEQ
- ADDI
- شیی
### J-Type

- J

---

## Endianness

This emulator uses a **Little-Endian** memory layout.

All instructions and data are stored in memory using little-endian byte order. The assembler generates binary files in the same format, ensuring full compatibility between the assembler, loader, and emulator.

---

## Testing

Every module is tested independently before integration.

---

Current test coverage includes:

- Memory operations
- Register File
- ALU operations
- Instruction decoding
- Control signal generation
- CPU integration (first MVP)

---

## Technologies

- C++17
- CMake
- Assert-based Unit Testing

---

## Goals

- Learn computer architecture through implementation.
- Build a clean, modular, and extensible emulator.
- Simulate the execution of MIPS32 machine instructions.
- Provide a solid foundation for future pipeline and cache implementations.


