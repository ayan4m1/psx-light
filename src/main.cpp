#include <Arduino.h>
#include <Button2.h>

#include <Light.hpp>

#define PIN_SW1 D1

Button2 sw1;
LightManager lights;
uint8_t activeLight = 0;
bool toggle = true;

void click(Button2& btn) {
  lights.setBrightness(activeLight, 255);
  lights.setStrobe(activeLight, false);
  if (activeLight == 3) {
    activeLight = 0;
  } else {
    activeLight++;
  }
  lights.setStrobe(activeLight, true);
}

void doubleClick(Button2& btn) {
  lights.setState(activeLight, !lights.getState(activeLight));
}

void tripleClick(Button2& btn) {
  lights.setAllState(!toggle);
  toggle = !toggle;
}

void setup() {
  Serial.begin(115200);
  sw1.begin(PIN_SW1);
  sw1.setTapHandler(click);
  sw1.setDoubleClickHandler(doubleClick);
  sw1.setTripleClickHandler(tripleClick);

  lights.init();
  lights.setAllState(true);
}

void loop() {
  sw1.loop();
  lights.loop();
}
