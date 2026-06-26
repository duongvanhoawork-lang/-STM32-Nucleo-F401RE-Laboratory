# I2C — Inter-Integrated Circuit

> STM32F401RE · HAL Reference · [Back to README](../../README.md)

---

## Overview

I2C is a **synchronous, half-duplex** multi-device bus using only **2 wires**:

| Signal | Description |
|--------|-------------|
| **SCL** | Serial Clock (master drives) |
| **SDA** | Serial Data (bidirectional) |

Each device has a **7-bit address** (some use 10-bit). The bus requires **pull-up resistors** (typically 4.7 kΩ to VCC).

STM32F401RE has **3 I2C** peripherals.

---

## I2C Pins (Nucleo-F401RE)

| I2C | SCL | SDA |
|-----|-----|-----|
| I2C1 | PB8 | PB9 |
| I2C2 | PB10 | PB3 |
| I2C3 | PA8 | PB4 |

---

## Common Standard Speeds

| Mode | Speed |
|------|-------|
| Standard Mode | 100 kHz |
| Fast Mode | 400 kHz |
| Fast Mode+ | 1 MHz (not all devices support) |

---

## HAL API

```c
/* ---- Master Transmit ---- */
uint8_t data[2] = {REG_ADDR, value};
HAL_I2C_Master_Transmit(&hi2c1, (DEV_ADDR << 1), data, 2, HAL_MAX_DELAY);

/* ---- Master Receive ---- */
uint8_t buf[6];
HAL_I2C_Master_Receive(&hi2c1, (DEV_ADDR << 1), buf, 6, HAL_MAX_DELAY);

/* ---- Write to register (most common sensor pattern) ---- */
uint8_t reg_data = 0x01;
HAL_I2C_Mem_Write(&hi2c1,
                  DEV_ADDR << 1,          // 7-bit addr shifted left
                  REG_ADDR,               // register address
                  I2C_MEMADD_SIZE_8BIT,   // register address size
                  &reg_data, 1,           // data + length
                  HAL_MAX_DELAY);

/* ---- Read from register ---- */
uint8_t buf[2];
HAL_I2C_Mem_Read(&hi2c1,
                 DEV_ADDR << 1,
                 REG_ADDR,
                 I2C_MEMADD_SIZE_8BIT,
                 buf, 2,
                 HAL_MAX_DELAY);
```

> ⚠️ HAL always uses the **left-shifted address** (8-bit form): `DEV_ADDR << 1`

---

## Scanning for I2C Devices

```c
/* Scan all 7-bit addresses and print which respond */
for (uint8_t addr = 1; addr < 128; addr++) {
    if (HAL_I2C_IsDeviceReady(&hi2c1, addr << 1, 1, 10) == HAL_OK) {
        char buf[32];
        sprintf(buf, "Found device at 0x%02X\r\n", addr);
        HAL_UART_Transmit(&huart2, (uint8_t*)buf, strlen(buf), HAL_MAX_DELAY);
    }
}
```

---

## Common I2C Devices

| Device | Address (7-bit) | Function |
|--------|-----------------|----------|
| SSD1306 OLED | 0x3C / 0x3D | 128×64 display |
| MPU-6050 | 0x68 / 0x69 | Gyro + Accel |
| BMP280 | 0x76 / 0x77 | Pressure + Temp |
| PCF8574 | 0x20–0x27 | I2C GPIO expander |
| DS3231 RTC | 0x68 | Real-time clock |

---

## References

- RM0368 §23 — Inter-integrated circuit (I2C) interface
- HAL: `stm32f4xx_hal_i2c.h`

> 📝 *Notes for this topic will be updated as the lab progresses.*
