#include <components/cpu.h>
#include <ns.h>

ALUresult alu_functions::bitwise::AND(uint8_t accumulator, uint8_t memory) {
    uint8_t result{static_cast<uint8_t>(
        accumulator & memory
    )};
    
    uint8_t status{};
    bit_manip::SetBit(status, ZERO, result == 0);
    bit_manip::SetBit(status, NEGATIVE, bit_manip::BitSet(result, 7));

    return ALUresult{
        .result = result,
        .status = status,
        .clear_mask = 0xFF ^ (M_ZERO | M_NEGATIVE)
    };
}

ALUresult alu_functions::bitwise::OR(uint8_t accumulator, uint8_t memory) {
    uint8_t result{static_cast<uint8_t>(
        accumulator | memory
    )};

    uint8_t status{};
    bit_manip::SetBit(status, ZERO, result == 0);
    bit_manip::SetBit(status, NEGATIVE, bit_manip::BitSet(result, 7));

    return ALUresult{
        .result = result,
        .status = status,
        .clear_mask = 0xFF ^ (M_ZERO | M_NEGATIVE)
    };
}

ALUresult alu_functions::bitwise::XOR(uint8_t accumulator, uint8_t memory) {
    uint8_t result{static_cast<uint8_t>(
        accumulator ^ memory
    )};

    uint8_t status{};
    bit_manip::SetBit(status, ZERO, result == 0);
    bit_manip::SetBit(status, NEGATIVE, bit_manip::BitSet(result, 7));

    return ALUresult{
        .result = result,
        .status = status,
        .clear_mask = 0xFF ^ (M_ZERO | M_NEGATIVE)
    };
}

ALUresult alu_functions::bitwise::BitTest(uint8_t accumulator, uint8_t memory) {
    uint8_t result{static_cast<uint8_t>(
        accumulator & memory
    )};
    
    uint8_t status{};
    bit_manip::SetBit(status, ZERO, result == 0);
    bit_manip::SetBit(status, OVERFLOW, bit_manip::BitSet(result, 6));
    bit_manip::SetBit(status, NEGATIVE, bit_manip::BitSet(result, 7));

    return ALUresult{
        .status = status,
        .clear_mask = 0xFF ^ (M_ZERO | M_OVERFLOW | M_NEGATIVE)
    };
}