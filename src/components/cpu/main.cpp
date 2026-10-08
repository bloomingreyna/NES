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

    opcode_arr.at(ADC_IMM) = {IMMEDIATE, [this]() { AddWithCarry(); }};
    opcode_arr.at(ADC_ZP) = {ZERO_PAGE, [this]() { AddWithCarry(); }};
    opcode_arr.at(ADC_ZP_X) = {ZERO_PAGE_X, [this]() { AddWithCarry(); }};
    opcode_arr.at(ADC_ABS) = {ABSOLUTE, [this]() { AddWithCarry(); }};
    opcode_arr.at(ADC_ABS_X) = {ABSOLUTE_X, [this]() { AddWithCarry(); }};
    opcode_arr.at(ADC_ABS_Y) = {ABSOLUTE_Y, [this]() { AddWithCarry(); }};
    opcode_arr.at(ADC_IND_X) = {INDIRECT_X, [this]() { AddWithCarry(); }};
    opcode_arr.at(ADC_IND_Y) = {INDIRECT_Y, [this]() { AddWithCarry(); }};
}

void CPU::FetchInstruction() {
    opcode = static_cast<Opcode>(bus.ReadMemory(program_counter));
    program_counter++;
}

void CPU::ExecuteInstruction() {
    if (!instruction_complete) {
        AddressingMode mode{opcode_arr[opcode].first};
        std::function<void()> instruction{opcode_arr[opcode].second};

        if (!address_mode_complete) {
            addressing_modes[opcode_arr[opcode].first]();
            if (mode == IMMEDIATE) {
                current_internal_op++;
                instruction();
            }
        } else if (address_mode_complete) {
            instruction();
        }

        current_internal_op++;
    } else {
        FetchInstruction();
        current_internal_op = 0;
        address_mode_complete = false;
        instruction_complete = false;
    }
}

void CPU::CompleteAddressMode() {
    current_internal_op = 0;
    address_mode_complete = true;
}

void CPU::CompleteInstruction() {
    instruction_complete = true;
}