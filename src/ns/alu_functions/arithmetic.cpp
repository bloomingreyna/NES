#include <array>

#include <components/cpu.h>
#include <ns.h>

ALUresult alu_functions::arithmetic::AddWithCarry(uint8_t accumulator, uint8_t memory, bool carry) {
    uint16_t result{static_cast<uint8_t>(carry)};
    result += static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(memory);

    uint8_t status{};
    bit_manip::SetBit(status, CARRY, result > 0xFF);
    bit_manip::SetBit(status, ZERO, (result & 0xFF) == 0x00);
    bit_manip::SetBit(status, OVERFLOW, ((result ^ accumulator) & (result ^ memory) & 0x80) != 0);
    bit_manip::SetBit(status, NEGATIVE, bit_manip::BitSet(status, 7));

    return ALUresult{
        .result = static_cast<uint8_t>(result),
        .status = status,
        .clear_mask = 0xFF ^ (M_CARRY | M_ZERO | M_OVERFLOW | M_NEGATIVE)
    };
}

ALUresult alu_functions::arithmetic::Increment(uint8_t memory) {
    uint16_t result{static_cast<uint16_t>(static_cast<uint16_t>(memory) + 1)};

    uint8_t status{};
    bit_manip::SetBit(status, ZERO, (result & 0xFF) == 0);
    bit_manip::SetBit(status, NEGATIVE, bit_manip::BitSet(result, 7));

    return ALUresult{
        .result = static_cast<uint8_t>(result),
        .status = status,
        .clear_mask = 0xFF ^ (M_ZERO | M_NEGATIVE)
    };
}

ALUresult alu_functions::arithmetic::Decrement(uint8_t memory) {
    uint16_t result{static_cast<uint16_t>(static_cast<uint16_t>(memory) - 1)};

    uint8_t status{};
    bit_manip::SetBit(status, ZERO, (result & 0xFF) == 0);
    bit_manip::SetBit(status, NEGATIVE, bit_manip::BitSet(result, 7));

    return ALUresult{
        .result = static_cast<uint8_t>(result),
        .status = status,
        .clear_mask = 0xFF ^ (M_ZERO | M_NEGATIVE)
    };
}