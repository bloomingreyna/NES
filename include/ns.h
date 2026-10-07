#include <cstdint>
#include <queue>

#include <components/cpu.h>

template <typename... Args>
using cycle = std::function<void(Args...)>;

struct ALUresult;

namespace access_instructions {
    namespace load {
        cycle<uint8_t&, uint8_t> c1{[](uint8_t& reg, uint8_t memory_store) {
            
        }};
    }
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
    
}

namespace flag_instructions {
    
}

namespace jump_instructions {
    
}

namespace stack_instructions {
    
}

namespace transfer_instructions {
    
}