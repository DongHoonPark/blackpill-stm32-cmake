#include "blackpill/blackpill.h"

#include <stdio.h>
#include <stdbool.h>

void SysTick_Handler(void)
{
    HAL_IncTick();
}

int main(void)
{
    SystemClock_Config();
    
    GPIO_InitTypeDef led_gpio_init = {
        .Pin   = GPIO_PIN_13,
        .Mode  = GPIO_MODE_OUTPUT_PP,
        .Pull  = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_LOW,
        .Alternate = GPIO_MODE_AF_PP,
    };

    __HAL_RCC_GPIOC_CLK_ENABLE();
    HAL_GPIO_Init(GPIOC, &led_gpio_init);

    while(true)
    {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        HAL_Delay(500);
    }
}