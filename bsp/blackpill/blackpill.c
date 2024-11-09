#include "blackpill/blackpill.h"
#include "blackpill.h"

#include "stm32f4xx_hal.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);

SPI_HandleTypeDef hspi1;

void BSP_Init(void)
{
  // Initialize the HAL Library
  HAL_Init();

  // Configure the system clock
  SystemClock_Config();

  // Initialize all configured peripherals (GPIO and SPI1)
  MX_GPIO_Init();
  MX_SPI1_Init();
}

void SystemClock_Config(void)
{
  // System Clock Configuration Code
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  // Configure the main internal regulator output voltage
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  // Initialize the CPU, AHB, and APB buses clocks
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // Enable GPIOC clock
  __HAL_RCC_GPIOC_CLK_ENABLE();

  // Configure GPIOC Pin 13 for LED output (Output Push Pull mode)
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  // Enable GPIOB clock
  __HAL_RCC_GPIOB_CLK_ENABLE();

  // Configure GPIOB Pin 7 as input for interrupt (Input mode)
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  // Configure GPIOB Pin 6 as output with Open Drain mode
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

static void MX_SPI1_Init(void)
{
  __HAL_RCC_SPI1_CLK_ENABLE();
  // SPI1 initialization settings
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;  // Set SPI1 as master
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;  // Set bidirectional data mode
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;  // Set data frame size to 8 bits
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;  // Clock polarity low when idle
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;  // First clock transition is the first data capture edge
  hspi1.Init.NSS = SPI_NSS_SOFT;  // Hardware chip select management
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;  // Set baud rate prescaler to 16
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;  // Data is transmitted MSB first
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;  // Disable TI mode
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;  // Disable CRC calculation
  hspi1.Init.CRCPolynomial = 10;  // CRC polynomial value
  
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    // Initialization error handling
    Error_Handler();
  }

  // SPI1 Pin configuration: SCLK (PB3), MISO (PB4), MOSI (PB5)
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // Enable GPIOB clock
  __HAL_RCC_GPIOB_CLK_ENABLE();

  // Configure SPI1 SCLK, MISO, MOSI pins as Alternate Function Push Pull
  GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  // Enable GPIOA clock
  __HAL_RCC_GPIOA_CLK_ENABLE();

  // Configure NSS pin (PA4) as Alternate Function Push Pull
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  
}

void Error_Handler(void)
{
  // If an error occurs, stay in infinite loop
  while(1) {}
}
