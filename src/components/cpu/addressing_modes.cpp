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
    });
    task_queue.emplace([this, index]() {
        byte_2 += index;
        memory_store = bus.ReadMemory(byte_2);
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

        bool store_instruction{
            opcode == STA_ABS_X || opcode == STA_ABS_Y
        };
        if (!store_instruction && !bit_manip::BitSet(calc_low_byte.status, CARRY)) {
            task_queue.pop(); // Pops THIS task, instruction executor pops "oops" cycle.
        }
    });
    task_queue.emplace([this, index]() {
        uint16_t address{static_cast<uint16_t>(
            (byte_3 << 8) | byte_2
        )};
        memory_store = bus.ReadMemory(address + index);
    });
}

void CPU::QueueIndirectAddrMode() {
    task_queue.emplace([this, pc{program_counter}]() {
        byte_2 = bus.ReadMemory(pc + 1);
    });
    task_queue.emplace([this, pc{program_counter}]() {
        byte_3 = bus.ReadMemory(pc + 2);
    });
    task_queue.emplace([this]() {
        uint16_t ptr_address{static_cast<uint16_t>(
            (bus.ReadMemory(byte_3) << 8) | bus.ReadMemory(byte_2)
        )};
        memory_store = bus.ReadMemory(ptr_address);
    });
}

void CPU::QueueIndirectXAddrMode() {
    task_queue.emplace([this, pc{program_counter}]() {
        byte_2 = bus.ReadMemory(pc + 1);
    });
    task_queue.emplace([this]() {
        byte_2 += x_index;
    });
    task_queue.emplace([this]() {
        byte_3 = byte_2 + 1;
    });
    task_queue.emplace([this]() {
        uint16_t ptr_address{static_cast<uint16_t>(
            (bus.ReadMemory(byte_3) << 8) | bus.ReadMemory(byte_2)
        )};
        memory_store = bus.ReadMemory(ptr_address);
    });
}

void CPU::QueueIndirectYAddrMode() {
    task_queue.emplace([this, pc{program_counter}]() {
        byte_2 = bus.ReadMemory(pc + 1);
    });
    task_queue.emplace([this]() {
        byte_3 = byte_2 + 1;
    });
    task_queue.emplace([this]() {
        ALUresult calc_low_byte{alu_functions::arithmetic::AddWithCarry(
            bus.ReadMemory(byte_2),
            y_index,
            false
        )};

        uint16_t ptr_address{static_cast<uint16_t>(
            (bus.ReadMemory(byte_3) << 8) | bus.ReadMemory(calc_low_byte.result)
        )};
        memory_store = bus.ReadMemory(ptr_address);
    });
    task_queue.emplace([this]() {
        uint16_t ptr_address{static_cast<uint16_t>(
            (bus.ReadMemory(byte_3) << 8) | bus.ReadMemory(byte_2)
        )};
        memory_store = bus.ReadMemory(ptr_address + y_index);
    });
}