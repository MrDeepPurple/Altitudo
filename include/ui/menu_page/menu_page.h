#ifndef MENU_PAGE_H
#define MENU_PAGE_H

#include "ui/altimeter_ui.h"
#include "ui/menu_page/menu_options.h"

class MenuOptionPage: public TablePage
{
    /* Menu page
    * +---------------------------------------------------+
    * |  | 1. Calibrate QNH                  | QNE/custom |
    * |  | 2. Set QFE to current pressure    |            |
    * |->| 3. Display Height unit            | m/ft       |
    * |  | 4. Temperature unit               | C/F        |
    * |  | 5. Pressure unit                  | hPa/inHg   |
    * |  | 6. Back to main page              |            |
    * +---------------------------------------------------+
    * 
    * the arrow represent a selection curson. When an option is
    * selected, the arrow changes to a E (as in Edit) and the
    * user can changhe the option value.
    * e.g.: changing display unit from m to ft
    * +---------------------------------------------------+
    * |  | 1. Calibrate QNH                  | QNE/custom |
    * |  | 2. Set QFE to current pressure    |            |
    * |E | 3. Display Height unit            | ft         |
    * |  | 4. Temperature unit               | C/F        |
    * |  | 5. Pressure unit                  | hPa/inHg   |
    * |  | 6. Back to main page              |            |
    * +---------------------------------------------------+
    */
    private:
        const uint8_t numberOfOptions = 6;
        MenuOption *options[6] = {
            new setQNHOption(),
            new SetQFEOption(),
            new HeightUnitOption(),
            new TemperatureUnitOption(),
            new PressureUnitOption(),
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