#include "ui/error_page/error_page.h"

void ErrorPage::redraw() {
    display.clear();
    display.setTextSize(2);
    display.displayText(0, 0, "Error");
    display.setTextSize(1);
    display.displayText(0, 30, message);
    display.update();
}
