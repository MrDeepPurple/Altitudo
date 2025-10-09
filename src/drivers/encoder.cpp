#include "drivers/encoder.h"

Encoder* Encoder::instance = nullptr;

Encoder::Encoder(int pinA, int pinB, int btn) : pinA(pinA), pinB(pinB), btn(btn), position(0) {
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    lastState = digitalRead(pinA);
    pinMode(btn, INPUT_PULLUP);
    lastButtonState = false;
    numclicks = 0;

    attachInterrupt(digitalPinToInterrupt(pinA), Encoder::encoderIntr, CHANGE);
    attachInterrupt(digitalPinToInterrupt(btn), Encoder::btnIntr, CHANGE);
    instance = this;
}

void Encoder::btnIntr()
{
    if (!instance) return;
    // button press action shall be executed only once
    // per each time isButtonPressed() is called.
    // NOTE: btn is in INPUT_PULLUP mode. This means that
    // by default it outputs high
    bool btnstate = (digitalRead(instance->btn) == LOW);

    if (btnstate)
    {
        if (!instance->lastButtonState) {
            instance->numclicks++;
        }
        instance->lastButtonState = true;
    } else {
        instance->lastButtonState = false;
    }
}

void Encoder::encoderIntr()
{
    if (!instance) return;
    int stateA = digitalRead(instance->pinA);
    int stateB = digitalRead(instance->pinB);
    if (stateA != instance->lastState) {
        if (stateB != stateA) {
            instance->position++;
        } else {
            instance->position--;
        }
    }
    instance->lastState = stateA;
}

int Encoder::getSteps() 
{
    int retpos = position;
    position = 0; // Reset position after reading
    return retpos;
}

bool Encoder::isButtonPressed() 
{
    int retbtn = numclicks > 0;
    numclicks = 0; // reset clicks after reading
    return retbtn;
}

