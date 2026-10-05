#include <array>

#include <components/cpu.h>
#include <ns.h>

ALUresult alu_functions::arithmetic::AddWithCarry(uint8_t accumulator, uint8_t memory, bool carry) {
    uint16_t result{static_cast<uint8_t>(carry)};
    result += static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(memory);

    std::array<StatusFlags, 4> flags{
        StatusFlags::CARRY,
        StatusFlags::ZERO,
        StatusFlags::OVERFLOW,
        StatusFlags::NEGATIVE
    };
    std::array<bool, 4> conditions{
        result > 0xFF,
        (result & 0xFF) == 0,
        ((result ^ accumulator) & (result ^ memory) & 0x80) != 0,
        bit_manip::BitSet(static_cast<uint8_t>(result), 7)
    };

    uint8_t status{};
    for (size_t i{}; i < 4; ++i) {
        status |= static_cast<uint8_t>(flags[i]) * conditions[i];
    }

    return ALUresult{
        .result = static_cast<uint8_t>(result),
        .status = status,
        .clear_mask = 0x0C
    };
}

ALUresult alu_functions::arithmetic::Increment(uint8_t memory) {
    uint16_t result{static_cast<uint16_t>(static_cast<uint16_t>(memory) + 1)};

    std::array<StatusFlags, 2> flags{
        StatusFlags::ZERO,
        StatusFlags::NEGATIVE
    };
    std::array<bool, 2> conditions{
        (result & 0xFF) == 0,
        bit_manip::BitSet(static_cast<uint8_t>(result), 7)
    };

    uint8_t status{};
    for (size_t i{}; i < 2; ++i) {
        status |= static_cast<uint8_t>(flags[i]) * conditions[i];
    }

    return ALUresult{
        .result = static_cast<uint8_t>(result),
        .status = status,
        .clear_mask = 0x82
    };
}

ALUresult alu_functions::arithmetic::Decrement(uint8_t memory) {
    uint16_t result{static_cast<uint16_t>(static_cast<uint16_t>(memory) - 1)};

    std::array<StatusFlags, 2> flags{
        StatusFlags::ZERO,
        StatusFlags::NEGATIVE
    };
    std::array<bool, 2> conditions{
        (result & 0xFF) == 0,
        bit_manip::BitSet(static_cast<uint8_t>(result), 7)
    };

    uint8_t status{};
    for (size_t i{}; i < 2; ++i) {
        status |= static_cast<uint8_t>(flags[i]) * conditions[i];
    }

    return ALUresult{
        .result = static_cast<uint8_t>(result),
        .status = status,
        .clear_mask = 0x82
    };
}