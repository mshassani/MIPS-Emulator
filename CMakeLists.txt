cmake_minimum_required(VERSION 3.15)

project(MIPS)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        src/memory
        src/registers
        src/alu
        src/decoder
        src/control
)

# Memory tests
add_executable(
        memory_test
        test/memory_test.cpp
        src/memory/memory.cpp
)

# Registers tests
add_executable(
        registers_test
        test/registers_test.cpp
        src/registers/registers.cpp
)

# ALU tests
add_executable(
        alu_test
        test/alu_test.cpp
        src/alu/alu.cpp
)

# Decoder Tests
add_executable(
        decoder_test
        test/decoder_test.cpp
        src/decoder/decoder.cpp
)

# Control Test
add_executable(
        control_test
        test/control_test.cpp

        src/control/control.cpp
        src/decoder/decoder.cpp
)

# Cpu Test
add_executable(
        cpu_test
        test/cpu_test.cpp

        src/cpu/cpu.cpp
        src/memory/memory.cpp
        src/registers/registers.cpp
        src/decoder/decoder.cpp
        src/control/control.cpp
        src/alu/alu.cpp
)