#include <components/memory_bus.h>
#include <components/cpu.h>
#include <ns.h>

void CPU::AddWithCarry() {
    alu = alu_functions::arithmetic::AddWithCarry(
        accumulator,
        data_bus,
        bit_manip::BitSet(status_register, CARRY)
    );
    accumulator = alu.result;
    ALUstatusUpdate(alu);

    CompleteInstruction();
}

void CPU::IncrementMemory() {
    switch (current_internal_op) {
    case 1: break; // Read data
    case 2: {
        rw_signal = WRITE;

        alu = alu_functions::arithmetic::Increment(
            data_bus
        );
        ALUstatusUpdate(alu);
        break;
    }
    case 3: {
        data_bus = alu.result;

        CompleteInstruction();
        break;
    }
    }
}

void CPU::IncrementIndex(uint8_t& index) {
    alu = alu_functions::arithmetic::Increment(
        bus.ReadMemory(address_bus)
    );
    index = alu.result;
    ALUstatusUpdate(alu);

    CompleteInstruction();
}