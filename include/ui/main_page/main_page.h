#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include "ui/altimeter_ui.h"
#include "ui/main_page/measure_items.h"

#define NUM_MEASURES 4

class MainPage: public PageCanvas
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
            PageCanvas(disp, sett), data_column_x(disp.getWidth()/2 - 10)
        {};
        void dataUpdate(AltimeterData &d);
        void redraw();
        void update();
        void onClick() override;
        void onScroll(int direction) override;
    private:
        const int data_column_x;
        const int x_padding = 10;
        const int y_padding = 10;
        const int row_height = 10;
        const int textsize_large = 3;
        const int textsize_small = 1;

        const uint8_t numMeasures = NUM_MEASURES;
        MeasureItem *measures[NUM_MEASURES] = {
            new AltitudeMeasure("Alt: "),
            new HeigthMeasure("Height: "),
            new TemperatureMeasure("Temp: "),
            new PressureMeasure("Press: ")
        };

        uint16_t currentItem = 0; // 0=altitude, 1=height, 2=temperature, 3=pressure
        void compactPageUpdate();
        void compactPageRedraw();
        void extendedPageUpdate();
        void extendedPageRedraw();
};

#endif