# Project Title

## Description

This repository contains a comprehensive collection of embedded systems projects, including a specific project that logs or displays data using EUSART. The projects are structured into two main layers:

- **MCAL Layer**: This includes drivers for:
  - GPIO
  - ADC
  - I2C
  - SPI
  - EUSART
  - CCP
  - Timers (0, 1, 2, 3)
  - EEPROM
  - Interrupts

- **ECU Layer**: This consists of:
  - LED
  - Relay
  - DC Motors
  - Buttons
  - 7-Segment Display
  - LCD
  - Keypad

The MCAL and ECU layers provide a modular approach to embedded system design, facilitating easier integration and management of different components.

## Final Project: Data Logging and Monitoring System

This project showcases a comprehensive data logging and monitoring system, integrating various components for effective functionality. Below are the key features and components:

### Features

- **Real-Time Clock (RTC)**:
  - Accurate timekeeping for timestamping logged data.
  - Utilizes I2C communication for interfacing.

- **Temperature Monitoring**:
  - Measures ambient temperature using a temperature sensor.
  - Data is logged and displayed in real-time.

- **External EEPROM Storage**:
  - Stores logged data for long-term retention.
  - I2C communication is used for reading/writing data.

- **EUSART Communication**:
  - Enables data transmission for logging or displaying purposes.
  - Facilitates communication with a host device for data retrieval.

### Components Used

- **Microcontroller**: PIC18F4620
- **RTC Module**: (e.g., DS3231)
- **Temperature Sensor**: (e.g., LM35)
- **EEPROM**: (e.g., 24LC256)
- **Development Environment**: MPLAB X IDE with XC8 Compiler

### Project Structure

- **MCAL Layer**: Drivers for basic functionalities including:
  - GPIO
  - ADC
  - I2C
  - SPI
  - EUSART
  - CCP
  - Timers (0, 1, 2, 3)
  - EEPROM
  - Interrupts

- **ECU Layer**: High-level control for:
  - LED indicators
  - Relay control for devices
  - DC motor operation
  - User input via buttons and keypad
  - Display output on 7-segment displays and LCDs

Contributions
Contributions to improve the code and documentation are welcome! Please adhere to the project's contribution guidelines.

Acknowledgments
This project incorporates concepts and implementations learned during my embedded systems diploma,
with inspiration and partial code derived from other repositories. Special thanks to https://github.com/MasameEh/PIC18F4620_Drivers/ for their contributions to the community.


