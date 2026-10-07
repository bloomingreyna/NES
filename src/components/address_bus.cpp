#include <components/address_bus.h>

uint8_t AddressBus::ReadMemory(uint16_t address) {
    return memory[address];
}

void AddressBus::WriteMemory(uint16_t address, uint8_t value) {
    memory[address] = value;
}