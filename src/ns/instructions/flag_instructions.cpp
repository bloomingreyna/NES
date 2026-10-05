#include <components/cpu.h>
#include <ns.h>

void flag_instructions::ClearFlag(uint8_t& status, StatusFlag flag) {
    status &= ~(1 << flag);
}

void flag_instructions::SetFlag(uint8_t& status, StatusFlag flag) {
    status |= 1 << flag;
}