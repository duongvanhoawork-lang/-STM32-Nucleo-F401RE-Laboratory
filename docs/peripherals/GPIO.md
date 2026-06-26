# GPIO — General Purpose I/O

> STM32F401RE · HAL Reference · [Back to README](../../README.md)

---

## Overview

GPIO (General Purpose Input/Output) is the most fundamental peripheral. On the STM32F401RE, all I/O pins belong to one of the GPIO ports: **GPIOA** through **GPIOE** and **GPIOH**.

---

## CubeMX Configuration

| Setting | Options |
|---------|---------|
| **Mode** | Input / Output Push-Pull / Output Open-Drain / Alternate Function PP / AF Open-Drain / Analog |
| **Pull** | No pull / Pull-up / Pull-down |
| **Speed** | Low / Medium / High / Very High |

> 💡 For most LED outputs: **Output Push-Pull, No pull, Low speed**  
> For most button inputs: **Input, Pull-up** (button connects pin to GND)

---

## Common HAL API

```c
#include "main.h"

/* --- Output --- */
// Set HIGH
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

// Set LOW
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

// Toggle
HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);


/* --- Input --- */
GPIO_PinState state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
if (state == GPIO_PIN_RESET) {
    // Button pressed (active-low with pull-up)
}


/* --- Multiple pins at once (same port) --- */
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2, GPIO_PIN_SET);
```

---

## Nucleo-F401RE On-Board Resources

| Resource | GPIO | Direction | Notes |
|----------|------|-----------|-------|
| **LD2** (green LED) | PA5 | Output | Active HIGH |
| **B1** (blue button) | PC13 | Input | Active LOW (pull-up) |
| **USART2 TX** | PA2 | AF | Virtual COM Port |
| **USART2 RX** | PA3 | AF | Virtual COM Port |

---

## Useful Patterns

### Blink LED

```c
while (1) {
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    HAL_Delay(500);  // 500 ms
}
```

### Read Button State

```c
if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET) {
    // Button is pressed
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
} else {
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
}
```

---

## References

- RM0368 §8 — General-purpose I/Os (GPIO)
- HAL documentation: `stm32f4xx_hal_gpio.h`
