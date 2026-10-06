#include <array>
#include <functional>
#include <unordered_set>

#include <components/address_bus.h>
#include <components/cpu.h>
#include <ns.h>

CPU::CPU(AddressBus& _bus) : bus(_bus) {
    addressing_modes.at(IMMEDIATE) = [this]() { QueueImmediateAddrMode(); };
    addressing_modes.at(ZERO_PAGE) = [this]() { QueueZeroPageAddrMode(); };
    addressing_modes.at(ZERO_PAGE_X) = [this]() { QueueZeroPageIndexedAddrMode(x_index); };
    addressing_modes.at(ZERO_PAGE_Y) = [this]() { QueueZeroPageIndexedAddrMode(y_index); };
    addressing_modes.at(ABSOLUTE) = [this]() { QueueAbsAddrMode(); };
    addressing_modes.at(ABSOLUTE_X) = [this]() { QueueAbsIndexedAddrMode(x_index); };
    addressing_modes.at(ABSOLUTE_Y) = [this]() { QueueAbsIndexedAddrMode(y_index); };
}

void CPU::FetchInstruction() {
    opcode = static_cast<Opcode>(bus.ReadMemory(program_counter));
}

void CPU::ExecuteInstruction() {
    if (!task_queue.empty()) {
        task_queue.front()();
    } else {
        FetchInstruction();
    }
}

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
        byte_3 = bus.ReadMemory(pc + 2);

        uint16_t address{static_cast<uint16_t>(
            (byte_3 << 8) | byte_2
        )};
        uint16_t result = address + index;
        memory_store = bus.ReadMemory(result);

        bool page_crossed{static_cast<bool>(
            (address ^ index ^ result) & 0x0100
        )};
        if (page_crossed) {
            task_queue.emplace([]() {});
        }
    });
}

void CPU::QueryALU() {
    uint8_t mask{0xFF};
}

void CPU::ALUstatusUpdate() {
    status_register &= alu_result.clear_mask;
    status_register |= alu_result.status;
}

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