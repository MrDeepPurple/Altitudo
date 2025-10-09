# Altitudo

**Altitudo** is an ESP32-based altimeter designed to be simple, compact but extensible. Current implementation has been developed with paramotor in mind, but it can be easily adapted to other outdoor activities.
It is based on the original [Altisense: Compact Altimeter Using ESP‑32](https://www.instructables.com/Altisense-Compact-Altimeter-Using-ESP32/) by Gokux, and extends its functionality with a modular codebase and support for multiple display types.

---

## Features

- **ESP32-S3 Supermini** support
- Modular driver architecture for multiple display types:
  - GxEPD2 (e-paper)
  - SH1106 (OLED)
  - SSD1306 (OLED)
- Simple UI
- Rotary encoder input support
- Easily extensible for new sensors and displays

---

## Getting Started

### Prerequisites

- ESP32 toolchain (Arduino IDE or PlatformIO)
- Required libraries (Install only the ones that suit your hardware):
  - [MS5611](https://github.com/RobTillaart/MS5611)
  - [GxEPD2](https://github.com/ZinggJM/GxEPD2)
  - [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
  - [SH1106](https://github.com/jakiki6/SH1106) (or compatible)
- A supported display
- A rotary encoder with integrated push button
- A supported barometer
  - MS5611
  - (Coming soon) BMP585

### Building

1. Clone this repository.
2. Configure your hardware in `include/utils/hwconfig.h` (set `DISPLAY_TYPE`, pin assignments, etc.).
3. Open the project in your preferred IDE.
4. Download required libraries
5. Build and upload to your ESP32 board.

---

## Credits

- Original concept by [Gokux](https://www.instructables.com/member/Gokux/)
- Libraries by ZinggJM, RobTillaart, adafruit, jakiki6, and others

---

## License

This project is open source and available under the MIT License.  
See [LICENSE](../LICENSE) for details.

---

## Status

**Under construction** — contributions and feedback are welcome!