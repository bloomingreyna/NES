#include <components/address_bus.h>
#include <components/cpu.h>
#include <ns.h>

void CPU::QueueImmediateAddrMode() {
    byte_2 = bus.ReadMemory(program_counter + 1);
    memory_store = byte_2;
}

void CPU::QueueZeroPageAddrMode() {
    task_queue.emplace([this, pc{program_counter}]() {
        byte_2 = bus.ReadMemory(pc + 1);
        memory_store = bus.ReadMemory(byte_2);
    });
}

void CPU::QueueZeroPageIndexedAddrMode(uint8_t index) {
    task_queue.emplace([this, pc{program_counter}]() {
        byte_2 = bus.ReadMemory(pc + 1);
        memory_store = bus.ReadMemory(byte_2);
    });
    task_queue.emplace([this, index]() {
        memory_store += index;
    });
}

void CPU::QueueAbsAddrMode() {
    task_queue.emplace([this, pc{program_counter}]() {
        byte_2 = bus.ReadMemory(pc + 1);
    });
    task_queue.emplace([this, pc{program_counter}]() {
        byte_3 = bus.ReadMemory(pc + 2);

        uint16_t address{static_cast<uint16_t>(
            (byte_3 << 8) | byte_2
        )};
        memory_store = bus.ReadMemory(address);
    });
}

void CPU::QueueAbsIndexedAddrMode(uint8_t index) {
    task_queue.emplace([this, pc{program_counter}]() {
        byte_2 = bus.ReadMemory(pc + 1);
    });
    task_queue.emplace([this, pc{program_counter}, index]() {
        ALUresult calc_low_byte{alu_functions::arithmetic::AddWithCarry(
            byte_2,
            index,
            false
        )};

        byte_3 = bus.ReadMemory(pc + 2);

        uint16_t address{static_cast<uint16_t>(
            (byte_3 << 8) | calc_low_byte.result
        )};
        memory_store = bus.ReadMemory(address);

        if (!bit_manip::BitSet(calc_low_byte.status, CARRY)) {
            task_queue.pop();
        }
    });
    task_queue.emplace([this, index]() {
        uint16_t address{static_cast<uint16_t>(
            (byte_3 << 8) | byte_2
        )};
        memory_store = bus.ReadMemory(address + index);
    });
}