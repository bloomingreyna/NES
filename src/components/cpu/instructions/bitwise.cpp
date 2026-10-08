#include <components/address_bus.h>
#include <components/cpu.h>
#include <ns.h>

void CPU::AND() {
    ALUresult alu_result{alu_functions::bitwise::AND(
        accumulator, bus.ReadMemory(address_store)
    )};
    accumulator = alu_result.result;
    ALUstatusUpdate(alu_result);

    CompleteInstruction();
}

void CPU::BitTest() {
    ALUresult alu_result{alu_functions::bitwise::BitTest(
        accumulator, bus.ReadMemory(address_store)
    )};
    ALUstatusUpdate(alu_result);

    CompleteInstruction();
}