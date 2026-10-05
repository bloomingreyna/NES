#include <cstdint>

enum StatusFlags {
    CARRY = 0,
    ZERO = 1,
    INTERRUPT_DISABLE = 2,
    DECIMAL = 3,
    OVERFLOW = 6,
    NEGATIVE = 7
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