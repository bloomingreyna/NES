#include <cassert>
#include <cstdint>
#include <functional>
#include <vector>

enum class StatusFlags;

struct ALUresult;

namespace alu_functions {
    uint8_t GenerateStatus(const std::vector<StatusFlags>& flags, const std::vector<std::function<bool()>>& conditions) {
        assert(flags.size() == conditions.size());

        uint8_t status{};
        for (size_t i{}; i < flags.size(); ++i) {
            status |= static_cast<uint8_t>(flags[i]) * conditions[i]();
        }
        return status;
    }

    namespace arithmetic {
        // Internally, SBC is implemented via ADC and inverting the memory.
        ALUresult AddWithCarry(uint8_t accumulator, uint8_t memory, bool carry);
        ALUresult Increment(uint8_t memory);
        ALUresult Decrement(uint8_t memory);
    }
    namespace bitwise {
        ALUresult And(uint8_t accumulator, uint8_t memory);
    }
}

namespace bit_manip {
    bool BitSet(uint8_t data, size_t bit);
    void SetBit(uint8_t& data, size_t bit, bool value);
}