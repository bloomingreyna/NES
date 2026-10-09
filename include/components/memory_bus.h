#pragma once

#include <cstdint>

class MemoryBus {
public:
    uint8_t ReadMemory(uint16_t address);
    uint8_t ReadStack(uint8_t stack_pointer);

    void WriteMemory(uint16_t address, uint8_t value);
    void WriteToStack(uint8_t stack_pointer, uint8_t value);
private:
    uint8_t memory[];
};