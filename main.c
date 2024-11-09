#include "blackpill/blackpill.h"
#include "wizchip.h"
#include "loopback.h"

#include <stdio.h>
#include <stdbool.h>

extern SPI_HandleTypeDef hspi1;

void SysTick_Handler(void)
{
    HAL_IncTick();
}

wiz_NetInfo net_info = {
     .mac  = { 0xEA, 0x11, 0x22, 0x33, 0x44, 0xEA },
     .ip = {192, 168, 137, 100},
     .sn = {255, 255, 255, 0},
     .gw = {192, 168, 137, 1},
     .dns = {0, 0, 0, 0},
}; // Network information.

uint8_t transaction_buf_sizes[] = {
    2, 2, 2, 2, 2, 2, 2, 2
}; // All 2kB buffer setting for each sockets

uint8_t buffer[8192] = {0,};

int main(void)
{
    BSP_Init();
    wizchip_register_stm32_hal(
        &hspi1,
        HAL_SPI_Receive,
        HAL_SPI_Transmit,
        GPIOA,
        GPIO_PIN_15,
        HAL_GPIO_WritePin
    );

    wizchip_init(transaction_buf_sizes, transaction_buf_sizes);
    setSHAR(net_info.mac);
    setSIPR(net_info.ip);
    setSUBR(net_info.sn);
    setGAR (net_info.gw);

    while(true)
    {
        loopback_tcps(0, buffer, 5000);
    }
}