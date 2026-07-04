#include <cassert>
#include <iostream>

#include "../src/control/control.hpp"
#include "../src/decoder/decoder.hpp"

int main()
{
    Decoder decoder;
    ControlUnit control;

    DecodedInstruction instruction;
    ControlSignals signals;

    //=================================
    // add $t0,$t1,$t2
    // 0x012A4020
    //=================================

    instruction = decoder.decode(0x012A4020);
    signals = control.generate(instruction);

    assert(signals.regWrite);
    assert(signals.regDst);
    assert(!signals.memRead);
    assert(!signals.memWrite);
    assert(!signals.memToReg);
    assert(!signals.aluSrc);
    assert(!signals.branch);
    assert(!signals.jump);
    assert(signals.aluOperation == ALUOperation::ADD);

    std::cout << "[PASS] ADD\n";


    //=================================
    // sub $t0,$t1,$t2
    // 0x012A4022
    //=================================

    instruction = decoder.decode(0x012A4022);
    signals = control.generate(instruction);

    assert(signals.regWrite);
    assert(signals.regDst);
    assert(signals.aluOperation == ALUOperation::SUB);

    std::cout << "[PASS] SUB\n";


    //=================================
    // lw $v0,4($at)
    // 0x8C220004
    //=================================

    instruction = decoder.decode(0x8C220004);
    signals = control.generate(instruction);

    assert(signals.regWrite);
    assert(signals.memRead);
    assert(!signals.memWrite);
    assert(signals.memToReg);
    assert(!signals.regDst);
    assert(signals.aluSrc);
    assert(signals.aluOperation == ALUOperation::ADD);

    std::cout << "[PASS] LW\n";


    //=================================
    // sw $v0,4($at)
    // 0xAC220004
    //=================================

    instruction = decoder.decode(0xAC220004);
    signals = control.generate(instruction);

    assert(!signals.regWrite);
    assert(!signals.memRead);
    assert(signals.memWrite);
    assert(signals.aluSrc);
    assert(signals.aluOperation == ALUOperation::ADD);

    std::cout << "[PASS] SW\n";


    //=================================
    // beq $at,$v0,4
    // 0x10220004
    //=================================

    instruction = decoder.decode(0x10220004);
    signals = control.generate(instruction);

    assert(!signals.regWrite);
    assert(signals.branch);
    assert(!signals.jump);
    assert(signals.aluOperation == ALUOperation::SUB);

    std::cout << "[PASS] BEQ\n";


    //=================================
    // j 0x00000004
    // 0x08000004
    //=================================

    instruction = decoder.decode(0x08000004);
    signals = control.generate(instruction);

    assert(!signals.regWrite);
    assert(signals.jump);
    assert(signals.aluOperation == ALUOperation::NOP);

    std::cout << "[PASS] J\n";


    std::cout << "\nAll Control Unit Tests Passed.\n";

    return 0;
}