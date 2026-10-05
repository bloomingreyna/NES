#include <array>

#include <components/cpu.h>
#include <ns.h>

void CPU::FetchInstruction() {

}

void CPU::ExecuteInstruction() {
    if (!task_queue.empty()) {
        task_queue.front()();
    } else {
        FetchInstruction();
    }
}

void CPU::QueryALU(uint8_t opcode) {
    uint8_t mask{0xFF};
}