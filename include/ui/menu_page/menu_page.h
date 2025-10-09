#ifndef MENU_PAGE_H
#define MENU_PAGE_H

#include "ui/altimeter_ui.h"
#include "ui/menu_page/menu_options.h"

#define MENU_OPTIONS 8

class MenuOptionPage: public TablePage
{
    /* Menu page
    * +---------------------------------------------------+
    * |  | 1. Calibrate QNH                  | QNE/custom |
    * |  | 2. Set QFE to current pressure    |            |
    * |->| 3. Display Height unit            |
    * |  | 4. Temperature unit               |
    * |  | 5. Reset SPS                      |
    * |  | 6. Back to main page              |
    * +--------------------------------------+
    * 
    */
    private:
        const uint8_t numberOfOptions = MENU_OPTIONS;
        MenuOption *options[MENU_OPTIONS] = {
            new setQNHOption(),
            new SetQFEOption(),
            new HeightUnitOption(),
            new TemperatureUnitOption(),
            new PressureUnitOption(),
            new UIModeOption(),
            new ResetOption(),
            new BackToMainOption()
        };
        uint8_t selectedOption;
        bool editMode;
        
        
        const uint16_t arrowXPos = 0;
        const uint16_t textxPos = 10;
        const uint16_t firstOptionYPos = 0;
        const uint16_t optionLineHeight = 10;
        const uint16_t optionsPerPage = 3;
        const uint16_t durationOKSplash = 500;

        bool ok_splash = false;
        uint16_t timer_ok_splash = 0;
        uint16_t page = 0;

        void drawOptionValue(int optionIndex);
        void redrawArrow(int oldpos, int newpos);
        void setEditMode(bool edit);
        void nextOption();
        void previousOption();
        
        void exitMenu();
    public:
        MenuOptionPage(DisplayWrapper &disp, AltimeterSettings &sett);
        void onClick();
        void onScroll(int direction);
        void redraw();
        void update();
        void dataUpdate(AltimeterData &data);
};

#endif