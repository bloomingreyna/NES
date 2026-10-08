#include <components/address_bus.h>
#include <components/cpu.h>
#include <ns.h>

void CPU::QueueImmediateAddrMode() {
    memory_store = bus.ReadMemory(program_counter++);

    address_mode_complete = true;
}

void CPU::QueueZeroPageAddrMode() {
    byte_2 = bus.ReadMemory(program_counter++);
    memory_store = bus.ReadMemory(byte_2);

    CompleteAddressMode();
}

void CPU::QueueZeroPageIndexedAddrMode(uint8_t index) {
    switch (current_internal_op) {
    case 0: {
        byte_2 = bus.ReadMemory(program_counter++);
        break;
    }
    case 1: {
        byte_2 += index;
        memory_store = bus.ReadMemory(byte_2);

        CompleteAddressMode();
        break;
    }
    }
}

void CPU::QueueAbsAddrMode() {
    switch (current_internal_op) {
    case 0: {
        byte_2 = bus.ReadMemory(program_counter++);
        break;
    }
    case 1: {
        byte_3 = bus.ReadMemory(program_counter++);

        uint16_t address{static_cast<uint16_t>(
            (byte_3 << 8) | byte_2
        )};
        memory_store = bus.ReadMemory(address);

        CompleteAddressMode();
        break;
    }
    }
}

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

        uint16_t address{static_cast<uint16_t>(
            (byte_3 << 8) | calc_low_byte.result
        )};
        memory_store = bus.ReadMemory(address);

        bool store_instruction{
            opcode == STA_ABS_X || opcode == STA_ABS_Y
        };

        if (!store_instruction && !bit_manip::BitSet(calc_low_byte.status, CARRY)) {
            CompleteAddressMode();
        }
        break;
    }
    case 2: {
        uint16_t address{static_cast<uint16_t>(
            (byte_3 << 8) | byte_2
        )};
        memory_store = bus.ReadMemory(address + index);

        CompleteAddressMode();
        break;
    }
    }
}

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
        memory_store = bus.ReadMemory(address);

        CompleteAddressMode();
        break;
    }
    }
}

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
        memory_store = bus.ReadMemory(address);

        CompleteAddressMode();
        break;
    }
    }
}

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
        memory_store = bus.ReadMemory(address);

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
        memory_store = bus.ReadMemory(address + y_index);

        CompleteAddressMode();
        break;
    }
    }
}