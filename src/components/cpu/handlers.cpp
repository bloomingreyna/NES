#include <components/address_bus.h>
#include <components/cpu.h>
#include <ns.h>

void CPU::ADChandler() {
    task_queue.emplace([this]() {
        alu_result = alu_functions::arithmetic::AddWithCarry(
            accumulator,
            memory_store,
            bit_manip::BitSet(status_register, CARRY)
        );
        accumulator = alu_result.result;
        ALUstatusUpdate();
    });
}