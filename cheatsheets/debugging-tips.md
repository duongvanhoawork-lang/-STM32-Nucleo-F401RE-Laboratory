# Debugging Tips — STM32 Common Issues & Fixes

> [Back to README](../README.md)

---

## Build Errors

| Error | Cause | Fix |
|-------|-------|-----|
| `undefined reference to 'HAL_TIM_PWM_Start'` | Missing library | Ensure `stm32f4xx_hal_tim.c` is in your build |
| `implicit declaration of 'printf'` | Missing include | Add `#include <stdio.h>` |
| `multiple definition of 'main'` | Two `main()` functions | Check if old generated files are included |
| Linking error with `_write` | Missing syscalls | Add `syscalls.c` or enable retargeting |

---

## Hardware Issues

| Symptom | Likely Cause | Fix |
|---------|-------------|-----|
| LED never blinks | Wrong pin in CubeMX | Check PA5 is output, no alternate function |
| Button doesn't trigger EXTI | No pull-up | Enable pull-up in CubeMX or add 10kΩ pull-up resistor |
| UART garbled output | Wrong baud rate | Match baud rate on PC terminal with CubeMX config |
| ADC always reads 0 | Pin not set to Analog | Set GPIO mode to **Analog** in CubeMX |
| ADC always reads 4095 | Floating pin | Add pull-down or connect a signal source |
| Servo jittering | Noisy PWM or power | Add 100µF cap on servo VCC; ensure common GND |
| SPI not responding | Wrong CPOL/CPHA | Check device datasheet for correct SPI mode |
| I2C bus hangs | Missing pull-ups | Add 4.7kΩ resistor from SCL/SDA to VCC |

---

## Debugging Strategies

### 1. Printf to UART

```c
// Fastest way to debug values
printf("ADC raw = %lu\r\n", raw_value);
printf("State = %d\r\n", my_state);
```

### 2. Toggle GPIO as Scope Probe

```c
// Toggle a free GPIO to measure timing with oscilloscope/logic analyzer
HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_10);  // In ISR or critical point
```

### 3. HAL Return Value Check

```c
if (HAL_SPI_TransmitReceive(&hspi1, tx, rx, 2, 100) != HAL_OK) {
    printf("SPI error!\r\n");
    Error_Handler();
}
```

### 4. Use the Debugger (STM32CubeIDE)

- Set **breakpoints** in `HAL_GPIO_EXTI_Callback`
- Use **Watch expressions** to monitor variables
- Use **Live Expressions** for real-time variable monitoring without stopping
- **SWV (Serial Wire Viewer)** for printf without UART (requires SWO pin)

---

## Timer Period Sanity Check

```c
// Print calculated period to verify CubeMX config
float period = (float)(PSC + 1) * (ARR + 1) / 84000000.0f;
printf("Timer period = %.4f s (%.1f Hz)\r\n", period, 1.0f / period);
```

---

## Wokwi Simulation Tips

- Use `Serial.print()` or `HAL_UART_Transmit()` → check Wokwi **Serial Monitor**
- Check the `diagram.json` — ensure GPIO pins match your CubeMX config
- Wokwi may not simulate all peripherals (DMA, FreeRTOS timing may differ)
- Save simulations with a unique URL and link them in lab reports

---

## Common CubeMX Mistakes

| Mistake | Fix |
|---------|-----|
| Forgot to enable peripheral clock | CubeMX does this automatically — regenerate code |
| Changed `.ioc` file but didn't regenerate | `Project → Generate Code` |
| NVIC interrupt not enabled | CubeMX NVIC tab → check the interrupt box |
| Wrong timer channel for PWM output | Verify pin's alternate function in pinout table |
| `HAL_Delay()` in ISR | Remove it — use flags or timers instead |
