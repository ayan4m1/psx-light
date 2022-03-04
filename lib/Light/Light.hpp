#include <Arduino.h>
#include <FastLED.h>

#ifndef LIGHT_H
#define LIGHT_H

#define PIN_COUNT 4
#define PIN_TRI D5
#define PIN_CIR D6
#define PIN_CRS D7
#define PIN_SQR D8

#define LIGHT_ARRAY \
  { Light(PIN_TRI), Light(PIN_CIR), Light(PIN_CRS), Light(PIN_SQR) }

struct Light {
  Light(uint8_t pin);

  uint8_t pin;
  bool enabled;
  bool strobe;
  bool strobeDirection;
  uint8_t brightness;
};

class LightManager {
  static Light lights[PIN_COUNT];

 public:
  void init();
  void loop();
  void setState(uint8_t index, bool state);
  bool getState(uint8_t index);
  void setAllState(bool state);
  void setStrobe(uint8_t index, bool strobe);
  bool getStrobe(uint8_t index);
  void setAllStrobe(bool strobe);
  void setBrightness(uint8_t index, uint8_t brightness);
  uint8_t getBrightness(uint8_t index);
  void setAllBrightness(uint8_t brightness);
};

#endif
