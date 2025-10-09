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

void MainPage::compactPageUpdate()
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
}

void MainPage::compactPageRedraw()
{
    display.displayText(10, 10, altitude_str);
    display.displayText(10, 20, height_str);
    display.displayText(10, 30, temperature_str );
    display.displayText(10, 40, pressure_str);
}

void MainPage::extendedPageUpdate()
{
    display.clear();
    display.setTextSize(1);
    display.displayText(10, 10, get_current_measure_name());
    display.setTextSize(textsize_large);
    display.displayText(10, 30, get_current_measure_value());
    display.setTextSize(1);
    display.displayText(std_unit_x, std_unit_y, get_current_measure_unit());

}

String MainPage::get_current_measure_name()
{
    switch (currentItem)
    {
        case 0:
            return altitude_str.c_str();
        case 1:
            return height_str.c_str();
        case 2:
            return temperature_str.c_str();
        case 3:
            return pressure_str.c_str();
        default:
            return "";
    }
}

String MainPage::get_current_measure_value()
{
    switch (currentItem) // altitude
    {
        case 0:
            if (currentAltitude < -999.99 || currentAltitude > 99999.99)
                return String("----");
            else if (settings.heightUnit == FEET)
                return String(currentAltitude * 3.28084, 1);
            else
                return String(currentAltitude, 1);
        case 1: // height
            if (currentHeight < -999.99 || currentHeight > 99999.99)
                return "----";
            else if (settings.heightUnit == FEET)
                return String(currentHeight * 3.28084, 1);
            else
                return String(currentHeight, 1);
        case 2: // temperature
            if (settings.temperatureUnit == FAHRENHEIT)
                return String((currentTemperature - 273.15) * 9.0 / 5.0 + 32.0, 1);
            else
                return String(currentTemperature - 273.15, 1);
            break;
        case 3: // pressure
            if (settings.pressureUnit == INHG)
                return String(currentPressure * 0.029529983071445, 1);
            else
                return String(currentPressure, 1);
            break;
        default:
            return "";
    }
}


String MainPage::get_current_measure_unit()
{
    switch (currentItem) // altitude
    {
        case 0:
        case 1:
            if (settings.heightUnit == FEET)
                return "ft";
            else
                return "m";
            
            break;
        case 2: // temperature
            if (settings.temperatureUnit == FAHRENHEIT)
                return "F";
            else    
                return "C";
            break;
        case 3: // pressure
            if (settings.pressureUnit == INHG)
                return "inHg";
            else
                return "hPa";
            break;
        default:
            return "";
    }    
}

void MainPage::extendedPageRedraw()
{
    // In this case there are no differences between redraw and update
    extendedPageUpdate();
}

void MainPage::update()
{
    if(settings.uiMode == COMPACT)
        compactPageUpdate();
    else
        extendedPageUpdate();

    display.update();
}

void MainPage::redraw()
{
    /* display all the page */
    display.clear();
    
    if(settings.uiMode == COMPACT)
        compactPageRedraw();
    else
        extendedPageRedraw();

    /* draw variable data */
    update();
}

void MainPage::onClick()
{
    if (changePageCallback) changePageCallback();
}

void MainPage::onScroll(int direction)
{
    if (settings.uiMode == STANDARD)
    {
        if(direction > 0)
            currentItem = (currentItem + 1) % 4;
        else
            if (currentItem == 0)
                currentItem = 3;
            else
                currentItem = (currentItem - 1) % 4;
    }

}