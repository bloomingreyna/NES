#include <components/address_bus.h>
#include <components/cpu.h>
#include <ns.h>

// Zero extra cycles
void CPU::QueueImmediateAddrMode() {
    address_store = program_counter++;

    address_mode_complete = true;
}

// One extra cycle
void CPU::QueueZeroPageAddrMode() {
    address_store = bus.ReadMemory(program_counter++);

    CompleteAddressMode();
}

// Two extra cycles
void CPU::QueueZeroPageIndexedAddrMode(uint8_t index) {
    switch (current_internal_op) {
    case 0: {
        byte_2 = bus.ReadMemory(program_counter++);
        break;
    }
    case 1: {
        byte_2 += index;
        address_store = byte_2;

        CompleteAddressMode();
        break;
    }
    }
}

// Two extra cycles
void CPU::QueueAbsAddrMode() {
    switch (current_internal_op) {
    case 0: {
        byte_2 = bus.ReadMemory(program_counter++);
        break;
    }
    case 1: {
        byte_3 = bus.ReadMemory(program_counter++);
        address_store = (byte_3 << 8) | byte_2;

        CompleteAddressMode();
        break;
    }
    }
}

// Two to three extra cycles
void CPU::QueueAbsIndexedAddrMode(uint8_t index) {
    switch (current_internal_op) {
    case 0: {
        byte_2 = bus.ReadMemory(program_counter++);
        break;
    }
    case 1: {
        ALUresult calc_low_byte{alu_functions::arithmetic::AddWithCarry(
            byte_2, index, false
        )};
        byte_3 = bus.ReadMemory(program_counter++);

        address_store = (byte_3 << 8) | calc_low_byte.result;

        bool store_instruction{
            opcode == STA_ABS_X || opcode == STA_ABS_Y
        };

        if (!store_instruction && !bit_manip::BitSet(calc_low_byte.status, CARRY)) {
            CompleteAddressMode();
        }
        break;
    }
    case 2: {
        address_store = ((byte_3 << 8) | byte_2) + index;

        CompleteAddressMode();
        break;
    }
    }
}

// Three extra cycles
void CPU::QueueIndirectAddrMode() {
    switch (current_internal_op) {
    case 0: {
        byte_2 = bus.ReadMemory(program_counter++);
        break;
    }
    case 1: {
        byte_3 = bus.ReadMemory(program_counter++);
        break;
    }
    case 2: {
        uint16_t ptr_address{static_cast<uint16_t>(
            (byte_3 << 8) | byte_2
        )};
        uint16_t address{static_cast<uint16_t>(
            (bus.ReadMemory(ptr_address + 1) << 8) | bus.ReadMemory(ptr_address)
        )};
        address_store = address;

        CompleteAddressMode();
        break;
    }
    }
}

// Four extra cycles
void CPU::QueueIndirectXAddrMode() {
    switch (current_internal_op) {
    case 0: {
        byte_2 = bus.ReadMemory(program_counter++);
        break;
    }
    case 1: {
        byte_2 += x_index;
        break;
    }
    case 2: {
        byte_3 = byte_2 + 1;
        break;
    }
    case 3: {
        uint16_t address{static_cast<uint16_t>(
            (bus.ReadMemory(byte_3) << 8) | bus.ReadMemory(byte_2)
        )};
        address_store = address;

        CompleteAddressMode();
        break;
    }
    }
}

// Three to four extra cycles
void CPU::QueueIndirectYAddrMode() {
    switch (current_internal_op) {
    case 0: {
        byte_2 = bus.ReadMemory(program_counter++);
        break;
    }
    case 1: {
        byte_3 = byte_2 + 1;
        break;
    }
    case 2: {
        ALUresult calc_low_byte{alu_functions::arithmetic::AddWithCarry(
            bus.ReadMemory(byte_2), y_index, false
        )};

        uint16_t address{static_cast<uint16_t>(
            (bus.ReadMemory(byte_3) << 8) | calc_low_byte.result
        )};
        address_store = address;

        bool store_instruction{
            opcode == STA_ABS_X || opcode == STA_ABS_Y
        };

        if (!store_instruction && !bit_manip::BitSet(calc_low_byte.status, CARRY)) {
            CompleteAddressMode();
        }
        break;
    }
    case 3: {
        uint16_t address{static_cast<uint16_t>(
            (bus.ReadMemory(byte_3) << 8) | bus.ReadMemory(byte_2)
        )};
        address_store = address + y_index;

        CompleteAddressMode();
        break;
    }
    }
}