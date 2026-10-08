#include <components/address_bus.h>
#include <components/cpu.h>
#include <ns.h>

void CPU::BRK() {
    switch (current_internal_op) {
    case 1: {
        bus.WriteToStack(stack_pointer--, program_counter >> 8);
        break;
    }
    case 2: {
        bus.WriteToStack(stack_pointer--, program_counter & 0xFF);
        break;
    }
    case 3: {
        bus.WriteToStack(stack_pointer--, status_register | 0b00110000);
        break;
    }
    case 4: {
        byte_2 = bus.ReadMemory(0xFFFE);
        break;
    }
    case 5: {
        byte_3 = bus.ReadMemory(0xFFFF);
        break;
    }
    case 6: {
        uint16_t interrupt_vector{static_cast<uint16_t>(
            (byte_3 << 8) | byte_2
        )};
        program_counter = interrupt_vector;

        CompleteInstruction();
        break;
    }
    }
}