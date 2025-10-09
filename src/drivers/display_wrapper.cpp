#include "drivers/display_wrapper.h"

DisplayWrapper::DisplayWrapper()
{
    #if DISPLAY_TYPE == DT_GxEPD2
    #ifndef SCREEN_IS_RBW
    display = new GxEPD2_BW<GxEPD2_290_BS, GxEPD2_290_BS::HEIGHT>(GxEPD2_290_BS(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY));  // DEPG0290BS 128x296, SSD1680
    #else
    display = GxEPD2_3C<GxEPD2_290_C90c, GxEPD2_290_C90c::HEIGHT>(GxEPD2_290_C90c(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY)); // GDEM029C90 128x296, SSD1680
    #endif
    #else
    display = new SH1106();
    #endif
}

DisplayWrapper::~DisplayWrapper()
{
    delete display;
}

void DisplayWrapper::init()
{
    #if DISPLAY_TYPE == DT_GxEPD2
    display->init(115200, true, 50, false);
    display->setRotation(1);                     // Use 1 or 3 for landscape modes
    display->setTextColor(GxEPD_BLACK);
    display->setTextSize(2);
    display->setFullWindow();
    display->fillScreen(GxEPD_WHITE);
    display->setFullWindow();
    #else
    display->begin();
    clear();
    setTextSize(1);
    // Clear the buffer.
    #endif
}

void DisplayWrapper::setTextSize(int textsize)
{
    display->setTextSize(textsize);
}

void DisplayWrapper::displayText(int16_t x, int16_t y, String text)
{
    #if DISPLAY_TYPE == DT_SH1106
    display->setTextColor(WHITE);
    #endif
    display->setCursor(x, y);
    display->print(text);
}

void DisplayWrapper::clearRect(int16_t x, int16_t y, int16_t w, int16_t h)
{
    #if DISPLAY_TYPE == DT_GxEPD2
    display->fillRect(x, y, w, h, GxEPD_WHITE);
    #else
    display->fillRect(x, y, w, h, BLACK);
    #endif
}

void DisplayWrapper::clear()
{
    #if DISPLAY_TYPE == DT_GxEPD2
    display->fillScreen(GxEPD_WHITE);
    display->setFullWindow();
    #else
    // Clear the buffer.
    display->clearDisplay();
    #endif
}

void DisplayWrapper::update()
{
    #if DISPLAY_TYPE == DT_GxEPD2
    display->display(true); // partial update
    display->hibernate();
    #else
    display->display();
    #endif
}

int16_t DisplayWrapper::getHeight()
{
    return display->height();
}

int16_t DisplayWrapper::getWidth()
{
    return display->width();
}