#include <components/cpu.h>
#include <ns.h>

ALUresult alu_functions::compare::Compare(uint8_t value, uint8_t memory) {
    uint8_t result{static_cast<uint8_t>(
        value - memory
    )};

    uint8_t status{};
    bit_manip::SetBit(status, CARRY, value >= memory);
    bit_manip::SetBit(status, ZERO, value == memory);
    bit_manip::SetBit(status, NEGATIVE, bit_manip::BitSet(result, 7));

    return ALUresult{
        .status = status,
        .clear_mask = 0xFF ^ (M_CARRY | M_ZERO | M_NEGATIVE)
    };
}