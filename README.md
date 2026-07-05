# MIPS32 Emulator

A modular implementation of a **MIPS32 Single-Cycle CPU Emulator** written in modern C++.

The goal of this project is to build a complete MIPS32 processor from scratch by implementing every hardware component as an independent C++ module and then integrating them into a working CPU.

This project follows the architecture presented in standard Computer Architecture courses (Patterson & Hennessy).

---

## Current Features

- ✅ Byte-addressable Memory
- ✅ Register File (32 General Purpose Registers)
- ✅ Program Counter (PC)
- ✅ Arithmetic Logic Unit (ALU)
- ✅ Instruction Decoder
- ✅ Control Unit
- ✅ Single-Cycle CPU Core
- ✅ Unit Tests for every module
- ✅ First executable CPU MVP

---

## Implemented Architecture

```
                +----------------------+
                |       Memory         |
                +----------+-----------+
                           |
                           | Fetch
                           v
                +----------------------+
                |      Decoder         |
                +----------+-----------+
                           |
                           v
                +----------------------+
                |    Control Unit      |
                +----------+-----------+
                           |
           +---------------+---------------+
           |                               |
           v                               v
 +---------------------+         +----------------+
 |    Register File    |         |      ALU       |
 +----------+----------+         +-------+--------+
            |                            |
            +------------+---------------+
                         |
                         v
                   Write Back
```

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

Control signals implemented for:

- LW
- SW
- BEQ

### J-Type

Control signals implemented for:

- J

> Memory access and branching will be completed in the next milestone.

---

## Project Structure

```
src/
│
├── alu/
├── control/
├── cpu/
├── decoder/
├── memory/
└── registers/

test/
├── alu_test.cpp
├── control_test.cpp
├── cpu_test.cpp
├── decoder_test.cpp
├── memory_test.cpp
└── registers_test.cpp
```

---

## Development Roadmap

### Phase 1 (Completed)

- [x] Memory
- [x] Register File
- [x] ALU
- [x] Decoder
- [x] Control Unit
- [x] CPU Core MVP

### Phase 2

- [ ] Load/Store execution
- [ ] Branch execution
- [ ] Jump execution
- [ ] Program Loader

### Phase 3

- [ ] MIPS Assembler
- [ ] ELF/Binary Loader
- [ ] Full instruction support

### Phase 4

- [ ] Pipeline implementation
- [ ] Hazard detection
- [ ] Forwarding Unit
- [ ] Cache simulation

---

## Testing

Every module is tested independently before integration.

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

---

## Status

**Work in Progress**

The first MVP successfully executes basic R-Type instructions using a complete fetch → decode → execute → write-back cycle.
