#include <components/cpu.h>
#include <ns.h>

ALUresult alu_functions::shift::ArithmeticShiftLeft(uint8_t value) {
    uint8_t result{static_cast<uint8_t>(
        value << 1
    )};

    uint8_t status{};
    bit_manip::SetBit(status, CARRY, bit_manip::BitSet(value, 7));
    bit_manip::SetBit(status, ZERO, result == 0);
    bit_manip::SetBit(status, NEGATIVE, bit_manip::BitSet(result, 7));

    return ALUresult{
        .result = result,
        .status = status,
        .clear_mask = 0xFF ^ (M_CARRY | M_ZERO | M_NEGATIVE)
    };
}

ALUresult alu_functions::shift::LogicalShiftRight(uint8_t value) {
    uint8_t result{static_cast<uint8_t>(
        value >> 1
    )};

    uint8_t status{};
    bit_manip::SetBit(status, CARRY, bit_manip::BitSet(value, 0));
    bit_manip::SetBit(status, ZERO, result == 0);
    bit_manip::SetBit(status, NEGATIVE, false);

    return ALUresult{
        .result = result,
        .status = status,
        .clear_mask = 0xFF ^ (M_CARRY | M_ZERO | M_NEGATIVE)
    };
}

ALUresult alu_functions::shift::RotateLeft(uint8_t value, bool carry) {
    uint8_t shifted_value{static_cast<uint8_t>(
        value << 1
    )};
    uint8_t result{static_cast<uint8_t>(
        shifted_value | carry
    )};

    uint8_t status{};
    bit_manip::SetBit(status, CARRY, bit_manip::BitSet(value, 7));
    bit_manip::SetBit(status, ZERO, result == 0);
    bit_manip::SetBit(status, NEGATIVE, bit_manip::BitSet(result, 7));

    return ALUresult{
        .result = result,
        .status = status,
        .clear_mask = 0xFF ^ (M_CARRY | M_ZERO | M_NEGATIVE)
    };
}

ALUresult alu_functions::shift::RotateRight(uint8_t value, bool carry) {
    uint8_t shifted_value{static_cast<uint8_t>(
        value >> 1
    )};
    uint8_t carry_flag{static_cast<uint8_t>(
        carry << 7
    )};
    uint8_t result{static_cast<uint8_t>(
        shifted_value | carry_flag
    )};

    uint8_t status{};
    bit_manip::SetBit(status, CARRY, bit_manip::BitSet(value, 0));
    bit_manip::SetBit(status, ZERO, result == 0);
    bit_manip::SetBit(status, NEGATIVE, bit_manip::BitSet(result, 7));

    return ALUresult{
        .result = result,
        .status = status,
        .clear_mask = 0xFF ^ (M_CARRY | M_ZERO | M_NEGATIVE)
    };
}