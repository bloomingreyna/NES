#include <cstdint>

struct ALUresult;

namespace access_instructions {
    void Load(uint8_t& reg, uint8_t& status, uint8_t memory);
    void Store(uint8_t reg, uint8_t& memory);
}

namespace alu_functions {
    namespace arithmetic {
        // Internally, SBC is implemented via ADC and inverting the memory.
        ALUresult AddWithCarry(uint8_t accumulator, uint8_t memory, bool carry);

        ALUresult Increment(uint8_t memory);
        ALUresult Decrement(uint8_t memory);
    }
    namespace bitwise {
        ALUresult AND(uint8_t accumulator, uint8_t memory);
        ALUresult OR(uint8_t accumulator, uint8_t memory);
        ALUresult XOR(uint8_t accumulator, uint8_t memory);
        ALUresult BitTest(uint8_t accumulator, uint8_t memory);
    }
    namespace compare {
        ALUresult Compare(uint8_t reg, uint8_t memory);
    }
    namespace shift {
        ALUresult ArithmeticShiftLeft(uint8_t value);
        ALUresult LogicalShiftRight(uint8_t value);
        ALUresult RotateLeft(uint8_t value, bool carry);
        ALUresult RotateRight(uint8_t value, bool carry);
    }
}

namespace bit_manip {
    bool BitSet(uint8_t data, size_t bit);
    void SetBit(uint8_t& data, size_t bit, bool value);
}

namespace flag_instructions {
    void ClearCarry(uint8_t& status);
    void SetCarry(uint8_t& status);

    void ClearInterruptDisable(uint8_t& status);
    void SetInterruptDisable(uint8_t& status);

    void ClearDecimal(uint8_t& status);
    void SetDecimal(uint8_t& status);
    
    void ClearOverflow(uint8_t& status);
}

namespace transfer_instructions {
    void Transfer(uint8_t src_reg, uint8_t& dest_reg, uint8_t& status);
}