#include <cassert>
#include <iostream>

#include "../src/cpu/cpu.hpp"

int main() {

    CPU cpu;

    cpu.reset();

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
    std::cout << " First MVP Passed Successfully!\n";
    std::cout << "=====================================\n";

    return 0;
}