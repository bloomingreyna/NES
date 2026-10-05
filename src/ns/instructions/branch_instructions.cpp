#include <components/cpu.h>
#include <ns.h>

void branch_instructions::Branch(uint16_t& pc, int8_t memory, bool condition) {
    if (condition) {
        pc += 2 + memory;
    }
}