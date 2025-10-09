#ifndef HWCONFIG_H
#define HWCONFIG_H

// hardware pins for rotary encoder
#define ENCODER_PIN_A D0
#define ENCODER_PIN_B D1
#define ENCODER_BUTTON_PIN D2

// display type definitions
#define DT_SH1106 0
#define DT_SSD1306 1
#define DT_GxEPD2 2

// display type selection. Chose only one
#define DISPLAY_TYPE DT_SH1106
// display-specific settings
#if DISPLAY_TYPE == DT_GxEPD2
// Connections for ESP32-S3 Supermini, trying to have most ADC pins left available
static const uint8_t EPD_BUSY = D0; // to EPD BUSY labled as 'TX' pin
static const uint8_t EPD_CS = D3;   // to EPD CS
static const uint8_t EPD_RST = D1;  // to EPD RST
static const uint8_t EPD_DC = D2;   // to EPD DC
//static const uint8_t EPD_SCK = 44;  // to EPD CLK labled as 'RX' pin
//static const uint8_t EPD_MISO = -1; // Master-In Slave-Out not used, as no data from display
//static const uint8_t EPD_MOSI = 10; // to EPD DIN / SDA
#define SCREEN_IS_RBW // enable if screen is Red Black White color
#define SCREEN_WIDTH 296
#define SCREEN_HEIGHT 128
#else
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#endif

// timing settings
/* duration of the splash screen. Default: 3s */
#define SPLASH_DURATION 3000
/* update interval of the screen. Default: 50ms */
#define SCREEN_UPDATE_INTERVAL 50
/* update interval of the barometer. Default: 10ms */
#define SENSOR_UPDATE_INTERVAL 10

// uncomment to enable debug output on serial
//#define EN_DEBUG
#define SERIAL_RATE 115200

#endif