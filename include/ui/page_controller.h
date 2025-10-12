#ifndef PAGE_CONTROLLER_H
#define PAGE_CONTROLLER_H

#include <map>

#include "ui/altimeter_ui.h"
#include "ui/main_page/main_page.h"
#include "ui/menu_page/menu_page.h"
#include "ui/splash_page/splash_page.h"
#include "ui/error_page/error_page.h"
#include "drivers/display_wrapper.h"
#include "sensors/altimeter_data.h"

class PageController
{
    public:
        PageController(DisplayWrapper &disp, AltimeterSettings &sett);
        void init();
        void eventHandler(int encoderSteps, bool buttonPressed); // Handle events and delegate to current page
        void ShowSplash();
        void dataUpdate(AltimeterData &data); // Update data on the current page
        void changePage(PageType to); // Change to a specific page
        void panic(String message); // Show error message and halt
    protected:
        DisplayWrapper &display;
        AltimeterSettings &settings;
        ErrorPage errorPage;
        
        PageCanvas *currentPage;

        std::map<PageType, PageCanvas*> pages;

        /* event functions */
        bool buttonActionExecuted;
};

#endif // PAGE_CONTROLLER_H