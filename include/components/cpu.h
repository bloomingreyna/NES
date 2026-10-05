#pragma once

#include <cstdint>
#include <functional>
#include <queue>

enum StatusFlag {
    CARRY = 0,
    ZERO = 1,
    INTERRUPT_DISABLE = 2,
    DECIMAL = 3,
    OVERFLOW = 6,
    NEGATIVE = 7
};

enum StatusFlagMasks {
    M_CARRY = 0b00000001,
    M_ZERO = 0b00000010,
    M_INTERRUPT_DISABLE = 0b00000100,
    M_DECIMAL = 0b00001000,
    M_OVERFLOW = 0b01000000,
    M_NEGATIVE = 0b10000000
};

enum InterruptServiceDelay {
    ISD_FALSE,
    ISD_TRUE,
    ISD_NONE
};

struct ALUresult {
    uint8_t result{};
    uint8_t status{};
    uint8_t clear_mask{};
};

class CPU {
public:
    void FetchInstruction();
    void ExecuteInstruction();

    void QueryALU(uint8_t opcode);
private:
    uint8_t accumulator{};
    uint8_t status_register{};

    uint8_t x_index{};
    uint8_t y_index{};

    uint16_t program_counter{};
    uint8_t stack_pointer{};

    bool service_interrupts{false};
    InterruptServiceDelay isd{ISD_NONE};

    std::queue<std::function<void()>> task_queue{};
};