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

enum AddressingMode {
    IMMEDIATE,
    ZERO_PAGE, ZERO_PAGE_X, ZERO_PAGE_Y,
    ABSOLUTE, ABSOLUTE_X, ABSOLUTE_Y,
    INDIRECT, INDIRECT_X, INDIRECT_Y,

    MODE_COUNT
};

enum Opcode {
    ADC_IMM = 0x69,
    ADC_ZP = 0x65,
    ADC_ZP_X = 0x75,
    ADC_ABS = 0x6D,
    ADC_ABS_X = 0x7D,
    ADC_ABS_Y = 0x79,
    ADC_IND_X = 0x61,
    ADC_IND_Y = 0x71,

    STA_ZP = 0x85,
    STA_ZP_X = 0x95,
    STA_ABS = 0x8D,
    STA_ABS_X = 0x9D,
    STA_ABS_Y = 0x99,
    STA_IND_X = 0x81,
    STA_IND_Y = 0x91
};

struct ALUresult {
    uint8_t result{};
    uint8_t status{};
    uint8_t clear_mask{};
};

class AddressBus;

class CPU {
public:
    CPU(AddressBus& _bus);

    void FetchInstruction();
    void ExecuteInstruction();

    void QueueImmediateAddrMode();
    void QueueZeroPageAddrMode();
    void QueueZeroPageIndexedAddrMode(uint8_t index);
    void QueueAbsAddrMode();
    void QueueAbsIndexedAddrMode(uint8_t index);
    void QueueIndirectAddrMode();
    void QueueIndirectXAddrMode();
    void QueueIndirectYAddrMode();

    void QueryALU();
    void ALUstatusUpdate();

    void ADChandler();
private:
    AddressBus& bus;

    Opcode opcode;
    uint8_t byte_2;
    uint8_t byte_3;
    uint8_t memory_store;

    std::array<std::function<void()>, MODE_COUNT> addressing_modes;

    ALUresult alu_result;

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