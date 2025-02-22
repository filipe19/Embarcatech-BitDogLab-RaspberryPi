# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Inicializa o SDK do Raspberry Pi Pico
include(pico_sdk_import.cmake)

project(rgb_pwm C CXX ASM)

pico_sdk_init()

# Adicione o arquivo fonte do projeto e da biblioteca SSD1306.
add_executable(rgb_pwm 
    rgb_pwm.c
    inc/ssd1306_i2c.c
)

pico_set_program_name(rgb_pwm "rgb_pwm")
pico_set_program_version(rgb_pwm "0.1")

# Habilita saída USB
pico_enable_stdio_usb(rgb_pwm 1)

# Bibliotecas padrão
target_link_libraries(rgb_pwm pico_stdlib hardware_pwm hardware_i2c)

# Adiciona o diretório atual para include
target_include_directories(rgb_pwm PRIVATE ${CMAKE_CURRENT_LIST_DIR})

pico_add_extra_outputs(rgb_pwm)
