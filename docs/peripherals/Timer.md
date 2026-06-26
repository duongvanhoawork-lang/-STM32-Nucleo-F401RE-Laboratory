# Timer — TIM Peripheral

> STM32F401RE · HAL Reference · [Back to README](../../README.md)

---

## Overview

The STM32F401RE has **11 timers**:

| Timer | Type | Channels | Max Clock |
|-------|------|----------|-----------|
| TIM1 | Advanced | 4 | 84 MHz |
| TIM2 | General (32-bit) | 4 | 84 MHz |
| TIM3 | General (16-bit) | 4 | 84 MHz |
| TIM4 | General (16-bit) | 4 | 84 MHz |
| TIM5 | General (32-bit) | 4 | 84 MHz |
| TIM9 | General (16-bit) | 2 | 84 MHz |
| TIM10 | General (16-bit) | 1 | 84 MHz |
| TIM11 | General (16-bit) | 1 | 84 MHz |

> ⚠️ TIM1 is an **advanced** timer with complementary outputs and dead-time insertion.

---

## Key Registers / CubeMX Parameters

| Parameter | Register | Description |
|-----------|----------|-------------|
| **PSC** | Prescaler | Divides input clock. Timer clock = `fCLK / (PSC + 1)` |
| **ARR** | Auto-Reload Register | Counter resets at this value |
| **CCR** | Capture/Compare Reg | PWM duty cycle threshold |

---

## Period Formula

$$T_{interrupt} = \frac{(PSC + 1) \times (ARR + 1)}{f_{TIMER}}$$

The Nucleo-F401RE runs at **84 MHz** (both APB1 and APB2 timers at 84 MHz with default CubeMX config).

### Examples

| PSC | ARR | f_TIMER | Period |
|-----|-----|---------|--------|
| 8399 | 999 | 84 MHz | **100 ms** (10 Hz) |
| 83999 | 999 | 84 MHz | **1 s** (1 Hz) |
| 839 | 999 | 84 MHz | **10 ms** (100 Hz) |
| 0 | 83999 | 84 MHz | **1 ms** (1 kHz) |

---

## HAL API

### Base Timer (Periodic Interrupt)

```c
/* Start timer with interrupt */
HAL_TIM_Base_Start_IT(&htim2);

/* Stop timer */
HAL_TIM_Base_Stop_IT(&htim2);

/* Callback — fires every ARR+1 ticks of divided clock */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    }
    if (htim->Instance == TIM3) {
        // Another timer
    }
}
```

### Blocking Delay (Polling Mode)

```c
HAL_TIM_Base_Start(&htim2);
while (__HAL_TIM_GET_COUNTER(&htim2) < 1000);  // Wait for 1000 ticks
HAL_TIM_Base_Stop(&htim2);
__HAL_TIM_SET_COUNTER(&htim2, 0);              // Reset counter
```

---

## Multiple Timer Priority

Use NVIC preemption priority to control which timer ISR runs first:

| Priority Value | Meaning |
|---------------|---------|
| 0 | Highest |
| 15 | Lowest |

Set in CubeMX: **NVIC** → **TIM2 global interrupt** → **Preemption Priority**

---

## Common Mistakes

| Mistake | Fix |
|---------|-----|
| Timer doesn't trigger | Check `HAL_TIM_Base_Start_IT()` is called, and NVIC is enabled |
| Wrong period | Recalculate: `T = (PSC+1)*(ARR+1)/84000000` |
| Callback called for wrong timer | Always check `htim->Instance == TIMx` inside callback |
| Callback not firing | Ensure `HAL_TIM_IRQHandler()` is in `stm32f4xx_it.c` |

---

## References

- RM0368 §14–18 — General-purpose timers (TIM2–TIM5, TIM9–TIM11)
- RM0368 §13 — Advanced-control timer (TIM1)
- HAL: `stm32f4xx_hal_tim.h`
