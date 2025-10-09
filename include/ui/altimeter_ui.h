#ifndef ALTIMETER_UI_H
#define ALTIMETER_UI_H

#include <functional>

#include "settings.h"
#include "sensors/altimeter_data.h"
#include "drivers/display_wrapper.h"

class TablePage
{
    public:
        TablePage(DisplayWrapper &disp, AltimeterSettings &sett) : display(disp), settings(sett) {};
        virtual void redraw() {}
        virtual void update() {}
        virtual void onClick() {}
        virtual void onScroll(int direction) {}
        virtual void dataUpdate(AltimeterData &data) {}
        void registerChangePageCallback(std::function<void()> cb) {
            changePageCallback = cb;
        }
    protected:
        DisplayWrapper &display;
        AltimeterSettings &settings;
        std::function<void()> changePageCallback;
};

#endif // ALTIMETER_UI_H
