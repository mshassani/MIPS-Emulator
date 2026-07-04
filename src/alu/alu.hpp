#pragma once
#include <cstdint>

enum class ALUOperation {
    NOP,

    ADD,
    SUB,

    AND,
    OR,
    NOR,
    XOR,

    SLL,
    SRL,
    SRA,

    SLT,

    PASS

};

struct ALUOutput {
    uint32_t value;

    bool zero;
    bool carry;
    bool negative;
    bool overflow;
};

class ALU {
    public:
    ALUOutput execute(ALUOperation operation, uint32_t A, uint32_t B);
};