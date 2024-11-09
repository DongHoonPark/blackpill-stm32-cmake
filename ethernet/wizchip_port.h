#ifndef WIZCHIP_PORT_H
#define WIZCHIP_PORTH_H

typedef enum {
    __OK       = 0x00U,
    __ERROR    = 0x01U,
    __BUSY     = 0x02U,
    __TIMEOUT  = 0x03U
}eHalStatus;

typedef enum {
    __RESET = 0,
    __SET
}eGpioPinState;

typedef eHalStatus (*fHalSpiReceive)(volatile void*, uint8_t*, uint16_t, uint32_t);
typedef eHalStatus (*fHalSpiTransmit)(volatile void*, uint8_t*, uint16_t);
typedef void (*fHalGpioWritePin)(volatile void*, uint16_t, eGpioPinState);


void wizchip_register_stm32_hal(
    void* hspi,
    fHalSpiReceive   hal_spi_receive,
    fHalSpiTransmit  hal_spi_transmit,
    void* cs_gpiox,
    uint16_t cs_gpio_pin,
    fHalGpioWritePin hal_gpio_write_pin
);

#endif