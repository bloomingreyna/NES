#include <components/memory_bus.h>
#include <components/cpu.h>
#include <ns.h>

void CPU::Compare(uint8_t reg) {
    alu = alu_functions::compare::Compare(
        reg, data_bus
    );
    ALUstatusUpdate(alu);

    CompleteInstruction();
}