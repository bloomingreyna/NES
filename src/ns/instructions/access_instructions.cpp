#include <components/cpu.h>
#include <ns.h>

void access_instructions::Load(uint8_t& reg, uint8_t& status, uint8_t memory) {
    reg = memory;
    status &= 0xFF ^ (M_ZERO | M_NEGATIVE);
    bit_manip::SetBit(status, ZERO, memory == 0);
    bit_manip::SetBit(status, NEGATIVE, bit_manip::BitSet(memory, 7));
}

void access_instructions::Store(uint8_t reg, uint8_t& memory) {
    memory = reg;
}