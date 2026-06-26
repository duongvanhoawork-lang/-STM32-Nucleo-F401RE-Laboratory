# ADC — Analog-to-Digital Converter

> STM32F401RE · HAL Reference · [Back to README](../../README.md)

---

## Overview

The STM32F401RE has **one ADC (ADC1)** with:
- **12-bit resolution** → output range: 0–4095
- Up to **16 external channels**
- Reference voltage: **VREF+ = 3.3 V** on Nucleo

$$V_{input} = \frac{ADC_{value}}{4095} \times V_{REF+}$$

---

## CubeMX Configuration

| Parameter | Recommended Setting |
|-----------|---------------------|
| Resolution | 12 bits |
| Data Alignment | Right |
| Scan Conversion Mode | Disabled (single channel) |
| Continuous Conversion | Disabled (polling) |
| Sampling Time | 84 Cycles (good for most sensors) |

---

## Nucleo-F401RE ADC Pins

| Arduino Label | STM32 Pin | ADC Channel |
|---------------|-----------|-------------|
| A0 | PA0 | ADC1_IN0 |
| A1 | PA1 | ADC1_IN1 |
| A2 | PA4 | ADC1_IN4 |
| A3 | PB0 | ADC1_IN8 |
| A4 | PC1 | ADC1_IN11 |
| A5 | PC0 | ADC1_IN10 |

---

## HAL API

### Polling Mode (Blocking)

```c
/* Single conversion — blocking */
HAL_ADC_Start(&hadc1);
HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
uint32_t raw = HAL_ADC_GetValue(&hadc1);   // 0 – 4095
HAL_ADC_Stop(&hadc1);

/* Convert to voltage */
float voltage = raw * 3.3f / 4095.0f;
```

### Continuous Polling

```c
HAL_ADC_Start(&hadc1);
while (1) {
    if (HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK) {
        uint32_t raw = HAL_ADC_GetValue(&hadc1);
        // process raw
    }
}
```

### DMA Mode (Non-Blocking)

```c
uint32_t adc_buffer[NUM_CHANNELS];

/* Start ADC with DMA */
HAL_ADC_Start_DMA(&hadc1, adc_buffer, NUM_CHANNELS);

/* Callback when conversion complete */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    if (hadc->Instance == ADC1) {
        // adc_buffer now has fresh data
    }
}
```

---

## Mbed OS Equivalent

```cpp
AnalogIn pot(A0);           // A0 = PA0 = ADC1_IN0

float value   = pot.read();              // 0.0 – 1.0
float voltage = value * 3.3f;           // volts
int   adc_raw = (int)(value * 4095.0f); // 0 – 4095
```

> 📌 Used in [Potentiometer_Servo_STM32_F401RE](https://github.com/duongvanhoawork-lang/-STM32-Nucleo-F401RE-Laboratory/tree/main/Potentiometer_Servo_STM32_F401RE)

---

## Potentiometer Wiring

```
VCC (3.3V) ──┐
             │
          [POT]  ← 10kΩ recommended
             │
          ADC Pin (A0/PA0)
             │
          [POT]
             │
GND ─────────┘
```

---

## Common Mistakes

| Problem | Fix |
|---------|-----|
| Always reads 0 | Check the GPIO is configured as **Analog** in CubeMX |
| Always reads 4095 | Check pull-up isn't set; pin should be floating or analog |
| Noise in readings | Add a 100nF capacitor between the ADC pin and GND; increase sampling time |
| Wrong voltage | Verify VREF+ is connected to 3.3 V |

---

## References

- RM0368 §11 — Analog-to-digital converter (ADC)
- HAL: `stm32f4xx_hal_adc.h`
- Lab: [Potentiometer_Servo_STM32_F401RE](https://github.com/duongvanhoawork-lang/-STM32-Nucleo-F401RE-Laboratory/tree/main/Potentiometer_Servo_STM32_F401RE)
