#pragma once
#include "../decoder/decoder.hpp"
#include "../alu/alu.hpp"

struct ControlSignals {
    bool regWrite;
    bool memRead;
    bool memWrite;

    bool memToReg;
    bool regDst;
    bool aluSrc;

    bool branch;
    bool jump;

    ALUOperation aluOperation;
};

class ControlUnit {
    private:
        ALUOperation operation(uint8_t funct) const;
    public:
        ControlSignals generate(const DecodedInstruction &instruction) const;
};