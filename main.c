#include "blackpill/blackpill.h"

#include <stdio.h>
#include <stdbool.h>

void SysTick_Handler(void)
{
    HAL_IncTick();
}

int main(void)
{
    BSP_Init();

    while(true)
    {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        HAL_Delay(500);
    }
}