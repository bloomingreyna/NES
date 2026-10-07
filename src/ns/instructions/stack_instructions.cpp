#include <components/cpu.h>
#include <ns.h>

void stack_instructions::PushA(uint8_t& stack_value, uint8_t& stack_pointer, uint8_t a) {
    stack_value = a;
    stack_pointer--;
}

void stack_instructions::PullA(uint8_t stack_value, uint8_t& stack_pointer, uint8_t& a) {
    a = stack_value;
    stack_pointer++;
}

void stack_instructions::PushStatus(uint8_t& stack_value, uint8_t& stack_pointer, uint8_t status) {
    stack_value = status | 0b00110000;
    stack_pointer--;
}

void stack_instructions::PullStatus(uint8_t stack_value, uint8_t& stack_pointer, uint8_t& status, InterruptServiceDelay& isd) {
    status = (stack_value & 0b11001111) | (status & 0b00110000);
    stack_pointer++;

    isd = static_cast<InterruptServiceDelay>(!bit_manip::BitSet(status, INTERRUPT_DISABLE));
}

void stack_instructions::TransferX(uint8_t& stack_pointer, uint8_t x) {
    stack_pointer = x;
}