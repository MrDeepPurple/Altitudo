#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include "ui/altimeter_ui.h"

class MainPage: public TablePage
{
    /*NOTES:
     * QNH = Sea level pressure
     * QFE = Local ground pressure 
     * QNE = Standard pressure 1013.25 hPa
     */

    /* POSSIBLE EVOLUTION -> round diplay with heading*/

    /* Main page 
    * +------------------------------+
    * | Altitude:       |1234.56 m   |
    * | Height:         |405.25  m   |
    * | Temperature:    |23.4 C      |
    * | Pressure:       |1013.25 hPa |
    * +------------------------------+
    */
    public:
        MainPage(DisplayWrapper &disp, AltimeterSettings &sett) : 
            TablePage(disp, sett), xcol(disp.getWidth()/2 - 10), std_unit_x(disp.getWidth() - 30), std_unit_y(disp.getHeight() - 10)
        {
            currentAltitude = 0.0;
            currentTemperature = 0.0;
            currentPressure = 0.0;
        };
        void dataUpdate(AltimeterData &data);
        void redraw();
        void update();
        void onClick() override;
        void onScroll(int direction) override;
    private:
        const int xcol;
        const int textsize_large = 3;
        const int textsize_small = 1;
        const int std_unit_x;
        const int std_unit_y;
        String altitude_str = "Alt: ";
        String height_str = "Height: ";
        String temperature_str = "Temp: ";
        String pressure_str = "Press: ";
        float currentAltitude;
        float currentHeight;
        float currentTemperature;
        float currentPressure;
        uint16_t currentItem = 0; // 0=altitude, 1=height, 2=temperature, 3=pressure
        void compactPageUpdate();
        void compactPageRedraw();
        void extendedPageUpdate();
        void extendedPageRedraw();
        String get_current_measure_name();
        String get_current_measure_value();
        String get_current_measure_unit();
};

#endif