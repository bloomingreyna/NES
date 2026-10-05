#include <components/cpu.h>
#include <ns.h>

void transfer_instructions::Transfer(uint8_t src_reg, uint8_t& dest_reg, uint8_t& status) {
    dest_reg = src_reg;
    status &= 0xFF ^ (M_ZERO | M_NEGATIVE);
    bit_manip::SetBit(status, ZERO, src_reg == 0);
    bit_manip::SetBit(status, NEGATIVE, bit_manip::BitSet(src_reg, 7));
}