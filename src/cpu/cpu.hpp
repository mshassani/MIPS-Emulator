#pragma once

#include "../memory/memory.hpp"
#include "../registers/registers.hpp"
#include "../decoder/decoder.hpp"
#include "../control/control.hpp"
#include "../alu/alu.hpp"

class CPU {
    private:
        Memory memory;
        Registers registers;

        Decoder decoder;
        ControlUnit control;
        ALU alu;
    public:
        void loadInstruction(uint32_t address, uint32_t instruction);
        void setRegister(uint8_t reg, uint32_t value);

        uint32_t getRegister(uint8_t reg) const;
        uint32_t getPc() const;

        void step();
        void reset();
        // void run();
};