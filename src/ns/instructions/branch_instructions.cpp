#include <ns.h>

void branch_instructions::Branch(uint16_t& program_counter, int8_t memory, bool condition) {
    program_counter += 2 + memory * condition;
}