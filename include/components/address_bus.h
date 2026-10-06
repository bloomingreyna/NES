#include <cstdint>

class AddressBus {
public:
    uint8_t& ReadMemory(uint16_t address);
private:
    uint8_t memory[];
};