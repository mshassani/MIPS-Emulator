#include "control.hpp"

ALUOperation ControlUnit::operation(uint8_t funct) const {
    switch (funct) {
        case 0x20: return ALUOperation::ADD;
        case 0x22: return ALUOperation::SUB;
        case 0x24: return ALUOperation::AND;
        case 0x25: return ALUOperation::OR;
        case 0x26: return ALUOperation::XOR;
        case 0x27: return ALUOperation::NOR;
        case 0x2A: return ALUOperation::SLT;
        case 0x00: return ALUOperation::SLL;
        case 0x02: return ALUOperation::SRL;
        case 0x03: return ALUOperation::SRA;
        default: return ALUOperation::NOP;
    }
}

ControlSignals ControlUnit::generate(const DecodedInstruction &instruction) const {
    ControlSignals signals{};

    switch (instruction.opcode) {
        case 0x00:
            signals.regWrite = true;
            signals.regDst = true;

            signals.memRead = false;
            signals.memWrite = false;
            signals.memToReg = false;

            signals.aluSrc = false;

            signals.branch = false;
            signals.jump = false;

            signals.aluOperation = operation(instruction.funct);
            break;

        case 0x23:
            signals.regWrite = true;
            signals.memRead = true;
            signals.memWrite = false;

            signals.memToReg = true;
            signals.regDst = false;
            signals.aluSrc = true;

            signals.branch = false;
            signals.jump = false;

            signals.aluOperation = ALUOperation::ADD;
            break;

        case 0x2B:
            signals.regWrite = false;
            signals.memRead = false;
            signals.memWrite = true;

            signals.memToReg = false;
            signals.regDst = false;
            signals.aluSrc = true;

            signals.branch = false;
            signals.jump = false;

            signals.aluOperation = ALUOperation::ADD;
            break;

        case 0x04:
            signals.regWrite = false;
            signals.memRead = false;
            signals.memWrite = false;

            signals.memToReg = false;
            signals.regDst = false;
            signals.aluSrc = false;

            signals.branch = true;
            signals.jump = false;

            signals.aluOperation = ALUOperation::SUB;
            break;

        case 0x02:
            signals.regWrite = false;
            signals.memRead = false;
            signals.memWrite = false;

            signals.memToReg = false;
            signals.regDst = false;
            signals.aluSrc = false;

            signals.branch = false;
            signals.jump = true;

            signals.aluOperation = ALUOperation::NOP;
            break;

        case 0x08:
            signals.regWrite = true;
            signals.memRead = false;
            signals.memWrite = false;

            signals.memToReg = false;
            signals.regDst = false;
            signals.aluSrc = true;

            signals.branch = false;
            signals.jump = false;

            signals.aluOperation = ALUOperation::ADD;
            break;

        default:
            signals.regWrite = false;
            signals.memRead = false;
            signals.memWrite = false;
            signals.memToReg = false;
            signals.regDst = false;
            signals.aluSrc = false;
            signals.branch = false;
            signals.jump = false;
            signals.aluOperation = ALUOperation::NOP;
    }
    return signals;
}