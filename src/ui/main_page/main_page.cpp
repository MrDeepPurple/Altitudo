#include "ui/main_page/main_page.h"

/* Main page 
* +------------------------------+
* | Altitude:       |1234.5 m    |
* | Height:         |405.2  m    |
* | Temperature:    |23.4 C      |
* | Pressure:       |1013.25 hPa |
* +------------------------------+
*
* Interactions:
*  click: go to menu page
*  scroll: no action
*/
void MainPage::dataUpdate(AltimeterData &data)
{
    currentAltitude = data.altitude;
    currentHeight = data.height;
    currentTemperature = data.temperature;
    currentPressure = data.pressure;
}

void MainPage::update()
{
    //clear column
    display.clearRect(xcol, 10, 150, 100);

    /* display only the variable parts*/
    if (currentAltitude < -999.99 || currentAltitude > 99999.99)
        display.displayText(xcol, 10, "  ----  ");
    else if (settings.heightUnit == FEET)
        display.displayText(xcol, 10, String(currentAltitude * 3.28084, 1) + " ft");
    else
        display.displayText(xcol, 10, String(currentAltitude, 1) + " m");

    if (currentHeight < -999.99 || currentHeight > 99999.99)
        display.displayText(xcol, 20, "  ----  ");
    else if (settings.heightUnit == FEET)
        display.displayText(xcol, 20, String(currentHeight * 3.28084, 1) + " ft");
    else
        display.displayText(xcol, 20, String(currentHeight, 1) + " m");
    
    if (settings.temperatureUnit == FAHRENHEIT)
        display.displayText(xcol, 30, String((currentTemperature - 273.15) * 9.0 / 5.0 + 32.0, 1) + " F");
    else    
        display.displayText(xcol, 30, String(currentTemperature - 273.15, 1) + " C");
    
    if (settings.pressureUnit == INHG)
        display.displayText(xcol, 40, String(currentPressure * 0.029529983071445, 1) + " inHg");
    else
        display.displayText(xcol, 40, String(currentPressure, 1) + " hPa");

    display.update();
}

void MainPage::redraw()
{
    /* display all the page */
    display.clear();
    display.displayText(10, 10, altitude_str);
    display.displayText(10, 20, height_str);
    display.displayText(10, 30, temperature_str );
    display.displayText(10, 40, pressure_str);

    /* draw variable data */
    update();
}

void MainPage::onClick()
{
    if (changePageCallback) changePageCallback();
}

void MainPage::onScroll(int direction)
{
    // no action on scroll
    return;
}