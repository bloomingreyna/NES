#include <ns.h>

void jump_instructions::Jump(uint16_t& program_counter, uint16_t memory) {
    program_counter = memory;
}

void jump_instructions::JumpToSubroutine(uint16_t& program_counter, uint16_t memory, uint8_t& stack_value_high, uint8_t& stack_value_low, uint8_t& stack_pointer) {
    stack_value_high = program_counter >> 8;
    stack_value_low = program_counter & 0xFF;
    stack_pointer -= 2;

    program_counter = memory;
}

void jump_instructions::ReturnFromSubroutine(uint16_t& program_counter, uint8_t stack_value_high, uint8_t stack_value_low, uint8_t& stack_pointer) {
    program_counter = (stack_value_high << 8) | stack_value_low;
    stack_pointer += 2;
}

void jump_instructions::Break(uint16_t& program_counter, uint8_t& status, bool& service_interrupts, uint8_t& stack_value_high, uint8_t& stack_value_low, uint8_t& stack_value_status, uint8_t& stack_pointer) {
    stack_value_high = program_counter >> 8;
    stack_value_low = program_counter & 0xFF;
    stack_value_status = status | 0b00110000;
    stack_pointer -= 3;

    bit_manip::SetBit(status, INTERRUPT_DISABLE, true);
    service_interrupts = false;

    program_counter = 0xFFFE;
}