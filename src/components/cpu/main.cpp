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
    addressing_modes.at(INDIRECT) = [this]() { QueueIndirectAddrMode(); };
    addressing_modes.at(INDIRECT_X) = [this]() { QueueIndirectXAddrMode(); };
    addressing_modes.at(INDIRECT_Y) = [this]() { QueueIndirectYAddrMode(); };

    opcode_arr.at(ADC_IMM) = {IMMEDIATE, [this]() { ADC(); }};
    opcode_arr.at(ADC_ZP) = {ZERO_PAGE, [this]() { ADC(); }};
    opcode_arr.at(ADC_ZP_X) = {ZERO_PAGE_X, [this]() { ADC(); }};
    opcode_arr.at(ADC_ABS) = {ABSOLUTE, [this]() { ADC(); }};
    opcode_arr.at(ADC_ABS_X) = {ABSOLUTE_X, [this]() { ADC(); }};
    opcode_arr.at(ADC_ABS_Y) = {ABSOLUTE_Y, [this]() { ADC(); }};
    opcode_arr.at(ADC_IND_X) = {INDIRECT_X, [this]() { ADC(); }};
    opcode_arr.at(ADC_IND_Y) = {INDIRECT_Y, [this]() { ADC(); }};
}

void CPU::FetchInstruction() {
    opcode = static_cast<Opcode>(bus.ReadMemory(program_counter));
    
    addressing_modes.at(opcode_arr.at(opcode).first)();
    opcode_arr.at(opcode).second();
}

void CPU::ExecuteInstruction() {
    if (!task_queue.empty()) {
        task_queue.front()();
    } else {
        FetchInstruction();
    }
}