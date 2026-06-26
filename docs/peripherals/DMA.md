# DMA — Direct Memory Access

> STM32F401RE · HAL Reference · [Back to README](../../README.md)

---

## Overview

DMA transfers data between memory and peripherals **without CPU intervention**, freeing the CPU for other tasks.

STM32F401RE has **2 DMA controllers** (DMA1, DMA2), each with **8 streams** and **8 channels per stream**.

---

## When to Use DMA

| Scenario | Use DMA? |
|----------|----------|
| Single ADC read | ❌ Polling is simpler |
| Continuous ADC sampling | ✅ Yes |
| Short UART message | ❌ Blocking TX is fine |
| Large UART data stream | ✅ Yes |
| SPI display updates | ✅ Yes |
| Memory copy (memcpy) | ✅ For large buffers |

---

## HAL API

### ADC + DMA (Most Common Lab Use)

```c
uint32_t adc_buf[2];  // 2 channels

/* Start ADC with DMA in circular mode */
HAL_ADC_Start_DMA(&hadc1, adc_buf, 2);

/* Half-complete callback (optional) */
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc) {
    // First half of buffer is ready
}

/* Full-complete callback */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    if (hadc->Instance == ADC1) {
        // adc_buf[0] = channel 0, adc_buf[1] = channel 1
    }
}
```

### UART TX + DMA (Non-Blocking)

```c
char msg[] = "Hello via DMA!\r\n";

/* Non-blocking transmit */
HAL_UART_Transmit_DMA(&huart2, (uint8_t*)msg, strlen(msg));

/* Completion callback */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART2) {
        // Transmission complete
    }
}
```

---

## CubeMX DMA Setup

1. Select the peripheral (ADC1, USART2, etc.)
2. Go to **DMA Settings** tab
3. Click **Add** → select the correct DMA stream
4. Set **Direction**: Peripheral to Memory / Memory to Peripheral
5. Set **Mode**: Normal (one-shot) or Circular (continuous)
6. Enable DMA interrupt in **NVIC Settings**

---

## References

- RM0368 §9 — DMA controller
- HAL: `stm32f4xx_hal_dma.h`

> 📝 *Detailed notes will be added when DMA labs are completed.*
