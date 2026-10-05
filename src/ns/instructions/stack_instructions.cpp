#include <ns.h>

void stack_instructions::Push(uint8_t& stack_value, uint8_t& stack_pointer, uint8_t reg) {
    stack_value = reg;
    stack_pointer--;
}

void stack_instructions::Pull(uint8_t stack_value, uint8_t& stack_pointer, uint8_t& reg) {
    reg = stack_value;
    stack_pointer++;
}

void stack_instructions::TransferX(uint8_t& stack_pointer, uint8_t x) {
    stack_pointer = x;
}