#include <components/address_bus.h>

uint8_t& AddressBus::ReadMemory(uint16_t address) {
    return memory[address];
}