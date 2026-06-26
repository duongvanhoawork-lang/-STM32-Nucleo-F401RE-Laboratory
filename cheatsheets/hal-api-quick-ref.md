# HAL API Quick Reference

> One-liner cheat sheet for STM32 HAL driver. [Back to README](../README.md)

---

## GPIO

```c
HAL_GPIO_WritePin(GPIOx, GPIO_PIN_x, GPIO_PIN_SET);     // HIGH
HAL_GPIO_WritePin(GPIOx, GPIO_PIN_x, GPIO_PIN_RESET);   // LOW
HAL_GPIO_TogglePin(GPIOx, GPIO_PIN_x);                  // Toggle
GPIO_PinState s = HAL_GPIO_ReadPin(GPIOx, GPIO_PIN_x);  // Read
```

## Delay

```c
HAL_Delay(ms);                  // Blocking millisecond delay
uint32_t t = HAL_GetTick();    // Returns ms since boot
```

## Timer

```c
HAL_TIM_Base_Start_IT(&htimX);                          // Start TIM interrupt
HAL_TIM_Base_Stop_IT(&htimX);                           // Stop TIM interrupt
__HAL_TIM_SET_COUNTER(&htimX, 0);                       // Reset counter
uint32_t cnt = __HAL_TIM_GET_COUNTER(&htimX);           // Read counter
uint32_t arr = __HAL_TIM_GET_AUTORELOAD(&htimX);        // Read ARR
```

## PWM

```c
HAL_TIM_PWM_Start(&htimX, TIM_CHANNEL_N);               // Start PWM
HAL_TIM_PWM_Stop(&htimX, TIM_CHANNEL_N);                // Stop PWM
__HAL_TIM_SET_COMPARE(&htimX, TIM_CHANNEL_N, duty);     // Set duty (0–ARR)
```

## ADC

```c
HAL_ADC_Start(&hadcX);
HAL_ADC_PollForConversion(&hadcX, HAL_MAX_DELAY);
uint32_t raw = HAL_ADC_GetValue(&hadcX);                // 0–4095
HAL_ADC_Stop(&hadcX);
HAL_ADC_Start_DMA(&hadcX, buf, len);                    // DMA mode
```

## UART

```c
HAL_UART_Transmit(&huartX, data, len, timeout);         // TX blocking
HAL_UART_Receive(&huartX, buf, len, timeout);           // RX blocking
HAL_UART_Transmit_IT(&huartX, data, len);               // TX interrupt
HAL_UART_Receive_IT(&huartX, buf, len);                 // RX interrupt
HAL_UART_Transmit_DMA(&huartX, data, len);              // TX DMA
HAL_UART_Receive_DMA(&huartX, buf, len);                // RX DMA
```

## SPI

```c
HAL_SPI_Transmit(&hspiX, data, len, timeout);
HAL_SPI_Receive(&hspiX, buf, len, timeout);
HAL_SPI_TransmitReceive(&hspiX, tx, rx, len, timeout);
```

## I2C

```c
HAL_I2C_Master_Transmit(&hi2cX, addr<<1, data, len, timeout);
HAL_I2C_Master_Receive(&hi2cX, addr<<1, buf, len, timeout);
HAL_I2C_Mem_Write(&hi2cX, addr<<1, reg, I2C_MEMADD_SIZE_8BIT, data, len, timeout);
HAL_I2C_Mem_Read(&hi2cX, addr<<1, reg, I2C_MEMADD_SIZE_8BIT, buf, len, timeout);
HAL_I2C_IsDeviceReady(&hi2cX, addr<<1, retries, timeout);
```

## Power

```c
HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
HAL_PWR_EnterSTANDBYMode();
```

## Common Status Codes

| Code | Meaning |
|------|---------|
| `HAL_OK` | Success |
| `HAL_ERROR` | Generic error |
| `HAL_BUSY` | Peripheral busy |
| `HAL_TIMEOUT` | Operation timed out |

## Useful Macros

```c
__HAL_RCC_GPIOA_CLK_ENABLE();          // Enable GPIO clock
__HAL_TIM_ENABLE_IT(&htimX, TIM_IT_UPDATE); // Enable timer interrupt
__HAL_UART_ENABLE_IT(&huartX, UART_IT_RXNE); // Enable UART RX interrupt
__disable_irq(); /* critical section */ __enable_irq();
```
