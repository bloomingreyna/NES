#include <components/cpu.h>
#include <ns.h>

void CPU::CLC() {
    bit_manip::SetBit(status_register, CARRY, false);
    CompleteInstruction();
}

void CPU::CLD() {
    bit_manip::SetBit(status_register, DECIMAL, false);
    CompleteInstruction();
}

void CPU::CLI() {
    bit_manip::SetBit(status_register, INTERRUPT_DISABLE, false);
    CompleteInstruction();
}

void CPU::CLV() {
    bit_manip::SetBit(status_register, OVERFLOW, false);
    CompleteInstruction();
}