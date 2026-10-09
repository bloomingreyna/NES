#include <components/memory_bus.h>
#include <components/cpu.h>
#include <ns.h>

void CPU::Break() {
    switch (current_internal_op) {
    case 1: break; // Dummy read
    case 2: {
        rw_signal = WRITE;

        data_bus = program_counter >> 8;
        address_bus = 0x0100 + stack_pointer--;
        break;
    }
    case 3: {
        data_bus = program_counter & 0xFF;
        address_bus = 0x0100 + stack_pointer--;
        break;
    }
    case 4: {
        data_bus = status_register | 0b00110000;
        address_bus = 0x0100 + stack_pointer--;
        break;
    }
    case 5: {
        rw_signal = READ;

        program_counter = bus.ReadMemory(0xFFFE);
        break;
    }
    case 6: {
        program_counter |= bus.ReadMemory(0xFFFF) << 8;

        bit_manip::SetBit(status_register, INTERRUPT_DISABLE, true);
        service_interrupts = false;

        CompleteInstruction();
        break;
    }
    }
}