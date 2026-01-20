cmake_minimum_required(VERSION 4.1)

set(CMAKE_C_STANDARD 23)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(VisualFirmware)

add_executable(${PROJECT_NAME}
    include/visual_firmware/gpio.h
    src/main.c
    src/tasks/task_1.c
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        include
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -mcpu=cortex-m33
        -Wall
        -Werror
)

target_link_options(${PROJECT_NAME}
    PRIVATE
        -nostdlib
        -T${CMAKE_CURRENT_SOURCE_DIR}/src/linker.ld
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    SUFFIX ".elf"
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/picotool.exe uf2 convert $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.uf2
)
