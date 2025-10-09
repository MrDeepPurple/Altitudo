#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>

inline void debug_begin()
{
    #ifdef EN_DEBUG
        Serial.begin(SERIAL_RATE);
    #endif
    return;
}

inline void debug_println(const char *txt)
{
    #ifdef EN_DEBUG
        Serial.println(txt);
    #endif
    return;
}

inline void debug_pinttext(const char *txt)
{
    #ifdef EN_DEBUG
        Serial.print(txt);
    #endif
    return;  
}

inline void debug_printint(int n)
{
    #ifdef EN_DEBUG
        Serial.print(n);
    #endif
    return;  
}

inline void debug_printfloat(double d)
{
    #ifdef EN_DEBUG
        Serial.print(d);
    #endif
    return;  
}

#endif