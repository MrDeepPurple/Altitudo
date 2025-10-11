#ifndef MEASURE_ITEMS_H
#define MEASURE_ITEMS_H

#include "sensors/altimeter_data.h"

class MeasureItem
{
    public:
        MeasureItem(String n) : name(n) {};
        const String name;
        virtual void update(AltimeterData &data, AltimeterSettings &sett) = 0;
        virtual String getValue() = 0;
        virtual String getUnit() = 0;
};

class AltitudeMeasure : public MeasureItem
{
    public:
        AltitudeMeasure(String n) : MeasureItem(n) {};
        void update(AltimeterData &data, AltimeterSettings &sett) override 
        {
            value = data.altitude;
            unit = sett.heightUnit;
        };
        String getValue() override
        {
            if (value < -999.99 || value > 99999.99)
                return String("  ----  ");
            else if (unit == FEET)
                return String(value * 3.28084, 1);
            else
                return String(value, 1);
        };
        String getUnit() override
        {
            if (unit == FEET)
                return "ft";
            else
                return "m";
        }
    protected:
        double value = 0.0;
        HeightUnit unit = METERS;
};

class HeigthMeasure: public AltitudeMeasure
{
    public:
        HeigthMeasure(String n) : AltitudeMeasure(n) {};
        void update(AltimeterData &data, AltimeterSettings &sett) override 
        {
            value = data.height;
            unit = sett.heightUnit;
        };
        String getValue() override
        {
            if (value < -999.99 || value > 99999.99)
                return String("  ----  ");
            else if (unit == FEET)
                return String(value * 3.28084, 1);
            else
                return String(value, 1);
        };
};

class TemperatureMeasure : public MeasureItem
{
    public:
        TemperatureMeasure(String n) : MeasureItem(n) {};
        void update(AltimeterData &data, AltimeterSettings &sett) override 
        {
            value = data.temperature;
            unit = sett.temperatureUnit;
        };
        String getValue() override
        {
            if (unit == FAHRENHEIT)
                return String((value - 273.15) * 9.0 / 5.0 + 32.0, 1);
            else
                return String(value - 273.15, 1);
        };
        String getUnit() override
        {
            if (unit == FAHRENHEIT)
                return "F";
            else    
                return "C";
        }
    protected:
        double value = 0.0;
        TemperatureUnit unit = CELSIUS;
};


class PressureMeasure : public MeasureItem
{
    public:
        PressureMeasure(String n) : MeasureItem(n) {};
        void update(AltimeterData &data, AltimeterSettings &sett) override 
        {
            value = data.pressure;
            unit = sett.pressureUnit;
        };
        String getValue() override
        {
            if (unit == INHG)
                return String(value * 0.029529983071445, 1);
            else
                return String(value, 1);
        };
        String getUnit() override
        {
            if (unit == INHG)
                return "inHg";
            else
                return "hPa";
        }
    protected:
        double value = 0.0;
        PressureUnit unit = HPA;
};

#endif