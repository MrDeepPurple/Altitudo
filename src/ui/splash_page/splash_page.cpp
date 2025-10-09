#include "ui/splash_page/splash_page.h"

/* Splash page 
* +------------------------------+
* |       Altimeter              |
* |       v0.1.0                 |
* |       by Syncthread          |
* |                              |
* +------------------------------+
*
* Interactions:
*  - none -
*/
void SplashPage::redraw()
{
    display.clear();
    display.displayText(10, 20, "Altimeter");
    display.displayText(10, 30, "by Syncthread");
    display.displayText(10, 40, "v0.1.0");
    display.update();
}

void SplashPage::update()
{
    // no dynamic data to update
    return;
}

void SplashPage::onClick()
{
    // handled outside
    return;
}

void SplashPage::onScroll(int direction)
{
    // no action on scroll
    return;
}

void SplashPage::dataUpdate(AltimeterData &data)
{
    // no data to update
    return;
}


