#ifndef SPLASH_PAGE_H
#define SPLASH_PAGE_H

#include "ui/altimeter_ui.h"

class SplashPage: public TablePage
{
    /* Splash page 
    * +------------------------------+
    * |         Altimeter            |
    * |          v0.1.0              |
    * |       by Syncthread          |
    * |   https://syncthread.com     |
    * +------------------------------+
    */
    public:
        SplashPage(DisplayWrapper &disp, AltimeterSettings &sett) : TablePage(disp, sett) {};
        void redraw() override;
        void update() override;
        void onClick() override;
        void onScroll(int direction) override;
        void dataUpdate(AltimeterData &data) override;
};

#endif
