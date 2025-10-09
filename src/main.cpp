#include "main.h"

DisplayWrapper display;
Altimeter altimeter;
PageController *pageController;
Encoder encoder(ENCODER_PIN_A, ENCODER_PIN_B, ENCODER_BUTTON_PIN);

unsigned long screenUpdate = 0;
unsigned long sensorUpdate = 0;

void setup() {

  /* Debug is ignored if EN_DEBUG is not defined in hwconfig.h */
  debug_begin();

  display.init();
  pageController = new PageController(display, altimeter.getSettings());
  pageController->init();
  pageController->ShowSplash();
  uint64_t start = millis();

  altimeter.begin();
  
  // wait remaining time for splash screen
  delay(SPLASH_DURATION - (millis() - start));
  debug_println("Setup complete");

  /* hide splash page */
  pageController->HideSplash();

}

void loop() {
  // task 1: read sensor data at defined interval
  if (millis() - sensorUpdate >= SENSOR_UPDATE_INTERVAL) {
    sensorUpdate = millis();

    altimeter.read();
  }

  // task 2: update screen at defined interval
  if (millis() - screenUpdate >= SCREEN_UPDATE_INTERVAL) {
    screenUpdate = millis();

    pageController->eventHandler(encoder.getSteps(), encoder.isButtonPressed());
    pageController->dataUpdate(altimeter.getData());
  }
}

