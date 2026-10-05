#include <cstdint>

enum class StatusFlags {
    CARRY = 0b00000001,
    ZERO = 0b00000010,
    INTERRUPT_DISABLE = 0b00000100,
    DECIMAL = 0b00001000,
    OVERFLOW = 0b01000000,
    NEGATIVE = 0b10000000
};

struct ALUresult {
    uint8_t result{};
    uint8_t status{};
    uint8_t clear_mask{};
};

class CPU {
public:
    void QueryALU(uint8_t opcode);
private:
    uint8_t accumulator;
    uint8_t status_register;

    uint8_t x_index;
    uint8_t y_index;

    uint16_t program_counter;
    uint8_t stack_pointer;
};