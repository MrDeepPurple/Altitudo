#include "ui/page_controller.h"


PageController::PageController(DisplayWrapper &disp, AltimeterSettings &sett) : display(disp), settings(sett)
{
    buttonActionExecuted = false;

    pages = {
        {PageType::PAGE_MAIN, new MainPage(display, settings)},
        {PageType::PAGE_MENU, new MenuOptionPage(display, settings)},
        {PageType::PAGE_SPLASH, new SplashPage(display, settings)}
    };
}

void PageController::init()
{
    for (auto& pair : pages) {
        pair.second->registerChangePageCallback([this](PageType to) {this->changePage(to);});
    }
}

void PageController::ShowSplash()
{
    changePage(PageType::PAGE_SPLASH);
}

void PageController::changePage(PageType to)
{
    currentPage = pages[to];
    currentPage->redraw();
}

void PageController::eventHandler(int encoderSteps, bool buttonPressed)
{
    // encoderSteps: positive for clockwise, negative for counter-clockwise
    // number of steps since last execution of the event handler

    if (encoderSteps != 0) {
        currentPage->onScroll(encoderSteps);
    }
    // buttonPressed: true if button is pressed. Execute action only once per press
    if (buttonPressed) {
        if (!buttonActionExecuted) {
            currentPage->onClick();
            buttonActionExecuted = true;
        }
    } else {
        buttonActionExecuted = false;
    }
}

void PageController::dataUpdate(AltimeterData &data)
{
    if (currentPage) {
        currentPage->dataUpdate(data);
        currentPage->update();
    }
}
