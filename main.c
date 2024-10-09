#include <stdio.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

void SysTick_Handler(void)
{
    HAL_IncTick();
}

int main(void)
{
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 1000);

    GPIO_InitTypeDef led_gpio_init = {
        .Alternate = 0,
        .Mode  = GPIO_MODE_OUTPUT_PP,
        .Pin   = GPIO_PIN_13,
        .Pull  = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_LOW,
    };

    __HAL_RCC_GPIOC_CLK_ENABLE();
    HAL_GPIO_Init(GPIOC, &led_gpio_init);

    while(true)
    {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        HAL_Delay(500);
    }
}