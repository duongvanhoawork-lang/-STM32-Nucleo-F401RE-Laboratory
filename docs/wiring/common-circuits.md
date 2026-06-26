# Common Circuit Wiring Patterns

> [Back to README](../../README.md)

---

## LED with Current-Limiting Resistor

```
PA5 ──[330Ω]──[LED]── GND
```
- **Resistor**: 220Ω–1kΩ (330Ω is common)
- **LED Vf**: ~2V (red), ~3V (blue/white)
- **I_LED** = (3.3V − Vf) / R = (3.3 − 2.0) / 330Ω ≈ **4 mA** ✅

For **LD2**: already on-board with resistor — use PA5 directly.

---

## Push Button (Active Low, Pull-up)

```
VCC (3.3V)
     │
    [10kΩ]  ← optional (CubeMX internal pull-up = 40kΩ typical)
     │
PC13 ┤
     │
  [BTN]
     │
    GND
```
- Read `GPIO_PIN_RESET` = button pressed
- Enable internal pull-up in CubeMX to avoid external resistor

---

## RGB LED (Common Cathode)

```
PA6 ──[330Ω]── R ──┐
PA7 ──[330Ω]── G ──┤ → GND (common cathode)
PB6 ──[330Ω]── B ──┘
```
- HIGH = LED on
- Mix colors by toggling pins

---

## Potentiometer → ADC

```
3.3V ──┐
       │
     [POT 10kΩ]
       │ ← wiper → PA0 (A0 = ADC1_IN0)
     [POT 10kΩ]
       │
GND ───┘
```
- Output range: 0V – 3.3V → ADC reads 0–4095
- Add 100nF cap between PA0 and GND for noise filtering

---

## Servo Motor

```
STM32 PWM (e.g., PB10/D6) ──── Signal (Yellow/White)
VCC 5V ──────────────────────── VCC    (Red)
GND ─────────────────────────── GND    (Black/Brown)
```
- Servo **VCC = 5V** — use VBUS (USB) or external supply, NOT the 3.3V pin
- **PWM**: 50 Hz, 1–2 ms pulse width
- Common GND between STM32 and servo supply is **mandatory**

> ⚠️ Do NOT power the servo from the Nucleo 3.3V or 5V pins directly — it may draw too much current and reset the board.

---

## I2C Device (e.g., SSD1306 OLED)

```
PB8 (SCL) ──[4.7kΩ]── 3.3V
PB9 (SDA) ──[4.7kΩ]── 3.3V
                         │
                       OLED module (SCL, SDA, VCC=3.3V, GND)
```
- Pull-up resistors are **required** on both SCL and SDA
- Some breakout modules include on-board pull-ups (check before adding external ones)

---

## SPI Device (e.g., SSD1306 OLED 4-wire)

```
PB13 (SPI2_SCK)  ────── CLK
PB15 (SPI2_MOSI) ────── DIN/MOSI
PB14 (SPI2_MISO) ────── (unused for write-only devices)
PB12 (GPIO CS)   ────── CS
PA8  (GPIO DC)   ────── DC  ← data/command select
PA9  (GPIO RST)  ────── RST ← reset pin
VCC 3.3V         ────── VCC
GND              ────── GND
```

---

## UART-to-PC (External Module, if not using ST-LINK VCP)

```
STM32 TX (PA2) ────── RX of USB-UART module
STM32 RX (PA3) ────── TX of USB-UART module
GND            ────── GND of USB-UART module
```
> For the Nucleo board, the ST-LINK already provides the virtual COM port on USART2 (PA2/PA3) — no external module needed.

---

## DC Motor via L298N Driver

```
PB3 (PWM/D3) ──── IN1
PB4 (D4)     ──── IN2
PB10 (PWM/D6)──── ENA (enable, controls speed)

L298N VCC (12V) ── external supply
L298N 5V out   ── STM32 5V (optional, if powering from L298N)
L298N GND      ── STM32 GND (common GND!)
```
- IN1=HIGH, IN2=LOW → forward
- IN1=LOW, IN2=HIGH → reverse
- ENA PWM duty cycle → motor speed
