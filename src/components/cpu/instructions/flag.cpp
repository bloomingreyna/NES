#include <components/cpu.h>
#include <ns.h>

void CPU::ClearFlag(StatusFlag flag) {
    bit_manip::SetBit(status_register, flag, false);
    if (flag == INTERRUPT_DISABLE) {
        isd = ISD_TRUE;
    }

    CompleteInstruction();
}

void CPU::SetFlag(StatusFlag flag) {
    bit_manip::SetBit(status_register, flag, true);
    if (flag == INTERRUPT_DISABLE) {
        isd = ISD_FALSE;
    }

    CompleteInstruction();
}