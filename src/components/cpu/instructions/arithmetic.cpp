#include <components/address_bus.h>
#include <components/cpu.h>
#include <ns.h>

void CPU::AddWithCarry() {
    ALUresult alu_result{alu_functions::arithmetic::AddWithCarry(
        accumulator,
        bus.ReadMemory(address_store),
        bit_manip::BitSet(status_register, CARRY)
    )};
    accumulator = alu_result.result;
    ALUstatusUpdate(alu_result);

    CompleteInstruction();
}

void CPU::IncrementMemory() {
    switch (current_internal_op) {
    case 1: {
        memory_store = bus.ReadMemory(address_store);
        break;
    }
    case 2: {
        bus.WriteMemory(address_store, memory_store);
        ALUresult alu_result{alu_functions::arithmetic::Increment(
            bus.ReadMemory(address_store)
        )};
        memory_store = alu_result.result;
        ALUstatusUpdate(alu_result);
        break;
    }
    case 3: {
        bus.WriteMemory(address_store, memory_store);

        CompleteInstruction();
        break;
    }
    }
}

void CPU::IncrementIndex(uint8_t& index) {
    ALUresult alu_result{alu_functions::arithmetic::Increment(
        bus.ReadMemory(address_store)
    )};
    index = alu_result.result;
    ALUstatusUpdate(alu_result);

    CompleteInstruction();
}