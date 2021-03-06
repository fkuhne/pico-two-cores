# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "C:/Users/fkuhn/Documents/Pico/pico-sdk")

# Pull in Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(twoCores C CXX ASM)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

set(PICO_CXX_ENABLE_RTTI 1)

# Initialise the Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(twoCores twoCores.cpp)

pico_set_program_name(twoCores "twoCores")
pico_set_program_version(twoCores "0.1")

pico_enable_stdio_uart(twoCores 0)
pico_enable_stdio_usb(twoCores 1)

# Add the standard library to the build
target_link_libraries(twoCores
        pico_stdlib
        pico_unique_id
        hardware_pio
        hardware_adc
        pico_multicore
)

pico_add_extra_outputs(twoCores)
