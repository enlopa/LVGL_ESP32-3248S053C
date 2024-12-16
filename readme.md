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
- **PlatformIO Libraries**:
  - `TAMC_GT911`
  - `lvgl/lvgl@^9.2.2`
  - `TFT_eSPI`
- The `platformio.ini` file provided in this repository already includes the required libraries and configurations.

## Pin Configuration

- **TFT Display Pins**:
  - `TFT_MISO`: GPIO 12
  - `TFT_MOSI`: GPIO 13
  - `TFT_SLCK`: GPIO 14
  - `TFT_CS`: GPIO 15
  - `TFT_DC`: GPIO 2
  - `TFT_RST`: -1 (not used)
  - `TFT_BL`: GPIO 27

- **Touch Screen Pins (I2C)**:
  - `TOUCH_SDA`: GPIO 33
  - `TOUCH_SCL`: GPIO 32
  - `TOUCH_INT`: GPIO 21
  - `TOUCH_RST`: GPIO 25
  - `TOUCH_CS`: GPIO 33 (required by the `TFT_eSPI` library but not used as this is a capacitive touch screen, accessed via I2C).

### Pin Configuration File

The pin definitions must be configured in the `User_Setup.h` file located at the following path:

```
.pio\libdeps\esp32doit-devkit-v1\TFT_eSPI\User_Setup.h
```

An example configuration file, named `User_Setup.txt`, is provided in this repository. You can copy and rename it to `User_Setup.h` and place it in the specified directory. Ensure that the pin assignments match the ones listed above.

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

