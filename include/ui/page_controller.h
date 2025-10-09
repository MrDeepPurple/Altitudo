#ifndef PAGE_CONTROLLER_H
#define PAGE_CONTROLLER_H

#include "altimeter_ui.h"
#include "ui/main_page/main_page.h"
#include "ui/menu_page/menu_page.h"
#include "ui/splash_page/splash_page.h"
#include "drivers/display_wrapper.h"
#include "sensors/altimeter_data.h"

class PageController
{
    public:
        PageController(DisplayWrapper &disp, AltimeterSettings &sett);
        void init();
        void eventHandler(int encoderSteps, bool buttonPressed); // Handle events and delegate to current page
        void ShowSplash();
        void HideSplash();
        void dataUpdate(AltimeterData &data); // Update data on the current page
        void switchToMainPage();
        void switchToMenuPage();
    protected:
        DisplayWrapper &display;
        AltimeterSettings &settings;

        TablePage *currentPage;
        MainPage *mainPage;
        MenuOptionPage *menuOptionPage;
        SplashPage *splashPage;

        /* event functions */
        bool buttonActionExecuted;
};


#endif // PAGE_CONTROLLER_H