#include <cstdint>

class AddressBus {
public:
    uint8_t ReadMemory(uint16_t address);
    void WriteMemory(uint16_t address, uint8_t value);
private:
    uint8_t memory[];
};