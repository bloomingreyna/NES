#include <components/address_bus.h>
#include <components/cpu.h>
#include <ns.h>

void CPU::Compare(uint8_t reg) {
    ALUresult alu_result{alu_functions::compare::Compare(
        reg, bus.ReadMemory(address_store)
    )};
    ALUstatusUpdate(alu_result);

    CompleteInstruction();
}