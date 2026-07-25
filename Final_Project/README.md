# 🏁 Final Project: Bluetooth Line Follower Car

## 📝 Overview
This directory contains the final coursework project for the STM32 Embedded Systems laboratory: a Bluetooth-controlled Line Follower Car. The project integrates multiple peripherals (GPIO, PWM, UART, ADC) and control logic to build a functional robotic vehicle.

## 📂 Directory Structure
- `bluetooth-line-follower-car/`: The core project folder containing the implementation.
  - `main.cpp`: Main source code.
  - `Overview.pdf`: Project overview and specifications.
  - `Project_slides.pdf`: Presentation slides for the final project.

## 🎯 Project Features
- **Line Tracking**: Uses IR sensors and ADC/GPIO to detect and follow a path.
- **Remote Control**: Bluetooth module integration via UART to allow manual override or mode switching.
- **Motor Control**: PWM signals to control motor speed and steering via motor drivers (e.g., L298N).
- **System Integration**: Combines multiple microcontroller peripherals into a unified embedded system.
