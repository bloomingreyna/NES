#include <cstdint>

#include <components/cpu.h>

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

namespace branch_instructions {
    void Branch(uint16_t& pc, int8_t memory, bool condition);
}

namespace flag_instructions {
    void ClearFlag(uint8_t& status, StatusFlag flag);
    void SetFlag(uint8_t& status, StatusFlag flag);
}

namespace stack_instructions {
    void Push(uint8_t& stack_value, uint8_t& stack_pointer, uint8_t reg);
    void Pull(uint8_t stack_value, uint8_t& stack_pointer, uint8_t& reg);

    void TransferX(uint8_t& stack_pointer, uint8_t x);
}

namespace transfer_instructions {
    void Transfer(uint8_t src_reg, uint8_t& dest_reg, uint8_t& status);
}