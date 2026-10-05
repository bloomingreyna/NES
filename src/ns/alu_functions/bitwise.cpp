#include <array>

#include <components/cpu.h>
#include <ns.h>

ALUresult alu_functions::bitwise::And(uint8_t accumulator, uint8_t memory) {
    uint8_t result = accumulator & memory;

}