#include <components/cpu.h>
#include <ns.h>

void flag_instructions::ClearCarry(uint8_t& status) {
    bit_manip::SetBit(status, CARRY, false);
}

void SetCarry(uint8_t& status) {
    bit_manip::SetBit(status, CARRY, true);
}

void ClearInterruptDisable(uint8_t& status) {
    bit_manip::SetBit(status, INTERRUPT_DISABLE, false);
}

void SetInterruptDisable(uint8_t& status) {
    bit_manip::SetBit(status, INTERRUPT_DISABLE, true);
}

void ClearDecimal(uint8_t& status) {
    bit_manip::SetBit(status, DECIMAL, false);
}

void SetDecimal(uint8_t& status) {
    bit_manip::SetBit(status, DECIMAL, true);
}

void ClearOverflow(uint8_t& status) {
    bit_manip::SetBit(status, OVERFLOW, false);
}