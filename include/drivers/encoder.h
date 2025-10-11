#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>
// defining input pins. If not defined, fallback to D0, D1 and D2
#ifndef ENCODER_PIN_A
#define ENCODER_PIN_A D0
#endif
#ifndef ENCODER_PIN_B
#define ENCODER_PIN_B D1
#endif
#ifndef ENCODER_BUTTON_PIN
#define ENCODER_BUTTON_PIN D2
#endif

class Encoder
{
    public:
        Encoder(int pinA, int pinB, int btn);
        Encoder() : Encoder(ENCODER_PIN_A, ENCODER_PIN_B, ENCODER_BUTTON_PIN) {};
        int getSteps();
        bool isButtonPressed();
    protected:
        static Encoder* instance;
        static void encoderIntr();
        static void btnIntr();
    private:
        int pinA;
        int pinB;
        int btn;
        volatile int lastState;
        volatile int position;
        volatile int numclicks;
        volatile bool lastButtonState;
};

#endif