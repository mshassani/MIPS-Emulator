#include "cpu.hpp"
#include <cstdint>

void CPU::loadInstruction(uint32_t address, uint32_t instruction) {
  memory.write32(address, instruction);
}

void CPU::setRegister(uint8_t reg, uint32_t value) {
  registers.write(reg, value);
}
Memory& CPU::memoryInstance() {
    return memory;
}
uint32_t CPU::getRegister(uint8_t reg) const { return registers.read(reg); }

uint32_t CPU::getPc() const { return registers.getPc(); }

uint32_t CPU::getMemory(uint32_t address) {
  return memory.read32(address);
}

void CPU::reset() {
  memory.reset();
  registers.reset();
}

void CPU::step() {
  uint32_t instruction;

  DecodedInstruction decoded;

  ControlSignals signals;

  uint32_t operandB;

  uint32_t A;
  uint32_t B;

  ALUOutput aluOutput;

  //=========================================================================================================================================
  //=========================================================================================================================================

  //================================
  // 1- fetch
  //================================
  uint32_t pc = registers.getPc();

  instruction = memory.read32(pc);
  registers.setPc(pc + 4);

  //================================
  // 2- decode
  //================================
  decoded = decoder.decode(instruction);
  signals = control.generate(decoded);

  //================================
  // 3- read registers
  //================================
  A = registers.read(decoded.rs);
  B = registers.read(decoded.rt);

  //================================
  // 3- execute
  //================================
  if (signals.aluSrc) {
    operandB = static_cast<int32_t>(static_cast<int16_t>(decoded.immediate));
  } else {
    operandB = B;
  }

  aluOutput = alu.execute(signals.aluOperation, A, operandB);

  if (signals.branch && aluOutput.zero) {
    registers.setPc(pc + 4 + (static_cast<int32_t>(static_cast<int16_t>(decoded.immediate)) << 2));
  }

  if (signals.jump) {
    uint32_t target = ((pc + 4) & 0xF0000000) | (decoded.address << 2);
    registers.setPc(target);
  }

  //================================
  // 5- write back
  //================================

  uint32_t writeDate = aluOutput.value;

  // Memory access
  if (signals.memRead) {
    writeDate = memory.read32(aluOutput.value);
  }

  if (signals.memWrite) {
    memory.write32(aluOutput.value, B);
  }
  //====================================

  if (signals.regWrite) {
    uint8_t destination = signals.regDst ? decoded.rd : decoded.rt;
    registers.write(destination, writeDate);
  }
}
