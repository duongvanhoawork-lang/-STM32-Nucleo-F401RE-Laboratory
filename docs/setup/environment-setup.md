# Environment Setup Guide

> STM32 Nucleo-F401RE Development Environment · [Back to README](../../README.md)

---

## Required Software

| Tool | Purpose | Download |
|------|---------|----------|
| STM32CubeIDE | All-in-one IDE (CubeMX + GCC + GDB) | [st.com](https://www.st.com/en/development-tools/stm32cubeide.html) |
| ST-LINK Driver | USB driver for the Nucleo debugger | [st.com](https://www.st.com/en/development-tools/stsw-link009.html) |
| Serial Terminal | UART communication monitor | [PuTTY](https://www.putty.org) or [TeraTerm](https://github.com/TeraTermProject/teraterm/releases) |

---

## Step 1 — Install STM32CubeIDE

1. Download **STM32CubeIDE** (≥ 1.15) from [st.com](https://www.st.com/en/development-tools/stm32cubeide.html)
2. Run the installer with **administrator privileges**
3. Accept the license and choose the default installation directory
4. The installer includes: GCC toolchain, GDB, OpenOCD, and CubeMX integration

---

## Step 2 — Install STM32Cube F4 Firmware Package

1. Open **STM32CubeIDE**
2. Go to **Help → Manage Embedded Software Packages**
3. Select **STMicroelectronics** → **STM32F4** → install version **≥ 1.28.0**

---

## Step 3 — Install ST-LINK Driver

1. Download and install the **ST-LINK/V2 driver** from the link above
2. Connect the Nucleo board via USB
3. Verify in **Device Manager** → **Ports (COM & LPT)**: "STMicroelectronics STLink Virtual COM Port (COMx)"

---

## Step 4 — Create Your First Project (Blinky)

1. **File → New → STM32 Project**
2. Search for **NUCLEO-F401RE** → Select → Next
3. Enter a project name → Finish
4. CubeMX opens automatically
5. In the **Pinout & Configuration** tab:
   - PA5 → **GPIO_Output** (LED)
   - PC13 → **GPIO_Input** (Button)
6. In **Clock Configuration** → set HCLK to **84 MHz**
7. **Project → Generate Code** (or `Alt+K`)
8. In `main.c`, add to the `while(1)` loop:
   ```c
   HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
   HAL_Delay(500);
   ```
9. **Build** (`Ctrl+B`) → **Run** (green play button)

---

## Step 5 — Setup Wokwi (Simulation)

1. Visit [wokwi.com](https://wokwi.com) — no installation needed
2. Select **New Project → STM32**
3. Upload your compiled `.elf` or `.hex` binary
4. Add components (LEDs, buttons, servos) in the `diagram.json` editor
5. Press **Play ▶** to simulate

> 💡 Tip: Use the Wokwi VS Code extension for a tighter IDE integration.

---

## Step 6 — Setup Serial Terminal

### PuTTY

1. Open **Device Manager** → find the COM port number (e.g., COM5)
2. Open PuTTY → **Connection type: Serial**
3. Set:
   - **Serial line**: COM5 (your port)
   - **Speed**: 115200
4. Click **Open**

### VS Code Serial Monitor Extension

1. Install **Serial Monitor** extension
2. Select port and set baud rate to **115200**
3. Click **Start Monitoring**

---

## Mbed OS Setup (Optional)

Used in [Potentiometer_Servo_STM32_F401RE](https://github.com/duongvanhoawork-lang/-STM32-Nucleo-F401RE-Laboratory/tree/main/Potentiometer_Servo_STM32_F401RE).

1. Install [Mbed Studio](https://os.mbed.com/studio/)
2. Sign in with an Mbed account (free)
3. **File → New Program** → Select **NUCLEO-F401RE**
4. Choose **mbed-os-example-blinky** as template
5. Build and flash via USB drag-and-drop or Mbed CLI

---

## Troubleshooting

| Problem | Fix |
|---------|-----|
| Board not detected | Reinstall ST-LINK driver; try different USB cable |
| Build fails on first project | Check STM32F4 firmware package is installed |
| Upload fails: "No target connected" | Verify ST-LINK is not in use by another app |
| UART not showing in Device Manager | Install ST-LINK VCP driver separately |
