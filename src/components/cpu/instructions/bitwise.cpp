#include <components/cpu.h>
#include <ns.h>

void CPU::AND() {
    ALUresult alu_result{alu_functions::bitwise::AND(
        accumulator, memory_store
    )};
    accumulator = alu_result.result;
    ALUstatusUpdate(alu_result);

    CompleteInstruction();
}

void CPU::BIT() {
    ALUresult alu_result{alu_functions::bitwise::BitTest(
        accumulator, memory_store
    )};
    ALUstatusUpdate(alu_result);

    CompleteInstruction();
}