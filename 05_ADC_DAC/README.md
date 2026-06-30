# 📊 ADC & DAC: Analog-to-Digital / Digital-to-Analog

## 📝 Overview
This section focuses on reading analog signals (ADC) and generating analog voltages (DAC, though STM32F401RE does not have an internal DAC, PWM + Low Pass Filter can be used as an alternative).

## 📂 Directory Structure
- `main.cpp`: Mbed OS code reading a potentiometer (ADC) and mapping the value to control an LED's brightness (PWM).
- `download.gif`: Demonstration of the potentiometer controlling the LED.

## 🎯 Learning Objectives
- Configure the ADC for single or continuous conversion.
- Read analog voltages from sensors (e.g., potentiometers, light sensors).
- Map ADC values (0-4095) to other ranges (e.g., PWM duty cycle, physical units).
