#include <components/cpu.h>
#include <ns.h>

void CPU::QueryALU() {
    uint8_t mask{0xFF};
}

void CPU::ALUstatusUpdate(ALU alu) {
    status_register &= alu.clear_mask;
    status_register |= alu.status;
}