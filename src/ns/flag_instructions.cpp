#include <components/cpu.h>
#include <ns.h>

void flag_instructions::ClearCarry(uint8_t& status) {
    bit_manip::SetBit(status, CARRY, false);
}

void flag_instructions::SetCarry(uint8_t& status) {
    bit_manip::SetBit(status, CARRY, true);
}

void flag_instructions::ClearInterruptDisable(uint8_t& status) {
    bit_manip::SetBit(status, INTERRUPT_DISABLE, false);
}

void flag_instructions::SetInterruptDisable(uint8_t& status) {
    bit_manip::SetBit(status, INTERRUPT_DISABLE, true);
}

void flag_instructions::ClearDecimal(uint8_t& status) {
    bit_manip::SetBit(status, DECIMAL, false);
}

void flag_instructions::SetDecimal(uint8_t& status) {
    bit_manip::SetBit(status, DECIMAL, true);
}

void flag_instructions::ClearOverflow(uint8_t& status) {
    bit_manip::SetBit(status, OVERFLOW, false);
}