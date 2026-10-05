#include <components/cpu.h>
#include <ns.h>

ALUresult alu_functions::arithmetic::AddWithCarry(uint8_t accumulator, uint8_t memory, bool carry) {
    uint16_t result{static_cast<uint8_t>(carry)};
    result += static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(memory);

    static const std::vector<StatusFlags> flags{
        StatusFlags::CARRY,
        StatusFlags::ZERO,
        StatusFlags::OVERFLOW,
        StatusFlags::NEGATIVE
    };
    static const std::vector<std::function<bool()>> conditions{
        [result] { return result > 0xFF; },
        [result] { return (result & 0xFF) == 0; },
        [result, accumulator, memory] { return ((result ^ accumulator) & (result ^ memory) & 0x80) != 0; },
        [result] { return bit_manip::BitSet(static_cast<uint8_t>(result), 7); }
    };

    uint8_t status{GenerateStatus(flags, conditions)};

    return ALUresult{
        .result = static_cast<uint8_t>(result),
        .status = status,
        .clear_mask = 0x0C
    };
}

ALUresult alu_functions::arithmetic::Increment(uint8_t memory) {
    uint16_t result{static_cast<uint16_t>(static_cast<uint16_t>(memory) + 1)};

    static const std::vector<StatusFlags> flags{
        StatusFlags::ZERO,
        StatusFlags::NEGATIVE
    };
    static const std::vector<std::function<bool()>> conditions{
        [result] { return (result & 0xFF) == 0; },
        [result] { return bit_manip::BitSet(static_cast<uint8_t>(result), 7); }
    };

    uint8_t status{GenerateStatus(flags, conditions)};

    return ALUresult{
        .result = static_cast<uint8_t>(result),
        .status = status,
        .clear_mask = 0x82
    };
}

ALUresult alu_functions::arithmetic::Decrement(uint8_t memory) {
    uint16_t result{static_cast<uint16_t>(static_cast<uint16_t>(memory) - 1)};

    static const std::vector<StatusFlags> flags{
        StatusFlags::ZERO,
        StatusFlags::NEGATIVE
    };
    static const std::vector<std::function<bool()>> conditions{
        [result] { return (result & 0xFF) == 0; },
        [result] { return bit_manip::BitSet(static_cast<uint8_t>(result), 7); }
    };

    uint8_t status{GenerateStatus(flags, conditions)};

    return ALUresult{
        .result = static_cast<uint8_t>(result),
        .status = status,
        .clear_mask = 0x82
    };
}