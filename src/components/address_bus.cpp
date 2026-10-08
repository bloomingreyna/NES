#include <components/address_bus.h>

uint8_t AddressBus::ReadMemory(uint16_t address) {
    return memory[address];
}

void AddressBus::WriteMemory(uint16_t address, uint8_t value) {
    memory[address] = value;
}

void AddressBus::WriteToStack(uint16_t stack_pointer, uint8_t value) {
    memory[0x0100 + stack_pointer] = value;
}