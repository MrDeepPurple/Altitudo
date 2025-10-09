#ifndef MENU_OPTIONS_H
#define MENU_OPTIONS_H

#include <stdio.h>
#include "sensors/altimeter_data.h"

class MenuOption
{
    public:
        MenuOption(const char* name) : name(name) {}
        const char* getName() const { return name; }
        void registerCallbacks(void (*btnCb)(), void (*scrCb)(int)) {
            buttonCallback = btnCb;
            scrollCallback = scrCb;
        }
        virtual int getOptionValue() {return 0;}
        virtual const char* getOptionText() {return "";}
        virtual bool isEditable() {return false;}
        bool hasChanged() {
            bool ret = changed;
            changed = false;
            return ret;
        }
        void clicked(AltimeterSettings &settings) {
            changed = true;
            clicked_internal(settings);
            if (buttonCallback != nullptr) {
                buttonCallback();
            }
        }
        void scroll(int direction) {
            changed = true;
            scroll_internal(direction);
            if (scrollCallback != nullptr) {
                scrollCallback(direction);
            }
        }
        virtual void dataUpdate(AltimeterData &data);
    private:
        const char* name;
    protected:
        void (*buttonCallback)() = nullptr;
        void (*scrollCallback)(int) = nullptr;
        virtual void clicked_internal(AltimeterSettings &settings);
        virtual void scroll_internal(int steps);
        bool changed;
};

class SetQFEOption : public MenuOption
{
    public:
        SetQFEOption() : MenuOption("Calibrate QFE") {}
        bool isEditable() override { return false; }
        void dataUpdate(AltimeterData &data) override;
    private:
        float qfeValue = SEA_LEVEL_PRESSURE_HPA; // Default QFE value in hPa
        // No additional members needed
    protected:
        void clicked_internal(AltimeterSettings &settings) override;
        void scroll_internal(int steps) override {}
};

class setQNHOption : public MenuOption
{
    public:
        setQNHOption() : MenuOption("Calibrate QNH") {}
        bool isEditable() override { return true; }
        const char* getOptionText() override;
        int getOptionValue() override;
        void dataUpdate(AltimeterData &data) override {}
    private:
        float qnhValue = SEA_LEVEL_PRESSURE_HPA; // Default QNH value in hPa
        // No additional members needed
        void clicked_internal(AltimeterSettings &settings) override;
        void scroll_internal(int steps) override;
};

class HeightUnitOption : public MenuOption
{
    public:
        HeightUnitOption() : MenuOption("Altitude unit") {}
        bool isEditable() override { return true; }
        const char* getOptionText() override;
        int getOptionValue() override;
        void dataUpdate(AltimeterData &data) override {};
    private:
        HeightUnit currentUnit = METERS;
        void clicked_internal(AltimeterSettings &settings) override;
        void scroll_internal(int direction) override;
};

class TemperatureUnitOption : public MenuOption
{
    public:
        TemperatureUnitOption() : MenuOption("Temperature unit") {}
        bool isEditable() override { return true; }
        const char* getOptionText() override;
        int getOptionValue() override;
        void dataUpdate(AltimeterData &data) override {};
    private:
        TemperatureUnit currentUnit = CELSIUS;
        void clicked_internal(AltimeterSettings &settings) override;
        void scroll_internal(int direction) override;
};

class PressureUnitOption : public MenuOption
{
    public:
        PressureUnitOption() : MenuOption("Pressure unit") {}
        bool isEditable() override { return true; }
        const char* getOptionText() override;
        int getOptionValue() override;
        void dataUpdate(AltimeterData &data) override {};
    private:
        PressureUnit currentUnit = HPA;
        void clicked_internal(AltimeterSettings &settings) override;
        void scroll_internal(int direction) override;
};

class UIModeOption : public MenuOption
{
    public:
        UIModeOption() : MenuOption("UI Mode") {}
        bool isEditable() override { return true; }
        const char* getOptionText() override;
        int getOptionValue() override;
        void dataUpdate(AltimeterData &data) override {};
    private:
        UIMode mode = COMPACT;
        void clicked_internal(AltimeterSettings &settings) override;
        void scroll_internal(int direction) override;
};

class ResetOption : public MenuOption
{
    public:
        ResetOption() : MenuOption("Reset SPS") {}
        bool isEditable() override { return false; }
        void dataUpdate(AltimeterData &data) override {};
    private:
        // No additional members needed
        void clicked_internal(AltimeterSettings &settings) override;
        void scroll_internal(int direction) override {}
};

class BackToMainOption : public MenuOption
{
    public:
        BackToMainOption() : MenuOption("Back") {}
        bool isEditable() override { return false; }
        void dataUpdate(AltimeterData &data) override {};
    private:
        // No additional members needed
        void clicked_internal(AltimeterSettings &settings) override {};
        void scroll_internal(int direction) override {}
};

#endif // MENU_OPTIONS_H
