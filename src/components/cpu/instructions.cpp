#include <components/address_bus.h>
#include <components/cpu.h>
#include <ns.h>

void CPU::ADC() {
    task_queue.emplace([this]() {
        ALUresult alu_result{alu_functions::arithmetic::AddWithCarry(
            accumulator, memory_store, bit_manip::BitSet(status_register, CARRY)
        )};
        accumulator = alu_result.result;
        ALUstatusUpdate(alu_result);
    });
}

void CPU::AND() {
    task_queue.emplace([this]() {
        ALUresult alu_result{alu_functions::bitwise::AND(
            accumulator, memory_store
        )};
        accumulator = alu_result.result;
        ALUstatusUpdate(alu_result);
    });
}

// ...

void CPU::BIT() {
    task_queue.emplace([this]() {
        ALUresult alu_result{alu_functions::bitwise::BitTest(
            accumulator, memory_store
        )};
        ALUstatusUpdate(alu_result);
    });
}

// ...

void CPU::BRK() {
    task_queue.emplace([this]() {
        program_counter++;
    });
    task_queue.emplace([this]() {
        bus.WriteMemory(stack_pointer--, program_counter >> 8);
    });
    task_queue.emplace([this]() {
        bus.WriteMemory(stack_pointer--, program_counter & 0xFF);
    });
    task_queue.emplace([this]() {
        bus.WriteMemory(stack_pointer--, status_register | 0b00110000);
    });
    task_queue.emplace([this]() {
        memory_store &= 0xFF00;
        memory_store |= bus.ReadMemory(0xFFFE);
    });
    task_queue.emplace([this]() {
        memory_store &= 0xFF;
        memory_store |= bus.ReadMemory(0xFFFF) << 8;

        program_counter = memory_store;
        bit_manip::SetBit(status_register, INTERRUPT_DISABLE, true);
    });
}

void CPU::CLC() {
    
}