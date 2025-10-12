#ifndef ERROR_PAGE_H
#define ERROR_PAGE_H

#include "ui/altimeter_ui.h"

class ErrorPage: public PageCanvas
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
        ErrorPage(DisplayWrapper &disp, AltimeterSettings &sett) : PageCanvas(disp, sett) {};
        void redraw() override;
        void update() override {};
        void onClick() override {};
        void onScroll(int direction) override {};
        void dataUpdate(AltimeterData &data) override {};
        void setMessage(String msg) {
            message = msg;
        }
    private:
        String message;
};

#endif