cmake_minimum_required(VERSION 3.16)

set(PROJ_NAME stm32-blackpill)
set(STM32_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/stm32-cmake)

set(CMAKE_TOOLCHAIN_FILE ${STM32_CMAKE_PATH}/cmake/stm32_gcc.cmake)
project(${PROJ_NAME} CXX C ASM)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

set(TARGET_NAME ${PROJ_NAME})

add_executable(${TARGET_NAME} main.c bsp/blackpill/blackpill.c)

target_include_directories(
    ${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/bsp
)

stm32_fetch_cmsis(F4)
stm32_fetch_hal(F4)

find_package(CMSIS COMPONENTS STM32F401CC REQUIRED)
find_package(HAL COMPONENTS STM32F4 REQUIRED)

set(WIZ_CHIP W5500)
set(WIZ_COMPILE_OPTIONS 
    -mcpu=cortex-m4 
    -mfpu=fpv4-sp-d16 
    -mfloat-abi=hard
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ethernet)

target_link_libraries(
    ${TARGET_NAME} 
    STM32::NoSys 
    CMSIS::STM32::F401CC
    HAL::STM32::F4::CORTEX
    HAL::STM32::F4::RCC
    HAL::STM32::F4::PWR
    HAL::STM32::F4::GPIO
    HAL::STM32::F4::ADC
    HAL::STM32::F4::TIM
    HAL::STM32::F4::USART
    HAL::STM32::F4::SPI
    wizchip
)


add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${TARGET_NAME}>
)
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${TARGET_NAME}> ${TARGET_NAME}.hex
)
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${TARGET_NAME}> ${TARGET_NAME}.bin
)