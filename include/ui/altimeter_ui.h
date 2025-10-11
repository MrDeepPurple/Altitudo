#ifndef ALTIMETER_UI_H
#define ALTIMETER_UI_H

#include <functional>

#include "settings.h"
#include "sensors/altimeter_data.h"
#include "drivers/display_wrapper.h"

enum class PageType {
    PAGE_MAIN,
    PAGE_MENU,
    PAGE_SPLASH
};

class PageCanvas
{
    public:
        PageCanvas(DisplayWrapper &disp, AltimeterSettings &sett) : display(disp), settings(sett) {};
        virtual void redraw() {}
        virtual void update() {}
        virtual void onClick() {}
        virtual void onScroll(int direction) {}
        virtual void dataUpdate(AltimeterData &data) {}
        void registerChangePageCallback(std::function<void(PageType)> cb) {
            changePageCallback = cb;
        }
    protected:
        DisplayWrapper &display;
        AltimeterSettings &settings;
        std::function<void(PageType)> changePageCallback;
};

#endif // ALTIMETER_UI_H
