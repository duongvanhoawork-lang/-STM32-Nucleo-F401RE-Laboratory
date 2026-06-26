# SPI — Serial Peripheral Interface

> STM32F401RE · HAL Reference · [Back to README](../../README.md)

---

## Overview

SPI is a **synchronous, full-duplex** serial protocol using 4 wires:

| Signal | Direction | Description |
|--------|-----------|-------------|
| **SCK** | Master → Slave | Clock |
| **MOSI** | Master → Slave | Master Out Slave In |
| **MISO** | Slave → Master | Master In Slave Out |
| **CS/NSS** | Master → Slave | Chip Select (active LOW) |

STM32F401RE has **3 SPI** peripherals.

---

## SPI Pins (Nucleo-F401RE)

| SPI | SCK | MOSI | MISO |
|-----|-----|------|------|
| SPI1 | PA5 | PA7 | PA6 |
| SPI2 | PB13 | PB15 | PB14 |
| SPI3 | PC10 | PC12 | PC11 |

> ⚠️ **PA5** is shared with the on-board LED (LD2). Use SPI2/SPI3 to avoid conflict.

---

## CubeMX Configuration

| Parameter | Options |
|-----------|---------|
| Mode | Full-Duplex Master |
| Data Size | 8 bits (most common) |
| First Bit | MSB First |
| CPOL | 0 (idle LOW) or 1 (idle HIGH) |
| CPHA | 0 (capture on first edge) or 1 (capture on second edge) |
| Prescaler | Adjust for target SCK frequency |

**CPOL/CPHA modes:**

| Mode | CPOL | CPHA |
|------|------|------|
| 0 | 0 | 0 |
| 1 | 0 | 1 |
| 2 | 1 | 0 |
| 3 | 1 | 1 |

---

## HAL API

```c
/* Full-duplex transmit + receive (blocking) */
uint8_t tx[2] = {0x80, 0x00};  // Example: read register 0x00
uint8_t rx[2] = {0};

HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);   // CS LOW
HAL_SPI_TransmitReceive(&hspi1, tx, rx, 2, HAL_MAX_DELAY);
HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);     // CS HIGH

/* Transmit only */
HAL_SPI_Transmit(&hspi1, tx, 2, HAL_MAX_DELAY);

/* Receive only (sends dummy bytes) */
HAL_SPI_Receive(&hspi1, rx, 2, HAL_MAX_DELAY);
```

---

## Common Use Cases

| Device | SPI Mode | Notes |
|--------|----------|-------|
| SD Card | Mode 0 | 400 kHz init, up to 25 MHz |
| OLED (SSD1306) | Mode 0 | 4-wire or 3-wire |
| Accelerometer (ADXL345) | Mode 3 | Read bit = MSB of address byte |
| DAC (MCP4921) | Mode 0 | 12-bit output |

---

## References

- RM0368 §20 — Serial peripheral interface (SPI)
- HAL: `stm32f4xx_hal_spi.h`

> 📝 *Notes for this topic will be updated as the lab progresses.*
