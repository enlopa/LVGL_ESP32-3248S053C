# Example Code for ESP-323248S035C Capacitive Touch Screens

This repository contains example code demonstrating how to use ESP-323248S035C capacitive touch screens. These screens feature the ST7796 driver for the display and the GT911 driver for touch functionality. The example program is built with LVGL, a powerful and open-source graphics library.

## Features

- **Display Driver**: ST7796
- **Touch Driver**: GT911
- **Graphics Library**: LVGL
- Implements a simple UI with a single button.
- Button functionality: When pressed, the button's label changes.

## Requirements

- ESP32 development board.
- ESP-323248S035C touch screen module.
- LVGL library integrated into your development environment.
- Properly configured drivers for ST7796 and GT911.

## Setup and Usage

1. **Hardware Connections**:
   - Ensure your ESP32 is connected to the ESP-323248S035C module according to the pinout specified by the manufacturer.
   - Double-check power and ground connections.

2. **Software Configuration**:
   - Install the [LVGL library](https://lvgl.io/) in your development environment.
   - Ensure the ST7796 and GT911 drivers are included and properly configured.
   - Clone this repository and upload the code to your ESP32.

3. **Running the Example**:
   - After powering up the device, you should see a button displayed on the screen.
   - When you touch the button, its label will change.

## How It Works

The program initializes the display and touch drivers and sets up a basic UI using LVGL. A button widget is created, and an event handler is attached to it. When the button is pressed, the event handler updates the button's label to a new text string.

This example demonstrates how to:

- Configure and use the ST7796 and GT911 drivers.
- Build a basic UI with LVGL.
- Handle touch events in a simple and interactive way.

## Getting Started with LVGL

If you are new to LVGL, visit the [LVGL documentation](https://docs.lvgl.io/) to learn more about its setup and usage. Ensure that your environment is correctly configured to use LVGL with ESP32.

## License

This code is released under the MIT License. Feel free to use, modify, and distribute it.

---

For any questions or issues, feel free to open an issue in this repository or reach out to the contributors.

