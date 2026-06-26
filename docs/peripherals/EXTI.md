# EXTI — External Interrupts

> STM32F401RE · HAL Reference · [Back to README](../../README.md)

---

## Overview

EXTI (External Interrupt/Event Controller) allows GPIO pin changes to trigger ISRs (Interrupt Service Routines) without polling. The STM32F401RE has 23 EXTI lines.

Each GPIO pin number maps to a single EXTI line — e.g., PA0, PB0, PC0 all map to **EXTI0**, but only **one can be active** at a time.

---

## CubeMX Configuration

1. Select the GPIO pin → set mode to:
   - `GPIO_EXTI_Rising` — triggers on LOW→HIGH
   - `GPIO_EXTI_Falling` — triggers on HIGH→LOW
   - `GPIO_EXTI_Rising_Falling` — both edges
2. Enable **NVIC** → check the corresponding EXTIx interrupt
3. Set **priority** (lower number = higher priority)

---

## NVIC Priority Groups

| Priority | EXTI Lines | IRQ Handler |
|----------|-----------|-------------|
| Single pin | EXTI0–EXTI4 | `EXTI0_IRQHandler` ... `EXTI4_IRQHandler` |
| Group | EXTI5–EXTI9 | `EXTI9_5_IRQHandler` |
| Group | EXTI10–EXTI15 | `EXTI15_10_IRQHandler` |

---

## HAL Callback

CubeMX generates the IRQ handlers automatically. Override the **weak** callback in `main.c`:

```c
/* Called by HAL for any EXTI line */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == B1_Pin) {
        // Button interrupt — keep this short!
        button_flag = 1;  // Set a flag, process in main loop
    }

    if (GPIO_Pin == GPIO_PIN_1) {
        // Another pin
    }
}
```

> ⚠️ **ISR Best Practices**
> - Keep ISR code **as short as possible**
> - **Never** call `HAL_Delay()` inside an ISR — it blocks indefinitely
> - Use **volatile flags** to communicate between ISR and main loop
> - Use **`__disable_irq()` / `__enable_irq()`** for critical sections

---

## Pattern: Flag + Main Loop

```c
/* In main.c — global volatile flag */
volatile uint8_t button_pressed = 0;

/* ISR — sets flag only */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == B1_Pin) {
        button_pressed = 1;
    }
}

/* Main loop — processes flag */
while (1) {
    if (button_pressed) {
        button_pressed = 0;
        // Do the actual work here
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    }
}
```

---

## Pattern: Counter with RGB LED Priority (Lab Reference)

```c
volatile uint8_t btn1_count = 0;
volatile uint8_t btn2_count = 0;
volatile uint8_t btn3_count = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if      (GPIO_Pin == BTN1_Pin) btn1_count++;
    else if (GPIO_Pin == BTN2_Pin) btn2_count++;
    else if (GPIO_Pin == BTN3_Pin) btn3_count++;
}

/* Main loop — RGB LED priority logic */
while (1) {
    if      (btn1_count > 0) { /* RED LED   — highest priority */ }
    else if (btn2_count > 0) { /* GREEN LED — medium priority  */ }
    else if (btn3_count > 0) { /* BLUE LED  — lowest priority  */ }
    else                     { /* All LEDs off                */ }
}
```

---

## Debouncing

Mechanical buttons "bounce" on press. Simple software debounce:

```c
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == B1_Pin) {
        HAL_Delay(20);  // Only safe outside ISR context (not recommended)
        // Better: check pin state is still active after delay using a timer
        if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET) {
            button_pressed = 1;
        }
    }
}
```

> 💡 For production code, use a **hardware debounce** (100nF cap) or a **TIM-based debounce timer**.

---

## References

- RM0368 §10 — External interrupt/event controller (EXTI)
- RM0368 §10.3.6 — NVIC interrupt priority
- HAL: `stm32f4xx_hal_gpio.h`, `stm32f4xx_it.c`
