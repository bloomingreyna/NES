#include <components/memory_bus.h>
#include <components/cpu.h>
#include <ns.h>

void CPU::ArithmeticShiftLeftAccumulator() {
    alu = alu_functions::shift::ArithmeticShiftLeft(accumulator);
    accumulator = alu.result;
    ALUstatusUpdate(alu);

    CompleteInstruction();
}

void CPU::ArithmeticShiftLeft() {
    switch (current_internal_op) {
    case 1: break; // Read data
    case 2: {
        rw_signal = WRITE;

        alu = alu_functions::shift::ArithmeticShiftLeft(data_bus);
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

void CPU::LogicalShiftRightAccumulator() {
    alu = alu_functions::shift::LogicalShiftRight(accumulator);
    accumulator = alu.result;
    ALUstatusUpdate(alu);

    CompleteInstruction();
}

void CPU::LogicalShiftRight() {
    switch (current_internal_op) {
    case 1: break; // Read data
    case 2: {
        rw_signal = WRITE;

        alu = alu_functions::shift::LogicalShiftRight(data_bus);
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

void CPU::RotateLeftAccumulator() {
    alu = alu_functions::shift::RotateLeft(
        accumulator, bit_manip::BitSet(status_register, CARRY)
    );
    accumulator = alu.result;
    ALUstatusUpdate(alu);

    CompleteInstruction();
}

void CPU::RotateLeft() {
    switch (current_internal_op) {
    case 1: break; // Read data
    case 2: {
        rw_signal = WRITE;

        alu = alu_functions::shift::RotateLeft(
            data_bus, bit_manip::BitSet(status_register, CARRY)
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

void CPU::RotateRightAccumulator() {
    alu = alu_functions::shift::RotateRight(
        accumulator, bit_manip::BitSet(status_register, CARRY)
    );
    accumulator = alu.result;
    ALUstatusUpdate(alu);

    CompleteInstruction();
}

void CPU::RotateRight() {
    switch (current_internal_op) {
    case 1: break; // Read data
    case 2: {
        rw_signal = WRITE;

        alu = alu_functions::shift::RotateRight(
            data_bus, bit_manip::BitSet(status_register, CARRY)
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