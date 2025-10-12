#include "ui/menu_page/menu_page.h"


/* Menu page
* +--------------------------------------+
* |  | 1. Calibrate QNH                  |
* |  | 2. Set QFE to current pressure    |
* |->| 3. Display Height unit            |
* |  | 4. Temperature unit               |
* |  | 5. Pressure unit                  |
* |  | 6. Back to main page              |
* +---------------------------------------------------+
* Interactions:
*  click: enter/exit edit mode or execute action
*  scroll: navigate options or change value in edit mode
*/

MenuOptionPage::MenuOptionPage(DisplayWrapper &disp, AltimeterSettings &sett)
        : PageCanvas(disp, sett), optionsPerPage((disp.getHeight() / optionLineHeight))
{
    selectedOption = 0;
    editMode = false;

    ok_splash = false;
    timer_ok_splash = 0;
    page = 0;
};

void MenuOptionPage::dataUpdate(AltimeterData &data)
{
    // route data update to all options
    for (int i = 0; i < numberOfOptions; i++)
    {
        options[i]->dataUpdate(data);
    }
}

void MenuOptionPage::redrawArrow(int oldpos, int newpos)
{
    //clear column
    display.clearRect(0, 0, 10, 64);
    display.displayText(arrowXPos, (newpos * optionLineHeight), "->");
}

void MenuOptionPage::setEditMode(bool edit)
{
    editMode = edit;
}

void MenuOptionPage::onClick()
{
    if(!editMode)
    {
        if(selectedOption == numberOfOptions - 1)
        {
            exitMenu();
            return;
        }
        // enter edit mode if current option is editable
        MenuOption* option = options[selectedOption];
        if(option->isEditable())
        {
            editMode = true;
            setEditMode(true);
        }
        else
        {
            // if not editable, trigger the click action and show
            // the OK splash screen
            ok_splash = true;
            timer_ok_splash = millis();
            option->clicked(settings);
        }
            
    }
    else
    {
        if(selectedOption == numberOfOptions - 1) // Back to main page
        {
            // handled outside
            exitMenu();
        }
        else
        {
            MenuOption* option = options[selectedOption];
            if(option->isEditable())
            {
                // exit edit mode
                editMode = false;
                setEditMode(false);
                option->clicked(settings);
            }
        }
    }
}

void MenuOptionPage::onScroll(int direction)
{
    if(!editMode)
    {
        if(direction > 0)
            selectedOption = (selectedOption + 1) % numberOfOptions;
        else
            if(selectedOption == 0)
                selectedOption = (numberOfOptions - 1);
            else
                selectedOption = (selectedOption - 1) % numberOfOptions;
    }
    else
    {
        MenuOption* option = options[selectedOption];
        option->scroll(direction);
    }
}

void MenuOptionPage::redraw()
{
    display.clear();

    if(ok_splash)
    {
        if ((millis() - timer_ok_splash) <  durationOKSplash)
        {
            display.displayText(display.getWidth() / 2 - 5, display.getHeight() / 2 - 5, "OK");
        }
        else
        {
            ok_splash = false;
        }
    }
    else if(editMode)
    {
        // draw option
        display.displayText(textxPos, optionLineHeight, options[selectedOption]->getName());
        display.displayText(textxPos, 2*optionLineHeight, options[selectedOption]->getOptionText());
    }
    else
    {
        int current_page = selectedOption / optionsPerPage;
        int local_opt_index = selectedOption - current_page * optionsPerPage;

        int opts_to_print = min(optionsPerPage, uint16_t(numberOfOptions - current_page * optionsPerPage));

        for (uint8_t i = 0; i < opts_to_print; i++)
        {
            int optionIndex = current_page * optionsPerPage + i;
            display.displayText(textxPos, (i * optionLineHeight), String(optionIndex + 1) + ". " + options[optionIndex]->getName());
        }

        redrawArrow(-1, local_opt_index);
    }

    display.update();
}

void MenuOptionPage::update()
{
    redraw();
}

void MenuOptionPage::exitMenu()
{
    if (changePage) changePage(PageType::PAGE_MAIN);
}
