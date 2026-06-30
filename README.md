# 🔬 STM32 Nucleo-F401RE — Companion Resource Hub

<div align="center">

[![Main Lab Repository](https://img.shields.io/badge/🔗%20Main%20Lab%20Repository-duongvanhoawork--lang-181717?style=for-the-badge&logo=github)](https://github.com/duongvanhoawork-lang/-STM32-Nucleo-F401RE-Laboratory)
[![STM32CubeIDE](https://img.shields.io/badge/STM32CubeIDE-1.15+-03234B?style=for-the-badge&logo=stmicroelectronics&logoColor=white)](https://www.st.com/en/development-tools/stm32cubeide.html)
[![Board](https://img.shields.io/badge/Board-Nucleo--F401RE-blue?style=for-the-badge&logo=arm&logoColor=white)](https://www.st.com/en/evaluation-tools/nucleo-f401re.html)
[![University](https://img.shields.io/badge/FPT%20University-CS200558-orange?style=for-the-badge)](https://fpt.edu.vn)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)

<br/>

> **A companion resource hub for the [STM32 Nucleo-F401RE Laboratory](https://github.com/duongvanhoawork-lang/-STM32-Nucleo-F401RE-Laboratory).**  
> Cheat sheets · Wiring guides · Peripheral references · Progress tracking · Study notes.

<br/>

[📖 Peripheral Reference](#-peripheral-quick-reference) &nbsp;•&nbsp;
[🗺️ Roadmap](#️-learning-roadmap) &nbsp;•&nbsp;
[📌 Projects](#-project-index) &nbsp;•&nbsp;
[🛠️ Setup](#️-environment-setup) &nbsp;•&nbsp;
[📚 Resources](#-resources)

</div>

---

## 📁 Repository Structure

```
STM32_NUCLEO_F401RE/                          ← This companion repo
│
├── 📄 README.md                              ← You are here
├── 📄 PROGRESS.md                            ← Lab & topic completion tracker
├── 📄 CONTRIBUTING.md                        ← Contribution guidelines
├── 📄 LICENSE                                ← MIT License
│
├── 📂 01_GPIO_LED_Button/                    ← GPIO Lab materials
│   └── 📂 STM32_NUCLEO_F401RE/
├── 📂 02_Timers_PWM/                         ← Timer & PWM Lab materials
│   ├── 📂 Exercise_Easy/
│   └── 📂 Exercise_Hard/
├── 📂 03_Interrupts/                         ← EXTI Lab materials
├── 📂 04_UART_Communication/                 ← UART Lab materials
├── 📂 05_ADC_DAC/                            ← ADC/DAC Lab materials
├── 📂 Final_Project/                         ← Final Coursework Project
│   ├── 📂 Hardware/
│   ├── 📂 Software/
│   └── 📂 Documentation/
│
├── 📂 docs/                                  ← Documentation & notes
│   ├── setup/
│   │   ├── environment-setup.md              ← STM32CubeIDE + Wokwi setup guide
│   │   └── first-project.md                 ← First blinky walkthrough
│   ├── peripherals/
│   │   ├── GPIO.md                           ← GPIO cheat sheet
│   │   ├── EXTI.md                           ← External Interrupt reference
│   │   ├── Timer.md                          ← Timer / TIM reference
│   │   ├── PWM.md                            ← PWM configuration guide
│   │   ├── ADC.md                            ← ADC reference
│   │   ├── UART.md                           ← UART communication guide
│   │   ├── SPI.md                            ← SPI reference
│   │   ├── I2C.md                            ← I2C reference
│   │   ├── DMA.md                            ← DMA reference
│   │   ├── FreeRTOS.md                       ← FreeRTOS basics
│   │   └── LowPower.md                       ← Low Power modes
│   └── wiring/
│       ├── nucleo-f401re-pinout.md           ← Board pinout quick reference
│       └── common-circuits.md               ← Common wiring patterns
│
├── 📂 cheatsheets/                           ← Quick references
│   ├── hal-api-quick-ref.md                  ← HAL API one-liners
│   ├── cubemx-config-tips.md                 ← CubeMX configuration tips
│   └── debugging-tips.md                    ← Common bugs & fixes
│
└── 📂 resources/
    └── references.md                        ← Curated learning resources
```

---

## 🔗 Relationship to Main Repository

This is a **companion resource hub** — not a replacement for the main lab repo.

| | **This Repo** (Companion Hub) | **Main Lab Repo** |
|---|---|---|
| **Purpose** | Reference docs, cheat sheets, tracker | Lab assignments, CubeIDE projects, reports |
| **Contains** | Guides, diagrams, notes, progress log | `.ioc` files, source code, `.docx` reports |
| **Link** | ← You are here | [→ Main Repository](https://github.com/duongvanhoawork-lang/-STM32-Nucleo-F401RE-Laboratory) |

> All graded submissions and STM32CubeIDE projects live in the [**main repository**](https://github.com/duongvanhoawork-lang/-STM32-Nucleo-F401RE-Laboratory).

---

## 🗺️ Learning Roadmap

```mermaid
graph LR
    A[🟢 GPIO] --> B[⚡ EXTI]
    B --> C[⏱️ Timer]
    C --> D[🎛️ PWM]
    D --> E[📊 ADC]
    E --> F[📡 UART]
    F --> G[🔌 SPI]
    F --> H[🔗 I2C]
    G --> I[🚀 DMA]
    H --> I
    I --> J[🧵 FreeRTOS]
    J --> K[🔋 Low Power]
    K --> L[🏁 Final Project]

    style A fill:#22c55e,color:#fff
    style B fill:#22c55e,color:#fff
    style C fill:#22c55e,color:#fff
    style D fill:#22c55e,color:#fff
    style E fill:#22c55e,color:#fff
    style F fill:#22c55e,color:#fff
    style G fill:#f59e0b,color:#fff
    style H fill:#f59e0b,color:#fff
    style I fill:#6b7280,color:#fff
    style J fill:#6b7280,color:#fff
    style K fill:#6b7280,color:#fff
    style L fill:#6b7280,color:#fff
```

| # | Topic | Status | Ref |
|---|-------|--------|-----|
| 1 | GPIO | ✅ Completed | [docs →](docs/peripherals/GPIO.md) |
| 2 | EXTI | ✅ Completed | [docs →](docs/peripherals/EXTI.md) |
| 3 | Timer | ✅ Completed | [docs →](docs/peripherals/Timer.md) |
| 4 | PWM | ✅ Completed | [docs →](docs/peripherals/PWM.md) |
| 5 | ADC | ✅ Completed | [docs →](docs/peripherals/ADC.md) |
| 6 | UART | ✅ Completed | [docs →](docs/peripherals/UART.md) |
| 7 | SPI | 🔄 In Progress | [docs →](docs/peripherals/SPI.md) |
| 8 | I2C | 🔄 In Progress | [docs →](docs/peripherals/I2C.md) |
| 9 | DMA | ⏳ Planned | [docs →](docs/peripherals/DMA.md) |
| 10 | FreeRTOS | ⏳ Planned | [docs →](docs/peripherals/FreeRTOS.md) |
| 11 | Low Power | ⏳ Planned | [docs →](docs/peripherals/LowPower.md) |
| 12 | Final Project | ⏳ Planned | — |

📄 Full progress log → [PROGRESS.md](PROGRESS.md)

---

## 📌 Project Index

| # | Project | Peripheral(s) | Platform | Main Repo |
|---|---------|---------------|----------|-----------|
| 01 | External Interrupt with Push Buttons & RGB LEDs | GPIO, EXTI | Hardware | [→ View](https://github.com/duongvanhoawork-lang/-STM32-Nucleo-F401RE-Laboratory/tree/main/03_Interrupts) |
| 02 | Button Counter with RGB LED Priority & Serial Output | GPIO, EXTI, UART | Hardware | [→ View](https://github.com/duongvanhoawork-lang/-STM32-Nucleo-F401RE-Laboratory/tree/main/03_Interrupts) |
| 03 | External Interrupt and Pull-Up Button | GPIO, EXTI | Hardware | [→ View](https://github.com/duongvanhoawork-lang/-STM32-Nucleo-F401RE-Laboratory/tree/main/03_Interrupts) |
| 04 | Car Control System | GPIO, PWM, UART | Hardware | [→ View](https://github.com/duongvanhoawork-lang/-STM32-Nucleo-F401RE-Laboratory/tree/main/Final_Project/Documentation) |
| 05 | Potentiometer → LED Brightness (ADC + PWM) | ADC, PWM, Timer | Mbed OS | [→ View](https://github.com/duongvanhoawork-lang/-STM32-Nucleo-F401RE-Laboratory/tree/main/05_ADC_DAC) |
| 06 | PWM Timer & Periodic Interrupts | Timer, PWM | Wokwi Sim | [→ View](https://github.com/duongvanhoawork-lang/-STM32-Nucleo-F401RE-Laboratory/tree/main/02_Timers_PWM) |
| 07 | UART-Based Servo Motor Control | UART, PWM, Timer | Wokwi Sim | [→ View](https://github.com/duongvanhoawork-lang/-STM32-Nucleo-F401RE-Laboratory/tree/main/04_UART_Communication) |

---

## ⚡ Peripheral Quick Reference

<details>
<summary><strong>🔌 GPIO — General Purpose I/O</strong></summary>

```c
/* Common HAL API calls */
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);    // Drive HIGH
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);  // Drive LOW
HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);                 // Toggle
GPIO_PinState s = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);// Read input

/* Key CubeMX settings */
// Mode:  Output Push-Pull / Input / Alternate Function
// Pull:  Pull-up / Pull-down / No pull
// Speed: Low / Medium / High / Very High
```

📄 [Full GPIO Reference →](docs/peripherals/GPIO.md)

</details>

<details>
<summary><strong>⚡ EXTI — External Interrupts</strong></summary>

```c
/* Override this weak callback in main.c */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == BUTTON_Pin) {
        // ISR logic — keep it short!
        // Use flags + main loop for heavy processing
    }
}
```

> ⚠️ Always configure the GPIO pin as **Input** with the correct trigger edge (Rising/Falling/Both) in CubeMX.

📄 [Full EXTI Reference →](docs/peripherals/EXTI.md)

</details>

<details>
<summary><strong>⏱️ Timer — TIM Peripheral</strong></summary>

```c
/* Base Timer with Interrupt */
HAL_TIM_Base_Start_IT(&htim2);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {
        // Called every (PSC+1)*(ARR+1) / fCLK seconds
    }
}

/* Timer period formula */
// Interrupt period = (PSC + 1) × (ARR + 1) / TIMER_CLOCK_Hz
// Example: PSC=8399, ARR=999 → 1s at 84 MHz
```

📄 [Full Timer Reference →](docs/peripherals/Timer.md)

</details>

<details>
<summary><strong>🎛️ PWM — Pulse Width Modulation</strong></summary>

```c
/* Start PWM output */
HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

/* Set duty cycle (0 to ARR) */
__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, duty_value);

/* Servo angle → PWM (50Hz, ARR=20000-1) */
// 0°  → CCR = 500   (0.5 ms pulse)
// 90° → CCR = 1500  (1.5 ms pulse)
// 180°→ CCR = 2500  (2.5 ms pulse)
```

📄 [Full PWM Reference →](docs/peripherals/PWM.md)

</details>

<details>
<summary><strong>📊 ADC — Analog-to-Digital Converter</strong></summary>

```c
/* Polling mode (blocking) */
HAL_ADC_Start(&hadc1);
HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
uint32_t raw = HAL_ADC_GetValue(&hadc1);  // 0–4095 (12-bit)
float voltage = raw * 3.3f / 4095.0f;    // Convert to volts

/* Mbed OS equivalent */
AnalogIn pot(A0);
float value   = pot.read();        // 0.0–1.0
float voltage = value * 3.3f;
int   adc_val = (int)(value * 4095.0f);
```

📄 [Full ADC Reference →](docs/peripherals/ADC.md)

</details>

<details>
<summary><strong>📡 UART — Serial Communication</strong></summary>

```c
/* Transmit (blocking) */
HAL_UART_Transmit(&huart2, (uint8_t*)"Hello\r\n", 7, HAL_MAX_DELAY);

/* Receive 1 byte (blocking) */
uint8_t rx;
HAL_UART_Receive(&huart2, &rx, 1, HAL_MAX_DELAY);

/* Enable printf → add to main.c (retarget stdout) */
int __io_putchar(int ch) {
    HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return ch;
}
// Also: add #include <stdio.h> and ensure "Use MicroLIB" (Keil) or
// syscalls.c retargeting (GCC) is in place.
```

> 💡 Nucleo-F401RE virtual COM port uses **USART2** (PA2=TX, PA3=RX) via the on-board ST-LINK.

📄 [Full UART Reference →](docs/peripherals/UART.md)

</details>

<details>
<summary><strong>🔌 SPI — Serial Peripheral Interface</strong></summary>

```c
/* Transmit + Receive (Full Duplex, blocking) */
uint8_t tx_data[2] = {0x01, 0x02};
uint8_t rx_data[2];
HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET); // CS LOW
HAL_SPI_TransmitReceive(&hspi1, tx_data, rx_data, 2, HAL_MAX_DELAY);
HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);   // CS HIGH
```

📄 [Full SPI Reference →](docs/peripherals/SPI.md)

</details>

<details>
<summary><strong>🔗 I2C — Inter-Integrated Circuit</strong></summary>

```c
/* Write to I2C device */
uint8_t data = 0xAB;
HAL_I2C_Master_Transmit(&hi2c1, (DEV_ADDR << 1), &data, 1, HAL_MAX_DELAY);

/* Read from I2C device */
uint8_t buf[2];
HAL_I2C_Master_Receive(&hi2c1, (DEV_ADDR << 1), buf, 2, HAL_MAX_DELAY);

/* Write to register then read (common sensor pattern) */
HAL_I2C_Mem_Read(&hi2c1, (DEV_ADDR << 1), REG_ADDR,
                 I2C_MEMADD_SIZE_8BIT, buf, 2, HAL_MAX_DELAY);
```

📄 [Full I2C Reference →](docs/peripherals/I2C.md)

</details>

---

## 🛠️ Environment Setup

### Requirements

| Tool | Version | Download |
|------|---------|----------|
| STM32CubeIDE | ≥ 1.15 | [st.com](https://www.st.com/en/development-tools/stm32cubeide.html) |
| STM32CubeMX | ≥ 6.11 | [st.com](https://www.st.com/en/development-tools/stm32cubemx.html) |
| STM32Cube F4 FW Pack | ≥ 1.28 | Via CubeIDE Package Manager |
| Wokwi Simulator | Online | [wokwi.com](https://wokwi.com) |
| ST-LINK Driver | Latest | [st.com](https://www.st.com/en/development-tools/stsw-link004.html) |
| Mbed CLI / Studio | 6.x | [mbed.com](https://os.mbed.com) |

### Quick Start

```bash
# 1. Clone the main lab repository (lab assignments, code, reports)
git clone https://github.com/duongvanhoawork-lang/-STM32-Nucleo-F401RE-Laboratory.git

# 2. Clone this companion hub alongside it
git clone https://github.com/duongvanhoawork-lang/STM32_NUCLEO_F401RE.git

# 3. In STM32CubeIDE: File → Open Projects from Filesystem
#    → Navigate to the cloned main repo
```

📄 [Detailed Environment Setup →](docs/setup/environment-setup.md)

---

## 📋 Hardware Reference

### STM32 Nucleo-F401RE Specifications

| Parameter | Value |
|-----------|-------|
| MCU | STM32F401RET6 |
| Core | ARM Cortex-M4 + FPU @ **84 MHz** |
| Flash | 512 KB |
| SRAM | 96 KB |
| GPIO | 50 I/O pins (5V tolerant) |
| Timers | 11 (TIM1–TIM11, incl. 1 advanced) |
| ADC | 1× 12-bit, 16 channels |
| UART / USART | 3 |
| SPI | 3 |
| I2C | 3 |
| USB | Full-Speed USB 2.0 OTG |
| Debugger | ST-LINK/V2-1 (on-board, no extra hardware needed) |

📄 [Full Pinout Reference →](docs/wiring/nucleo-f401re-pinout.md)

---

## 📝 Study Notes — CS200558

> Personal notes from the embedded systems laboratory at FPT University (2025–2026).

| Chapter | Topic | Notes File |
|---------|-------|------------|
| Ch. 1–2 | GPIO Basics | [GPIO.md](docs/peripherals/GPIO.md) |
| Ch. 3 | Interrupts & EXTI | [EXTI.md](docs/peripherals/EXTI.md) |
| Ch. 4 | Active Learning — Pull-up Button | [EXTI.md](docs/peripherals/EXTI.md) |
| Ch. 5 | Timers | [Timer.md](docs/peripherals/Timer.md) |
| Ch. 6 | ADC & PWM | [ADC.md](docs/peripherals/ADC.md) · [PWM.md](docs/peripherals/PWM.md) |
| Ch. 8 | PWM / Timer Simulation (Wokwi) | [PWM.md](docs/peripherals/PWM.md) |
| Ch. 9 | UART Servo Control (Wokwi) | [UART.md](docs/peripherals/UART.md) |

---

## 📚 Resources

| Resource | Description |
|----------|-------------|
| [STM32F401RE Reference Manual (RM0368)](https://www.st.com/resource/en/reference_manual/rm0368-stm32f401xbc-and-stm32f401xde-advanced-armbased-32bit-mcus-stmicroelectronics.pdf) | Full MCU register reference |
| [Nucleo-F401RE User Manual (UM1724)](https://www.st.com/resource/en/user_manual/um1724-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf) | Board hardware guide & schematics |
| [STM32 HAL & LL Driver Guide (UM1725)](https://www.st.com/resource/en/user_manual/um1725-description-of-stm32f4-hal-and-lowlayer-drivers-stmicroelectronics.pdf) | Official HAL API documentation |
| [Wokwi STM32 Simulator](https://wokwi.com/stm32) | Free online STM32 simulation |
| [Mbed OS Documentation](https://os.mbed.com/docs/mbed-os/latest/) | Mbed OS 6 API reference |
| [STM32 Community Forum](https://community.st.com) | Official ST Q&A community |
| [FPT University](https://fpt.edu.vn) | Course institution |

📄 [Full Resources List →](resources/references.md)

---

## 🤝 Contributing

This is a personal academic repository. Contributions that improve notes or fix errors are welcome.

- **Found an error or typo?** → Open an [issue](https://github.com/duongvanhoawork-lang/STM32_NUCLEO_F401RE/issues)
- **Want to suggest an improvement?** → Submit a [pull request](https://github.com/duongvanhoawork-lang/STM32_NUCLEO_F401RE/pulls)

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

---

## 📜 License

This project is licensed under the **MIT License** — see [LICENSE](LICENSE) for details.

---

<div align="center">

**Duong Van Hoa** &nbsp;·&nbsp; FPT University &nbsp;·&nbsp; CS200558 &nbsp;·&nbsp; 2025–2026

[![GitHub](https://img.shields.io/badge/GitHub-duongvanhoawork--lang-181717?style=flat-square&logo=github)](https://github.com/duongvanhoawork-lang)
[![Main Repo](https://img.shields.io/badge/Main%20Lab%20Repo-View%20→-03234B?style=flat-square&logo=stmicroelectronics)](https://github.com/duongvanhoawork-lang/-STM32-Nucleo-F401RE-Laboratory)

*"Learning embedded systems one peripheral at a time."*

</div>
