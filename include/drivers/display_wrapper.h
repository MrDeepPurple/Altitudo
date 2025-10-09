#ifndef DISPLAY_H
#define DISPLAY_H

#include <SPI.h>
#include "utils/hwconfig.h"
#if DISPLAY_TYPE == DT_GxEPD2
#include <GxEPD2_BW.h>  // https://github.com/ZinggJM/GxEPD2
#include <GxEPD2_3C.h>
#elif DISPLAY_TYPE == DT_SH1106
#include <SH1106.h>
#elif DISPLAY_TYPE == DT_SSD1306
#include <Adafruit_SSD1306.h>
#endif

/* NOTE:
Pins to avoid on an ESP32-S3 Supermini board:
GPIO  0 : Boot button
GPIO 48 : Onboard LED + RGB LED (pin sharing)
*/

class DisplayWrapper
{
    public:
        DisplayWrapper();
        ~DisplayWrapper();
        void init();
        void setTextSize(int textsize);
        void clear();
        void clearRect(int16_t x, int16_t y, int16_t w, int16_t h);
        void displayText(int16_t x, int16_t y, String text);
        void update();

        int16_t getHeight();
        int16_t getWidth();
    private:
        /* Define a display object according to display type */
        #if DISPLAY_TYPE == DT_GxEPD2
        #ifndef SCREEN_IS_RBW
        GxEPD2_BW<GxEPD2_290_BS, GxEPD2_290_BS::HEIGHT> *display;  // DEPG0290BS 128x296, SSD1680
        #else
        GxEPD2_3C<GxEPD2_290_C90c, GxEPD2_290_C90c::HEIGHT> *display; // GDEM029C90 128x296, SSD1680
        #endif
        #elif DISPLAY_TYPE == DT_SH1106
        SH1106 *display;
        #endif
};

#endif