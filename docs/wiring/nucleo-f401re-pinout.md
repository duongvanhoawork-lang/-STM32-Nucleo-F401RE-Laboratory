# Nucleo-F401RE Pinout Quick Reference

> [Back to README](../../README.md) · [Official Pinout PDF](https://www.st.com/resource/en/user_manual/um1724-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf)

---

## Arduino Connector (CN5 / CN9) → STM32 Pin Mapping

| Arduino | STM32 | AF Options | Notes |
|---------|-------|-----------|-------|
| A0 | PA0 | ADC1_IN0 | Analog input |
| A1 | PA1 | ADC1_IN1 | Analog input |
| A2 | PA4 | ADC1_IN4 | Analog input |
| A3 | PB0 | ADC1_IN8 | Analog input |
| A4 | PC1 | ADC1_IN11 | I2C SDA (with I2C2) |
| A5 | PC0 | ADC1_IN10 | I2C SCL (with I2C2) |
| D0 | PA3 | USART2_RX | Virtual COM RX |
| D1 | PA2 | USART2_TX | Virtual COM TX |
| D2 | PA10 | — | |
| D3 | PB3 | TIM2_CH2 | PWM |
| D4 | PB5 | — | |
| D5 | PB4 | TIM3_CH1 | PWM |
| D6 | PB10 | TIM2_CH3 | PWM (Mbed D6=PB10) |
| D7 | PA8 | TIM1_CH1 | |
| D8 | PA9 | USART1_TX | |
| D9 | PC7 | TIM3_CH2 | PWM |
| D10 | PB6 | SPI1_CS | |
| D11 | PA7 | SPI1_MOSI | |
| D12 | PA6 | SPI1_MISO | |
| D13 | PA5 | SPI1_SCK | **LD2 LED shared!** |
| D14 | PB9 | I2C1_SDA | |
| D15 | PB8 | I2C1_SCL | |

---

## On-Board Resources

| Resource | Pin | Direction | Active Level |
|----------|-----|-----------|--------------|
| **LD2** Green LED | PA5 | Output | HIGH |
| **B1** Blue Button | PC13 | Input | LOW (pull-up) |
| **USART2 TX** | PA2 | Output | — |
| **USART2 RX** | PA3 | Input | — |

---

## Morpho Connector (CN7 / CN10) — Key Pins

| Signal | Pin | Notes |
|--------|-----|-------|
| 3.3V | CN7-16 | Power output |
| 5V | CN7-18 | Power output |
| GND | CN7-20, CN10-14 | Ground |
| NRST | CN7-14 | Reset |
| BOOT0 | CN7-7 | Boot mode select |

---

## Clock Configuration (Default CubeMX)

```
HSE (8 MHz crystal on ST-LINK) → PLL → SYSCLK = 84 MHz
  AHB Prescaler: /1  → HCLK = 84 MHz
  APB1 Prescaler: /2 → PCLK1 = 42 MHz → TIM2,3,4,5 × 2 = 84 MHz
  APB2 Prescaler: /1 → PCLK2 = 84 MHz → TIM1,9,10,11 = 84 MHz
```

---

## References

- [UM1724 — STM32 Nucleo-64 User Manual](https://www.st.com/resource/en/user_manual/um1724-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf)
- [MB1136 Schematic](https://www.st.com/resource/en/schematic_pack/mb1136-f401re-c01_schematic.pdf)
