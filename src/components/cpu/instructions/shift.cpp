#include <components/address_bus.h>
#include <components/cpu.h>
#include <ns.h>

void CPU::ArithmeticShiftLeftAccumulator() {
    ALUresult alu_result{alu_functions::shift::ArithmeticShiftLeft(accumulator)};
    accumulator = alu_result.result;
    ALUstatusUpdate(alu_result);

    CompleteInstruction();
}

void CPU::ArithmeticShiftLeft() {
    switch (current_internal_op) {
    case 1: {
        memory_store = bus.ReadMemory(address_store);
        break;
    }
    case 2: {
        bus.WriteMemory(address_store, memory_store);
        ALUresult alu_result{alu_functions::shift::ArithmeticShiftLeft(memory_store)};
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

void CPU::LogicalShiftRightAccumulator() {
    ALUresult alu_result{alu_functions::shift::LogicalShiftRight(accumulator)};
    accumulator = alu_result.result;
    ALUstatusUpdate(alu_result);

    CompleteInstruction();
}

void CPU::LogicalShiftRight() {
    switch (current_internal_op) {
    case 1: {
        memory_store = bus.ReadMemory(address_store);
        break;
    }
    case 2: {
        bus.WriteMemory(address_store, memory_store);
        ALUresult alu_result{alu_functions::shift::LogicalShiftRight(memory_store)};
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

void CPU::RotateLeftAccumulator() {
    ALUresult alu_result{alu_functions::shift::RotateLeft(
        accumulator, bit_manip::BitSet(status_register, CARRY)
    )};
    accumulator = alu_result.result;
    ALUstatusUpdate(alu_result);

    CompleteInstruction();
}

void CPU::RotateLeft() {
    switch (current_internal_op) {
    case 1: {
        memory_store = bus.ReadMemory(address_store);
        break;
    }
    case 2: {
        bus.WriteMemory(address_store, memory_store);
        ALUresult alu_result{alu_functions::shift::RotateLeft(
            memory_store, bit_manip::BitSet(status_register, CARRY)
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

void CPU::RotateRightAccumulator() {
    ALUresult alu_result{alu_functions::shift::RotateRight(
        accumulator, bit_manip::BitSet(status_register, CARRY)
    )};
    accumulator = alu_result.result;
    ALUstatusUpdate(alu_result);

    CompleteInstruction();
}

void CPU::RotateRight() {
    switch (current_internal_op) {
    case 1: {
        memory_store = bus.ReadMemory(address_store);
        break;
    }
    case 2: {
        bus.WriteMemory(address_store, memory_store);
        ALUresult alu_result{alu_functions::shift::RotateRight(
            memory_store, bit_manip::BitSet(status_register, CARRY)
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