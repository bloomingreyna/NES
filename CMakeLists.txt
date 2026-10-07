cmake_minimum_required(VERSION 3.20)

project(
    "Reyna's Blooming Entertainment System (RBES)"
    VERSION 1.0
    LANGUAGES CXX
)
include(CTest)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(rbes)

target_sources(rbes
PRIVATE
    src/main.cpp
    include/glfw3/glfw3.h
    include/glfw3/glfw3native.h
    include/components/cpu.h
    src/components/cpu/main.cpp
    include/ns.h
    src/ns/bit_manip.cpp
    src/ns/alu_functions/arithmetic.cpp
    src/ns/alu_functions/bitwise.cpp
    src/ns/alu_functions/shift.cpp
    src/ns/alu_functions/compare.cpp
    src/ns/instructions/flag_instructions.cpp
    src/ns/instructions/access_instructions.cpp
    src/ns/instructions/transfer_instructions.cpp
    src/ns/instructions/branch_instructions.cpp
    src/ns/instructions/stack_instructions.cpp
    src/ns/instructions/jump_instructions.cpp
    include/components/address_bus.h
    src/components/address_bus.cpp
    src/components/cpu/addressing_modes.cpp
    src/components/cpu/alu.cpp
    src/components/cpu/instructions.cpp
)

target_include_directories(rbes
PRIVATE
    include
)

target_link_directories(rbes
PRIVATE
    lib
)

target_link_libraries(rbes
PRIVATE
    glfw3
    OpenGL::GL
)

enable_testing()
add_library(test_config INTERFACE)

target_sources(test_config INTERFACE
    include/ns.h
    include/components/cpu.h
)
target_include_directories(test_config INTERFACE
    include
)
target_link_directories(test_config INTERFACE
    lib
)
target_link_libraries(test_config INTERFACE
    glfw3
    OpenGL::GL
)

add_executable(add_with_carry
    tests/add_with_carry.cpp
    src/ns/alu_functions/arithmetic.cpp
    src/ns/bit_manip.cpp
)
target_link_libraries(add_with_carry PRIVATE test_config)

add_test(NAME TestADC COMMAND add_with_carry)