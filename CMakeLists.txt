cmake_minimum_required(VERSION 3.20)

project(
    "Reyna's Blooming Entertainment System (RBES)"
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

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
    include/components/address_bus.h
    src/components/address_bus.cpp
    src/components/cpu/addressing_modes.cpp
    src/components/cpu/alu.cpp
    src/components/cpu/instructions/arithmetic.cpp
    src/components/cpu/instructions/bitwise.cpp
    src/components/cpu/instructions/jump.cpp
    src/components/cpu/instructions/flag.cpp
    src/components/cpu/instructions/compare.cpp
    src/components/cpu/instructions/shift.cpp
)

target_include_directories(rbes
PRIVATE
    include
)

target_link_directories(rbes
PRIVATE
    lib
)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(rbes
PRIVATE
    glfw3
    OpenGL::GL
)