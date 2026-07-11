# MIPS32 Emulator

A modular implementation of a **MIPS32 Single-Cycle CPU Emulator** written in modern **C++17**.

The purpose of this project is to build a complete MIPS32 processor from scratch by implementing each hardware component independently and integrating them into a functional CPU. Every module is designed to closely resemble its hardware counterpart, making the project suitable for learning computer architecture as well as experimenting with CPU design.

The implementation follows the architecture presented in **Computer Organization and Design** by **Patterson & Hennessy**.

---

# Features

-  Byte-addressable Memory
-  Register File (32 General Purpose Registers)
-  Program Counter (PC)
-  Arithmetic Logic Unit (ALU)
-  Instruction Decoder
-  Control Unit
-  Single-Cycle CPU Datapath
-  Binary Program Loader
-  Basic MIPS Assembler
-  Interactive Command-Line Emulator
-  Step-by-step Instruction Execution
-  Unit Tests for Individual Components

---

# Implemented Architecture

<img width="1217" height="699" alt="Single Cycle Datapath" src="https://github.com/user-attachments/assets/c37c012e-ce92-435e-b1e9-a15ee79cd9d4" />

---

# Supported Instructions

## R-Type

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

## I-Type

- ADDI
- LW
- SW
- BEQ

## J-Type

- J

---

# Endianness

The emulator uses **Little-Endian** memory layout.

Instructions and data are stored exactly as they would be in a little-endian MIPS system. The assembler generates binaries using the same format, ensuring full compatibility between the assembler, loader and emulator.

---

# Testing

Every hardware component is tested independently before being integrated into the CPU.

Current test coverage includes:

- Memory
- Register File
- ALU
- Decoder
- Control Unit
- CPU Integration
- Program Execution

---

# Usage

## 1. Clone the Repository

```bash
git clone https://github.com/mshassani/MIPS32-Emulator.git
cd MIPS32-Emulator
```

---

## 2. Build

```bash
mkdir build
cd build

cmake ..
cmake --build . --config Release
```

---

## 3. Assemble a MIPS Program

```bash
./assembler example.asm
```

This generates:

```
output.bin
```

---

## 4. Run the Emulator

```bash
./Emulator output.bin
```

The emulator loads the binary into memory and allows step-by-step execution.

---

# Technologies

- C++17
- CMake
- Assert-based Unit Testing

---

# Project Goals

- Learn computer architecture by implementing hardware components in software.
- Build a clean, modular and extensible MIPS32 emulator.
- Simulate the execution of MIPS machine instructions.
