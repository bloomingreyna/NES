#include <components/address_bus.h>
#include <components/cpu.h>
#include <ns.h>

void CPU::QueueADC() {
    task_queue.emplace([this]() {
        ALUresult alu_result{alu_functions::arithmetic::AddWithCarry(
            accumulator, memory_store, bit_manip::BitSet(status_register, CARRY)
        )};
        accumulator = alu_result.result;
        ALUstatusUpdate(alu_result);
    });
}

void CPU::QueueAND() {
    task_queue.emplace([this]() {
        ALUresult alu_result{alu_functions::bitwise::AND(
            accumulator, memory_store
        )};
        accumulator = alu_result.result;
        ALUstatusUpdate(alu_result);
    });
}

// ...

void CPU::QueueBIT() {
    task_queue.emplace([this]() {
        ALUresult alu_result{alu_functions::bitwise::BitTest(
            accumulator, memory_store
        )};
        ALUstatusUpdate(alu_result);
    });
}