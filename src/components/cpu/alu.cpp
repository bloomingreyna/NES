#include <components/cpu.h>
#include <ns.h>

void CPU::QueryALU() {
    uint8_t mask{0xFF};
}

void CPU::ALUstatusUpdate(ALUresult alu_result) {
    status_register &= alu_result.clear_mask;
    status_register |= alu_result.status;
}