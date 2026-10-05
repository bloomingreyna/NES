#include <components/cpu.h>
#include <ns.h>

void flag_instructions::ClearFlag(uint8_t& status, StatusFlag flag) {
    status &= ~(1 << flag);
}

void flag_instructions::SetFlag(uint8_t& status, StatusFlag flag) {
    status |= 1 << flag;
}

void flag_instructions::ClearInterruptDisable(uint8_t& status, InterruptServiceDelay& isd) {
    status &= ~(1 << INTERRUPT_DISABLE);
    isd = static_cast<InterruptServiceDelay>(false);
}

void flag_instructions::SetInterruptDisable(uint8_t& status, InterruptServiceDelay& isd) {
    status |= 1 << INTERRUPT_DISABLE;
    isd = static_cast<InterruptServiceDelay>(true);
}