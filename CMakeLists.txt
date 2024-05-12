cmake_minimum_required(VERSION 3.20)
project(run)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#CMake specific
enable_language(ASM)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    add_compile_options(-fdiagnostics-color=always)
endif()

#Includes
include(cmake/constants.cmake)

# Project specific
set (LINKER_SCRIPT            "../STM32F446RETX_FLASH.ld")
set (MCPU                     ${MCPU_CORTEX_M4})
set (MFPU                     ${MFPU_FPV4_SP_D16})
set (MFLOAT_ABI               "")
set (RUNTIME_LIBRARY          ${RUNTIME_LIBRARY_REDUCED_C})
set (RUNTIME_LIBRARY_SYSCALLS ${RUNTIME_LIBRARY_SYSCALLS_MINIMAL})

set (CMAKE_EXECUTABLE_SUFFIX ".elf")
set (CMAKE_STATIC_LIBRARY_SUFFIX ".a")
set (CMAKE_C_FLAGS "${MCPU} -std=gnu11 ${MFPU} ${MFLOAT_ABI} ${RUNTIME_LIBRARY} -mthumb -Wall -Werror")
set (CMAKE_EXE_LINKER_FLAGS "-T${LINKER_SCRIPT} ${RUNTIME_LIBRARY_SYSCALLS} -Wl,-Map=test.map -Wl,--gc-sections -static -Wl,--start-group -lc -lm -Wl,--end-group")
set (CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp")
# Project
add_compile_definitions(STM32F446xx=1)
add_subdirectory(Drivers)

set(PROJECT_SOURCES
    Core/Startup/startup_stm32f446retx.s
    Core/Src/bme280.c
    Core/Src/main.c  
    Core/Src/stm32f4xx_hal_msp.c  
    Core/Src/stm32f4xx_it.c  
    Core/Src/syscalls.c  
    Core/Src/sysmem.c  
    Core/Src/system_stm32f4xx.c
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE Core/Inc)
target_link_libraries(${PROJECT_NAME} PRIVATE STM32_Drivers)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}>)

# Flash
find_program(STM32_PROGRAMMER_CLI STM32_Programmer_CLI)
if(STM32_PROGRAMMER_CLI)
    message(STATUS "STM32_Programmer_CLI was found, 'program' target can be used")
    add_custom_target(program DEPENDS ${PROJECT_NAME} COMMAND ${STM32_PROGRAMMER_CLI} --connect port=SWD --write $<TARGET_FILE:${PROJECT_NAME}> --verify -rst)
else()
    message(STATUS "STM32_Programmer_CLI was not found, program target is inaccessible")
endif()

add_custom_target(cppcheck-check COMMAND ${CPPCHECK} 
        --check-level=exhaustive
        --checkers-report=${CMAKE_BINARY_DIR}/cppcheck-checks-report.log
        --cppcheck-build-dir=${CPPCHECK_BUILD_DIR}
        --enable=all
        --error-exitcode=1
        --inconclusive
        --language=c
        --platform=native
        --project=${CMAKE_BINARY_DIR}/compile_commands.json
        --suppress=checkersReport
        --suppress=*:*/Core/*
        --suppress=*:*/Drivers/*
        --suppress=unusedFunction
        -D__GNUC__
        -i ${CMAKE_BINARY_DIR}
        -j ${N_PROC}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        USES_TERMINAL
        COMMENT "Checking code with Cppcheck"
    )

# #############################################################################################################################
# # file:  CMakeLists.txt
# # brief: Template "CMakeLists.txt" for building of executables and static libraries.
# #
# # usage: Edit "VARIABLES"-section to suit project requirements.
# #        For debug build:
# #          cmake -DCMAKE_TOOLCHAIN_FILE=cubeide-gcc.cmake  -S ./ -B Debug -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
# #          ninja -C Debug VERBOSE=1
# #        For release build:
# #          cmake -DCMAKE_TOOLCHAIN_FILE=cubeide-gcc.cmake  -S ./ -B Release -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
# #          ninja -C Release VERBOSE=1
# #############################################################################################################################