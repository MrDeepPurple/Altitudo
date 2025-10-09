#include "ui/page_controller.h"


PageController::PageController(DisplayWrapper &disp, AltimeterSettings &sett) : display(disp), settings(sett)
{
    buttonActionExecuted = false;
}

void PageController::init()
{
    splashPage = new SplashPage(display, settings);
    mainPage = new MainPage(display, settings);
    mainPage->registerChangePageCallback([this]() {this->switchToMenuPage();});
    menuOptionPage = new MenuOptionPage(display, settings);
    menuOptionPage->registerChangePageCallback([this]() {this->switchToMainPage();});
}

void PageController::ShowSplash()
{
    display.clear();
    currentPage = splashPage;
    currentPage->redraw();
}

void PageController::HideSplash()
{
    switchToMainPage();
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

void PageController::switchToMainPage()
{
    display.clear();
    currentPage = mainPage;
    currentPage->redraw();
}

void PageController::switchToMenuPage()
{
    display.clear();
    currentPage = menuOptionPage;
    currentPage->redraw();
}
