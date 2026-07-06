#include <cassert>
#include <iostream>

#include "../src/cpu/cpu.hpp"

int main() {

    CPU cpu;

    cpu.reset();

    std::cout << "\n=====================================\n";
    std::cout << " R-Type Instructions\n";
    std::cout << "=====================================\n";

    //==================================================
    // R-Type Instructions
    //==================================================


    //==================================================
    // Test 1 : add $t0, $t1, $t2
    //==================================================

    // $t1 = 10
    cpu.setRegister(9, 10);

    // $t2 = 20
    cpu.setRegister(10, 20);

    // add $t0,$t1,$t2
    cpu.loadInstruction(0x00000000, 0x012A4020);

    cpu.step();

    assert(cpu.getRegister(8) == 30);
    assert(cpu.getPc() == 4);

    std::cout << "[PASS] ADD\n";


    //==================================================
    // Test 2 : sub $t0, $t1, $t2
    //==================================================

    cpu.reset();

    cpu.setRegister(9, 20);
    cpu.setRegister(10, 10);

    // sub $t0,$t1,$t2
    cpu.loadInstruction(0x00000000, 0x012A4022);

    cpu.step();

    assert(cpu.getRegister(8) == 10);

    std::cout << "[PASS] SUB\n";


    //==================================================
    // Test 3 : and
    //==================================================

    cpu.reset();

    cpu.setRegister(9, 0b1100);
    cpu.setRegister(10, 0b1010);

    // and $t0,$t1,$t2
    cpu.loadInstruction(0x00000000, 0x012A4024);

    cpu.step();

    assert(cpu.getRegister(8) == 0b1000);

    std::cout << "[PASS] AND\n";


    //==================================================
    // Test 4 : or
    //==================================================

    cpu.reset();

    cpu.setRegister(9, 0b1100);
    cpu.setRegister(10, 0b1010);

    cpu.loadInstruction(0x00000000, 0x012A4025);

    cpu.step();

    assert(cpu.getRegister(8) == 0b1110);

    std::cout << "[PASS] OR\n";


    //==================================================
    // Test 5 : xor
    //==================================================

    cpu.reset();

    cpu.setRegister(9, 0b1100);
    cpu.setRegister(10, 0b1010);

    cpu.loadInstruction(0x00000000, 0x012A4026);

    cpu.step();

    assert(cpu.getRegister(8) == 0b0110);

    std::cout << "[PASS] XOR\n";


    //==================================================
    // Test 6 : slt
    //==================================================

    cpu.reset();

    cpu.setRegister(9, 5);
    cpu.setRegister(10, 10);

    cpu.loadInstruction(0x00000000, 0x012A402A);

    cpu.step();

    assert(cpu.getRegister(8) == 1);

    std::cout << "[PASS] SLT\n";

    std::cout << "\n=====================================\n";
    std::cout << "I-Type Instructions\n";
    std::cout << "=====================================\n";

    //===================================================
    // I-Type Instructions
    //===================================================


    //===================================================
    // Test 7: LW
    //===================================================

    cpu.reset();

    //memory[100] = 0x12345678
    cpu.loadInstruction(0x64, 0x12345678);

    // lw $t0,100($zero)
    cpu.loadInstruction(0x00000000, 0x8C080064);

    cpu.step();

    assert(cpu.getRegister(8) == 0x12345678);
    std::cout << "[PASS] LW\n";

    //=====================================================
    // Test 8: SW
    //=====================================================

    cpu.reset();

    cpu.setRegister(8, 0xCAFEBABE);

    // sw $t0,100($zero)
    cpu.loadInstruction(0x00000000, 0xAC080064);

    cpu.step();

    assert(cpu.getMemory(100) == 0xCAFEBABE);
    std::cout << "[PASS] SW\n";

    //=======================================================
    // Test 9: BEQ
    //=======================================================

    /*
     * Beq Taken
     */

    cpu.reset();

    // $t0 = 10
    cpu.setRegister(8, 10);

    // $t1 = 10
    cpu.setRegister(9, 10);

    // beq $t0,$t1,1
    cpu.loadInstruction(0x00000000, 0x11090001);

    cpu.step();

    // PC = 0 + 4 + (1 << 2) = 8
    assert(cpu.getPc() == 8);

    std::cout << "[PASS] BEQ Taken\n";

    //=============================================================

    /*
     * Beq Not Taken
     */

    cpu.reset();

    cpu.setRegister(8, 10);
    cpu.setRegister(9, 20);

    // beq $t0,$t1,1
    cpu.loadInstruction(0x00000000, 0x11090001);

    cpu.step();

    // PC + 4 = 4
    assert(cpu.getPc() == 4);

    std::cout << "[PASS] BEQ Not Taken\n";

    //===============================================================

    /*
     * Beq Backward
     */

    cpu.reset();

    cpu.setRegister(8, 5);
    cpu.setRegister(9, 5);

    // beq $t0,$t1,-1
    cpu.loadInstruction(0x00000000, 0x1109FFFF);

    cpu.step();

    // PC = 0 + 4 - 4 = 0
    assert(cpu.getPc() == 0);

    std::cout << "[PASS] BEQ Backward\n";

    //===================================================
    // J-Type Instructions
    //===================================================

    //===================================================
    // Test 10: J
    //===================================================

    std::cout << "\n=====================================\n";
    std::cout << "J-Type Instructions\n";
    std::cout << "=====================================\n";

    //===================================================

    cpu.reset();

    cpu.loadInstruction(0, 0x08000004);

    cpu.step();

    assert(cpu.getPc() == 16);

    std::cout << "[PASS] JUMP\n";

    //===================================================



    return 0;
}