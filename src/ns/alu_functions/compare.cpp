#include <components/cpu.h>
#include <ns.h>

ALU alu_functions::compare::Compare(uint8_t reg, uint8_t memory) {
    uint8_t result{static_cast<uint8_t>(
        reg - memory
    )};

    uint8_t status{};
    bit_manip::SetBit(status, CARRY, reg >= memory);
    bit_manip::SetBit(status, ZERO, reg == memory);
    bit_manip::SetBit(status, NEGATIVE, bit_manip::BitSet(result, 7));

    return ALU{
        .status = status,
        .clear_mask = 0xFF ^ (M_CARRY | M_ZERO | M_NEGATIVE)
    };
}