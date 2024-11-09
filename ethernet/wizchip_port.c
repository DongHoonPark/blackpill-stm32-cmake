#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "wizchip_port.h"
#include "wizchip_conf.h"


static void hal_spi_readburst(uint8_t* pBuf, uint16_t len);
static void hal_spi_writeburst(uint8_t* pBuf, uint16_t len);

static uint8_t  hal_spi_readbyte(void);
static void 	hal_spi_writebyte(uint8_t wb);
static void     hal_spi_cs_sel(void);
static void     hal_spi_cs_desel(void);

static volatile void* hspi;

static fHalSpiReceive   hal_spi_receive;
static fHalSpiTransmit  hal_spi_transmit;

static volatile void* cs_gpiox;
static uint16_t       cs_gpio_pin;

static fHalGpioWritePin hal_gpio_write_pin;

// static uint8_t hal_spi_receive_dma;
// static uint8_t hal_spi_transmit_dma;
 
void wizchip_register_stm32_hal(
    void*            _hspi,
    fHalSpiReceive   _hal_spi_receive,
    fHalSpiTransmit  _hal_spi_transmit,
    void*            _cs_gpiox,
    uint16_t         _cs_gpio_pin,
    fHalGpioWritePin _hal_gpio_write_pin
)
{
    hspi = _hspi;
    hal_spi_receive      = _hal_spi_receive;
    hal_spi_transmit     = _hal_spi_transmit;
    // hal_spi_receive_dma  = _hal_spi_receive_dma;
    // hal_spi_transmit_dma = _hal_spi_transmit_dma;

    if( _cs_gpio_pin == NULL || _hal_gpio_write_pin == NULL)
    {
        // Assume hardware NSS select
        reg_wizchip_cs_cbfunc(NULL, NULL);
    }
    else
    {
        hal_gpio_write_pin = _hal_gpio_write_pin;
        cs_gpiox    = _cs_gpiox;
        cs_gpio_pin = _cs_gpio_pin;

        reg_wizchip_cs_cbfunc(hal_spi_cs_sel, hal_spi_cs_desel);
    }
    
    reg_wizchip_cris_cbfunc(NULL, NULL);
    reg_wizchip_spi_cbfunc(hal_spi_readbyte, hal_spi_writebyte);
    reg_wizchip_spiburst_cbfunc(hal_spi_readburst, hal_spi_writeburst);

    uint8_t version = getVERSIONR();
    return;
}

static uint8_t hal_spi_readbyte(void)
{
    uint8_t buf;
    hal_spi_receive(hspi, &buf, 1, 1);
    return buf;
}

static void hal_spi_writebyte(uint8_t wb)
{
    hal_spi_transmit(hspi, &wb, 1);
}

void hal_spi_cs_sel(void)
{
    hal_gpio_write_pin(cs_gpiox, cs_gpio_pin, __RESET);
}

void hal_spi_cs_desel(void)
{
    hal_gpio_write_pin(cs_gpiox, cs_gpio_pin, __SET);
}

static void hal_spi_readburst(uint8_t *pBuf, uint16_t len)
{
    hal_spi_receive(hspi, pBuf, len, 1);
}

static void hal_spi_writeburst(uint8_t *pBuf, uint16_t len)
{
    hal_spi_transmit(hspi, pBuf, len);
}
