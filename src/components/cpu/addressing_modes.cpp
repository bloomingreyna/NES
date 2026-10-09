#include <components/memory_bus.h>
#include <components/cpu.h>
#include <ns.h>

// Zero extra cycles
void CPU::QueueImmediateAddrMode() {
    address_bus = program_counter++;

    address_mode_complete = true;
}

// One extra cycle
void CPU::QueueZeroPageAddrMode() {
    address_bus = bus.ReadMemory(program_counter++);

    CompleteAddressMode();
}

// Two extra cycles
void CPU::QueueZeroPageIndexedAddrMode(uint8_t index) {
    switch (current_internal_op) {
    case 0: {
        address_bus = bus.ReadMemory(program_counter++);
        break;
    }
    case 1: {
        address_bus += index;
        address_bus &= 0xFF;

        CompleteAddressMode();
        break;
    }
    }
}

// Two extra cycles
void CPU::QueueAbsAddrMode() {
    switch (current_internal_op) {
    case 0: {
        address_bus = bus.ReadMemory(program_counter++);
        break;
    }
    case 1: {
        address_bus |= bus.ReadMemory(program_counter++) << 8;

        CompleteAddressMode();
        break;
    }
    }
}

// Two to three extra cycles
void CPU::QueueAbsIndexedAddrMode(uint8_t index) {
    switch (current_internal_op) {
    case 0: {
        address_bus = bus.ReadMemory(program_counter++);
        break;
    }
    case 1: {
        address_bus |= bus.ReadMemory(program_counter++) << 8;

        alu = alu_functions::arithmetic::AddWithCarry(
            address_bus & 0xFF, index, false
        );

        bool store_instruction{
            opcode == STA_ABS_X || opcode == STA_ABS_Y
        };

        if (!store_instruction && !bit_manip::BitSet(alu.status, CARRY)) {
            address_bus = (address_bus & 0xFF) | alu.result;
            CompleteAddressMode();
        }
        break;
    }
    case 2: {
        address_bus += index;

        CompleteAddressMode();
        break;
    }
    }
}

// Four extra cycles
void CPU::QueueIndirectAddrMode() {
    switch (current_internal_op) {
    case 0: {
        address_bus = bus.ReadMemory(program_counter++);
        break;
    }
    case 1: {
        address_bus |= bus.ReadMemory(program_counter++) << 8;
        break;
    }
    case 2: {
        internal_addr_latch = bus.ReadMemory(address_bus);
        address_bus = (address_bus & 0xFF00) | ((address_bus + 1) & 0xFF);

        break;
    }
    case 3: {
        address_bus = (bus.ReadMemory(address_bus) << 8) | internal_addr_latch;

        CompleteAddressMode();
        break;
    }
    }
}

// Four extra cycles
void CPU::QueueIndirectXAddrMode() {
    switch (current_internal_op) {
    case 0: {
        address_bus = bus.ReadMemory(program_counter++);
        break;
    }
    case 1: {
        address_bus += x_index;
        address_bus &= 0xFF;
        break;
    }
    case 2: {
        internal_addr_latch = bus.ReadMemory(address_bus);
        address_bus++;
        address_bus &= 0xFF;
        break;
    }
    case 3: {
        address_bus = (bus.ReadMemory(address_bus) << 8) | internal_addr_latch;

        CompleteAddressMode();
        break;
    }
    }
}

// Three to four extra cycles
void CPU::QueueIndirectYAddrMode() {
    switch (current_internal_op) {
    case 0: {
        address_bus = bus.ReadMemory(program_counter++);
        break;
    }
    case 1: {
        internal_addr_latch = bus.ReadMemory(address_bus);
        address_bus++;
        address_bus &= 0xFF;
        break;
    }
    case 2: {
        address_bus = (bus.ReadMemory(address_bus) << 8) | internal_addr_latch;

        alu = alu_functions::arithmetic::AddWithCarry(
            address_bus & 0xFF, y_index, false
        );

        bool store_instruction{
            opcode == STA_ABS_X || opcode == STA_ABS_Y
        };

        if (!store_instruction && !bit_manip::BitSet(alu.status, CARRY)) {
            address_bus = (address_bus & 0xFF) | alu.result;
            CompleteAddressMode();
        }
        break;
    }
    case 3: {
        address_bus += y_index;

        CompleteAddressMode();
        break;
    }
    }
}