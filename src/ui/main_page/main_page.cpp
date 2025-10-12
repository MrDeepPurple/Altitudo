#include "ui/main_page/main_page.h"

/* Main page - Compact view
* +------------------------------+
* | Altitude:       |1234.5 m    |
* | Height:         |405.2  m    |
* | Temperature:    |23.4 C      |
* | Pressure:       |1013.25 hPa |
* +------------------------------+
*
* Main page - Standard view
* +------------------------------+
* | Altitude:                    |
* |          1234.56             |
* |                   m          |
* +------------------------------+
*
* Interactions:
*  click: go to menu page
*  scroll:
*  - in compact mode: no action
*  - in standard mode: navigate between measures
*/

void MainPage::dataUpdate(AltimeterData &d)
{
    for (int i = 0; i < numMeasures; i++)
    {
        measures[i]->update(d, settings);
    }
}

void MainPage::compactPageUpdate()
{
    //clear column
    display.clearRect(data_column_x, 0, display.getWidth() - data_column_x, display.getHeight());

    for (int i = 0; i < numMeasures; i++)
    {
        display.displayText(data_column_x, y_padding + i * row_height, measures[i]->getValue() + " " + measures[i]->getUnit());
    }
}

void MainPage::compactPageRedraw()
{
    for (int i = 0; i < numMeasures; i++)
    {
        display.displayText(x_padding, y_padding + i * row_height, measures[i]->name);
    }
}

void MainPage::extendedPageUpdate()
{
    display.clear();
    display.setTextSize(1);
    display.displayText(x_padding, y_padding, measures[currentItem]->name);
    display.setTextSize(textsize_large);
    display.displayText(x_padding, y_padding + 20, measures[currentItem]->getValue());
    display.setTextSize(1);
    display.displayText(display.getWidth() - (x_padding + row_height), display.getHeight() - y_padding, measures[currentItem]->getUnit());
}

void MainPage::extendedPageRedraw()
{
    // In this case there are no differences between redraw and update
    extendedPageUpdate();
}

void MainPage::update()
{
    if(settings.uiMode == COMPACT)
        compactPageUpdate();
    else
        extendedPageUpdate();

    display.update();
}

void MainPage::redraw()
{
    /* display all the page */
    display.clear();
    
    if(settings.uiMode == COMPACT)
        compactPageRedraw();
    else
        extendedPageRedraw();

    /* draw variable data */
    update();
}

void MainPage::onClick()
{
    if (changePage) changePage(PageType::PAGE_MENU);
}

void MainPage::onScroll(int direction)
{
    if (settings.uiMode == STANDARD)
    {
        if(direction > 0)
            currentItem = (currentItem + 1) % 4;
        else
            if (currentItem == 0)
                currentItem = 3;
            else
                currentItem = (currentItem - 1) % 4;
    }
}