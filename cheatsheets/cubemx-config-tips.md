# STM32CubeMX Configuration Tips

> [Back to README](../README.md)

---

## General Workflow

```
1. Open .ioc file in STM32CubeIDE
2. Configure peripherals in the Pinout & Configuration view
3. Set Clock Configuration (84 MHz for Nucleo-F401RE)
4. Configure Project settings
5. Generate Code (Alt+K or Project → Generate Code)
6. Write user code in "USER CODE BEGIN / END" sections
```

> ⚠️ Always write your code inside `/* USER CODE BEGIN */` and `/* USER CODE END */` blocks. CubeMX overwrites everything outside these sections when regenerating.

---

## Clock Configuration for 84 MHz

| Setting | Value |
|---------|-------|
| Input Frequency | 8 MHz (HSE from ST-LINK) |
| PLL Source | HSE |
| PLLM | 8 |
| PLLN | 336 |
| PLLP | 4 |
| PLLQ | 7 |
| AHB Prescaler | 1 |
| APB1 Prescaler | 2 |
| APB2 Prescaler | 1 |
| **SYSCLK** | **84 MHz** |

---

## Timer Period Configuration

For a given desired interrupt period `T`:

$$PSC = \left\lfloor \frac{f_{TIM}}{f_{target} \times (ARR+1)} \right\rfloor - 1$$

**Quick table (84 MHz timer clock):**

| Desired Period | PSC | ARR |
|----------------|-----|-----|
| 1 ms | 83 | 999 |
| 10 ms | 839 | 999 |
| 100 ms | 8399 | 999 |
| 500 ms | 41999 | 999 |
| 1 s | 8399 | 9999 |

---

## PWM Configuration for Servo (50 Hz)

| Parameter | Value |
|-----------|-------|
| Timer | TIM3 (or TIM2) |
| PSC | 83 |
| ARR | 19999 |
| Pulse (CCR) | 1500 (90°) |
| **f_PWM** | **50 Hz** |
| **Period** | **20 ms** |

---

## UART Configuration

| Parameter | Value |
|-----------|-------|
| Mode | Asynchronous |
| Baud Rate | 115200 |
| Word Length | 8 bits |
| Parity | None |
| Stop Bits | 1 |
| USART | USART2 (Nucleo virtual COM) |

---

## ADC Configuration

| Parameter | Value |
|-----------|-------|
| Resolution | 12 bits |
| Data Alignment | Right |
| Scan Mode | Disabled (single channel) |
| Continuous Mode | Disabled |
| Sampling Time | 84 Cycles |

---

## NVIC Priority Rules

- **Lower number = higher priority**
- Range: 0 (highest) to 15 (lowest)
- Never set a peripheral interrupt to priority 0 — reserve for critical safety ISRs
- UART RX: priority 5 | Timer callbacks: priority 6 | GPIO EXTI: priority 7 (example)
- Ensure DMA priority ≥ peripheral that feeds it

---

## Regenerating Code Safely

1. Keep all user code inside `USER CODE BEGIN/END` blocks
2. Before regenerating, check `stm32f4xx_it.c` — verify IRQ handlers are present
3. After regeneration, check `main.c` — verify `HAL_Init()`, `SystemClock_Config()`, and peripheral init calls are correct
