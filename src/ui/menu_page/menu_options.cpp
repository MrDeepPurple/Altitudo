#include "ui/menu_page/menu_options.h"

void SetQFEOption::clicked_internal(AltimeterSettings &settings)
{
    // TODO: this shall set QFE to current pressure reading
    settings.QFE = qfeValue; // Placeholder function
    settings.save();
}

void SetQFEOption::dataUpdate(AltimeterData &data)
{
    qfeValue = data.pressure; // Update QFE value with current pressure
    changed = true;
}

void setQNHOption::clicked_internal(AltimeterSettings &settings)
{
    // accept edit mode:
    settings.QNH = qnhValue; // Update the QNH setting
    settings.save();
}

void setQNHOption::scroll_internal(int direction)
{
    // Adjust QNH value based on scroll direction
    if (direction > 0) 
    {
        qnhValue += 0.25; // Increase QNH by 0.25 hPa
    } 
    else 
    {
        qnhValue -= 0.25; // Decrease QNH by 0.25 hPa
    }
}

const char* setQNHOption::getOptionText()
{
    static char buffer[16];
    snprintf(buffer, sizeof(buffer), "%.2f hPa", qnhValue);
    return buffer;
}

int setQNHOption::getOptionValue()
{
    return static_cast<int>(qnhValue * 100); // Return QNH in Pa for higher precision
}


void HeightUnitOption::clicked_internal(AltimeterSettings &settings)
{
    // accept edit mode:
    settings.heightUnit = currentUnit; // Update the height unit setting
    settings.save();
}

void HeightUnitOption::scroll_internal(int direction)
{
    // Toggle between METERS and FEET
    if (direction != 0) 
    {
        currentUnit = (currentUnit == METERS) ? FEET : METERS;
    }
}

const char* HeightUnitOption::getOptionText()
{
    return (currentUnit == METERS) ? "m" : "ft";
}

int HeightUnitOption::getOptionValue()
{
    return static_cast<int>(currentUnit);
}

void TemperatureUnitOption::clicked_internal(AltimeterSettings &settings)
{
    // accept edit mode:
    settings.temperatureUnit = currentUnit; // Update the temperature unit setting
    settings.save();
}

void TemperatureUnitOption::scroll_internal(int direction)
{
    // Toggle between CELSIUS and FAHRENHEIT
    if (direction != 0) 
    {
        currentUnit = (currentUnit == CELSIUS) ? FAHRENHEIT : CELSIUS;
    }
}

const char* TemperatureUnitOption::getOptionText()
{
    return (currentUnit == CELSIUS) ? "C" : "F";
}

int TemperatureUnitOption::getOptionValue()
{
    return static_cast<int>(currentUnit);
}

void PressureUnitOption::clicked_internal(AltimeterSettings &settings)
{
    // accept edit mode:
    settings.pressureUnit = currentUnit; // Update the pressure unit setting
    settings.save();
}

void PressureUnitOption::scroll_internal(int direction)
{
    // Toggle between HPA and INHG
    if (direction != 0) 
    {
        currentUnit = (currentUnit == HPA) ? INHG : HPA;
    }
}

const char* PressureUnitOption::getOptionText()
{
    return (currentUnit == HPA) ? "hPa" : "inHg";
}

int PressureUnitOption::getOptionValue()
{
    return static_cast<int>(currentUnit);
}

void BackToMainOption::clicked_internal(AltimeterSettings &settings)
{
    return;
}
