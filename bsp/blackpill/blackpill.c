#include "blackpill/blackpill.h"

void Error_Handler(void)
{
    // User-defined error handling routine
    while (1)
    {
    }
}

void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};

    // HSE (High-Speed External) 오실레이터 구성
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;           // HSE ON
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;        // PLL ON
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE; // PLL 입력으로 HSE 선택
    RCC_OscInitStruct.PLL.PLLM = 25;                    // 입력 클럭 25MHz를 1MHz로 줄임
    RCC_OscInitStruct.PLL.PLLN = 336;                   // 1MHz x 336 = 336MHz (VCO 출력)
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;         // 336MHz / 4 = 84MHz (SYSCLK)
    RCC_OscInitStruct.PLL.PLLQ = 7;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        // 오류 처리
        Error_Handler();
    }
        // 2. Configure clocks (SYSCLK, AHB, APB bus clocks)
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    // 클록 타입 설정: SYSCLK, HCLK, PCLK1, PCLK2
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;  // SYSCLK 소스로 PLL 선택
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;         // AHB 클록 분배기: 1로 나눔 (84MHz)
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;          // APB1 클록 분배기: 2로 나눔 (42MHz)
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;          // APB2 클록 분배기: 1로 나눔 (84MHz)

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        // 오류 처리
        Error_Handler();
    }
}
