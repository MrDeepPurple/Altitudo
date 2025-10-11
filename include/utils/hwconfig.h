#ifndef HWCONFIG_H
#define HWCONFIG_H

/*********************************
 * Input configuration
 *********************************/
/* hardware pins for rotary encoder */
#define ENCODER_PIN_A D0
#define ENCODER_PIN_B D1
#define ENCODER_BUTTON_PIN D2

/*********************************
 * Display configuration
 *********************************/
/* display type definitions */
#define DT_SH1106 0
#define DT_SSD1306 1
#define DT_GxEPD2 2

/* display type selection. Chose only one */
#define DISPLAY_TYPE DT_SH1106
/* display-specific settings */
#if DISPLAY_TYPE == DT_GxEPD2
    // Connections for ESP32-S3 Supermini, trying to have most ADC pins left available
    #define EPD_BUSY = D0   // to EPD BUSY labled as 'TX' pin
    #define EPD_CS = D3     // to EPD CS
    #define EPD_RST = D1    // to EPD RST
    #define EPD_DC = D2     // to EPD DC
    #define SCREEN_IS_RBW   // enable if screen is Red Black White color
    #define SCREEN_WIDTH 296
    #define SCREEN_HEIGHT 128
#else
    #define SCREEN_WIDTH 128
    #define SCREEN_HEIGHT 64
#endif

/*********************************
 * Sensor configuration
 *********************************/
/* Barometer settings */
#define BT_MS5611 0
#define BT_BMP585 1
/* select barometer type. */
#define BAROMETER_TYPE BT_MS5611
#if BAROMETER_TYPE == BT_MS5611
/* some MS5611 use different constants to compute pressure from registers.
* math mode 0 is the original MS5611 mode, math mode 1 is used by some clones.
* In general, math mode 0 should be the correct one. Set to 1 if barometer
* returns incorrect pressure values (roughly off by factor 2).
*/
    #define MATH_MODE 1 
#endif
/* Uncomment to use the more precise barometric formula for altitude calculation */
//#define USE_PRECISE_FORMULA
/* Enable or disable rolling average filtering. Note: Rolling average might not be needed
 * for BMP585, as it has built-in filtering enabled by default. 
 */
#define USE_ROLLING_AVG

/*********************************
 * Other settings
 *********************************/
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