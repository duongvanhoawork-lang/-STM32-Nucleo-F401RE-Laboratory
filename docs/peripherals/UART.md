# UART — Universal Asynchronous Receiver/Transmitter

> STM32F401RE · HAL Reference · [Back to README](../../README.md)

---

## Overview

The STM32F401RE has **3 USART** peripherals. On the **Nucleo-F401RE**, **USART2** is connected to the on-board ST-LINK USB bridge, providing a **Virtual COM Port** — no external USB-UART adapter needed.

| USART | TX Pin | RX Pin | Notes |
|-------|--------|--------|-------|
| **USART2** | PA2 | PA3 | Virtual COM Port via ST-LINK |
| USART1 | PA9 | PA10 | External, or via Arduino header |
| USART6 | PC6 | PC7 | External |

---

## CubeMX Configuration

| Parameter | Typical Value |
|-----------|---------------|
| Baud Rate | **115200** |
| Word Length | 8 bits |
| Stop Bits | 1 |
| Parity | None |
| Mode | TX + RX |
| Hardware Flow Control | None |

---

## HAL API

### Transmit

```c
/* Transmit a string (blocking) */
char msg[] = "Hello STM32\r\n";
HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

/* Transmit a single byte */
uint8_t b = 0x41; // 'A'
HAL_UART_Transmit(&huart2, &b, 1, HAL_MAX_DELAY);
```

### Receive

```c
/* Receive 1 byte (blocking, waits forever) */
uint8_t rx_byte;
HAL_UART_Receive(&huart2, &rx_byte, 1, HAL_MAX_DELAY);

/* Receive with timeout (100 ms) */
HAL_StatusTypeDef status = HAL_UART_Receive(&huart2, &rx_byte, 1, 100);
if (status == HAL_OK) {
    // Process rx_byte
} else if (status == HAL_TIMEOUT) {
    // No data received within 100 ms
}
```

### Interrupt-Driven Receive

```c
/* In main — start listening for 1 byte */
uint8_t rx_buf[1];
HAL_UART_Receive_IT(&huart2, rx_buf, 1);

/* Callback fires when 1 byte is received */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART2) {
        // Process rx_buf[0] here
        // Re-arm for next byte:
        HAL_UART_Receive_IT(&huart2, rx_buf, 1);
    }
}
```

---

## Enable `printf` / `sprintf`

### Method 1 — Retarget `__io_putchar` (GCC / STM32CubeIDE)

Add to `main.c`:

```c
#include <stdio.h>

/* Redirect stdout to UART2 */
int __io_putchar(int ch) {
    HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return ch;
}
```

Then `printf("ADC = %lu\r\n", raw_value);` works.

### Method 2 — `sprintf` + `HAL_UART_Transmit`

```c
char buf[64];
sprintf(buf, "ADC raw: %lu  Voltage: %.2f V\r\n", raw, voltage);
HAL_UART_Transmit(&huart2, (uint8_t*)buf, strlen(buf), HAL_MAX_DELAY);
```

---

## Servo Motor Control via UART (Lab Reference)

```c
/* UART command protocol used in Chapter 9 lab:
   '0' → 0°   → CCR 500
   '9' → 180° → CCR 2500                          */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART2) {
        uint8_t cmd = rx_buf[0];
        if (cmd >= '0' && cmd <= '9') {
            uint8_t angle = (cmd - '0') * 20;         // 0, 20, 40…180
            uint32_t ccr  = 500 + (angle * 2000 / 180);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, ccr);

            char resp[32];
            sprintf(resp, "Angle: %d deg\r\n", angle);
            HAL_UART_Transmit(&huart2, (uint8_t*)resp, strlen(resp), HAL_MAX_DELAY);
        }
        HAL_UART_Receive_IT(&huart2, rx_buf, 1);      // Re-arm
    }
}
```

> 📌 Pattern from [UART-Based_Servo_Motor_Control_on_Wokwi](https://github.com/duongvanhoawork-lang/-STM32-Nucleo-F401RE-Laboratory/tree/main/UART-Based_Servo_Motor_Control_on_Wokwi)

---

## PC Serial Terminal Settings

Use **PuTTY**, **TeraTerm**, or **VS Code Serial Monitor**:

| Setting | Value |
|---------|-------|
| Port | COMx (check Device Manager) |
| Baud Rate | 115200 |
| Data bits | 8 |
| Stop bits | 1 |
| Parity | None |
| Flow Control | None |

---

## References

- RM0368 §19 — Universal synchronous asynchronous receiver transmitter (USART)
- HAL: `stm32f4xx_hal_uart.h`
- Lab: [UART-Based_Servo_Motor_Control_on_Wokwi](https://github.com/duongvanhoawork-lang/-STM32-Nucleo-F401RE-Laboratory/tree/main/UART-Based_Servo_Motor_Control_on_Wokwi)
