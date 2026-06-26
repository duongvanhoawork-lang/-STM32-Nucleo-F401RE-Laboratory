# Low Power Modes

> STM32F401RE · HAL Reference · [Back to README](../../README.md)

---

## Overview

The STM32F401RE supports multiple low-power modes to reduce current consumption in battery-powered applications.

| Mode | CPU | Clocks | RAM | Wake-up |
|------|-----|--------|-----|---------|
| **Sleep** | Stopped | Running | Retained | Any interrupt |
| **Stop** | Stopped | Stopped | Retained | EXTI, RTC, IWDG |
| **Standby** | Stopped | Stopped | Lost | WKUP pin, RTC, NRST |

---

## Current Consumption (Typical)

| Mode | Current |
|------|---------|
| Run (84 MHz, all on) | ~27 mA |
| Sleep | ~5 mA |
| Stop | ~400 µA |
| Standby | ~2.4 µA |

---

## HAL API

### Sleep Mode

```c
/* Enter Sleep mode — CPU stopped, peripherals active */
HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
// WFI = Wait For Interrupt
// CPU resumes from next line after any interrupt fires
```

### Stop Mode

```c
/* Enter Stop mode — very low power, RAM retained */
HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
// After wake-up, re-initialize system clock:
SystemClock_Config();
```

### Standby Mode

```c
/* Enable wake-up pin (PA0 = WKUP1) */
HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);

/* Clear standby flag */
__HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);

/* Enter Standby — RAM lost, returns from reset on wake */
HAL_PWR_EnterSTANDBYMode();
// Code after this line will NOT execute
```

---

## Wake-up Sources

| Source | Sleep | Stop | Standby |
|--------|-------|------|---------|
| Any IRQ | ✅ | ✅ | ❌ |
| EXTI line | ✅ | ✅ | ❌ |
| WKUP pin (PA0) | ✅ | ✅ | ✅ |
| RTC alarm | ✅ | ✅ | ✅ |
| NRST pin | ✅ | ✅ | ✅ |

---

## Tips

- After waking from **Stop** mode, the HSI oscillator is used → call `SystemClock_Config()` to restore 84 MHz
- Disable unused peripherals before entering low-power mode
- Configure GPIO pins as **Analog Input** (no pull) to minimize leakage current

---

## References

- RM0368 §5 — Power controller (PWR)
- HAL: `stm32f4xx_hal_pwr.h`
- AN4488 — Getting started with STM32F4xx MCU power modes

> 📝 *Detailed notes will be added when Low Power lab is completed.*
