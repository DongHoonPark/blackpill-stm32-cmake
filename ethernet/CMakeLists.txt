
message("${WIZ_CHIP} ioLibrary Configuration")

set(DRIVER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary)

string(TOLOWER "${WIZ_CHIP}" WIZ_CHIP_LOWER)

set(DRIVER_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/wizchip_port.c
    ${DRIVER_DIR}/Ethernet/${WIZ_CHIP}/${WIZ_CHIP_LOWER}.c
    ${DRIVER_DIR}/Ethernet/socket.c
    ${DRIVER_DIR}/Ethernet/wizchip_conf.c
    ${DRIVER_DIR}/Application/loopback/loopback.c
)

set(DRIVER_INC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${DRIVER_DIR}/Ethernet
    ${DRIVER_DIR}/Application/loopback
)

message(${DRIVER_DIR}/${WIZ_CHIP}/${WIZ_CHIP_LOWER}.c)

add_library(wizchip ${DRIVER_SRC})
target_include_directories(wizchip PUBLIC ${DRIVER_INC})
target_compile_options(wizchip PRIVATE ${WIZ_COMPILE_OPTIONS})