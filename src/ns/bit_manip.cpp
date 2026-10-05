#include <cassert>

#include <ns.h>

bool bit_manip::BitSet(uint8_t data, size_t bit) {
    assert(bit >= 0 && bit < 8);
    return (data & (1 << bit)) != 0;
}

void bit_manip::SetBit(uint8_t& data, size_t bit, bool value) {
    assert(bit >= 0 && bit < 8);
    data &= ~(1 << bit);
    data |= value << bit;
}