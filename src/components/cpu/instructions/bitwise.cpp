#include <components/memory_bus.h>
#include <components/cpu.h>
#include <ns.h>

void CPU::AND() {
    alu = alu_functions::bitwise::AND(
        accumulator, bus.ReadMemory(address_bus)
    );
    accumulator = alu.result;
    ALUstatusUpdate(alu);

    CompleteInstruction();
}

void CPU::BitTest() {
    alu = alu_functions::bitwise::BitTest(
        accumulator, bus.ReadMemory(address_bus)
    );
    ALUstatusUpdate(alu);

    CompleteInstruction();
}