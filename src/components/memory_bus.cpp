#include <components/memory_bus.h>

uint8_t MemoryBus::ReadMemory(uint16_t address) {
    return memory[address];
}

uint8_t MemoryBus::ReadStack(uint8_t stack_pointer) {
    return memory[0x0100 + stack_pointer];
}

void MemoryBus::WriteMemory(uint16_t address, uint8_t value) {
    memory[address] = value;
}

void MemoryBus::WriteToStack(uint8_t stack_pointer, uint8_t value) {
    memory[0x0100 + stack_pointer] = value;
}