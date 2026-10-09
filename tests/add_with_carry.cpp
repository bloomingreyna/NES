#include <bitset>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <vector>

#include <components/cpu.h>
#include <ns.h>

int main() {
    // Operand 1, Operand 2, Carry-in, Expected result, Expected status
    const std::vector<std::tuple<uint8_t, uint8_t, bool, uint8_t, uint8_t>> test_cases{
        // Happy paths (no flag setting)
        {0x24, 0x56, false, 0x7A, 0x00},
        {0x53, 0x1A, false, 0x6D, 0x00},
        {0x72, 0x03, true,  0x76, 0x00},

        // Zero
        {0x00, 0x00, false, 0x00, 0x02},
        {0x00, 0x00, true,  0x01, 0x00},
        {0x00, 0x01, false, 0x01, 0x00},
        
        // Carry
        {0xFF, 0x00, false, 0xFF, 0x80},
        {0xFE, 0x03, false, 0x01, 0x01},
        {0xFF, 0x00, true,  0x00, 0x03},

        // Signed overflow
        {0x7F, 0x03, false, 0x82, 0xC0},
        {0x80, 0x82, true,  0x03, 0x41},
        {0x7F, 0x00, true,  0x80, 0xC0},
        {0x80, 0xFF, false, 0x7F, 0x41}
    };
    
    for (size_t test{}; test < test_cases.size(); ++test) {
        auto current_test{test_cases[test]};

        uint8_t accumulator{std::get<0>(current_test)};
        uint8_t memory{std::get<1>(current_test)};
        bool carry{std::get<2>(current_test)};
        uint8_t expected_result{std::get<3>(current_test)};
        uint8_t expected_status{std::get<4>(current_test)};

        ALU result{alu_functions::arithmetic::AddWithCarry(
            accumulator, memory, carry
        )};

        if (result.result != expected_result || result.status != expected_status) {
            std::cout << "Failed test case: " << test + 1 << "\n";
            std::cout << static_cast<int>(expected_result) << " " << static_cast<int>(result.result) << "\n";
            std::cout << static_cast<int>(expected_status) << " " << static_cast<int>(result.status);
            return -1;
        }
    }

    return 0;
}