#include "Light.hpp"

// uint8_t LightManager::pinArray[PIN_COUNT] = PIN_ARRAY;
// bool LightManager::stateArray[PIN_COUNT] = {false, false, false, false};
// bool LightManager::strobeArray[PIN_COUNT] = {false, false, false, false};
// bool LightManager::strobeDirArray[PIN_COUNT] = {true, true, true, true};
// uint8_t LightManager::brightnessArray[PIN_COUNT] = {255, 255, 255, 255};

Light LightManager::lights[PIN_COUNT] = LIGHT_ARRAY;

void LightManager::init() {
  for (uint8_t i = 0; i < PIN_COUNT; i++) {
    pinMode(lights[i].pin, OUTPUT);
    digitalWrite(lights[i].pin, LOW);
  }
}

void LightManager::loop() {
  EVERY_N_MILLISECONDS(10) {
    for (uint8_t i = 0; i < PIN_COUNT; i++) {
      auto light = lights[i];

      if (!light.enabled) {
        digitalWrite(light.pin, LOW);
      } else {
        if (light.strobe) {
          if (light.brightness == 255 || light.brightness == 0) {
            light.strobeDirection = !light.strobeDirection;
          }

          if (light.strobeDirection) {
            light.brightness++;
          } else {
            light.brightness--;
          }
        }

        analogWrite(light.pin, light.brightness);
      }
    }
  }
}

void LightManager::setBrightness(uint8_t index, uint8_t brightness) {
  if (index < 0 || index > PIN_COUNT) {
    return;
  }

  lights[index].brightness = brightness;
}

void LightManager::setAllBrightness(uint8_t brightness) {
  for (uint8_t i = 0; i < PIN_COUNT; i++) {
    setBrightness(i, brightness);
  }
}

uint8_t LightManager::getBrightness(uint8_t index) {
  if (index < 0 || index > PIN_COUNT) {
    return;
  }

  return lights[index].brightness;
}

void LightManager::setState(uint8_t index, bool state) {
  if (index < 0 || index > PIN_COUNT) {
    return;
  }

  lights[index].enabled = state;
}

void LightManager::setAllState(bool state) {
  for (uint8_t i = 0; i < PIN_COUNT; i++) {
    setState(i, state);
  }
}

bool LightManager::getState(uint8_t index) {
  if (index < 0 || index > PIN_COUNT) {
    return;
  }

  return lights[index].enabled;
}

void LightManager::setStrobe(uint8_t index, bool strobe) {
  if (index < 0 || index > PIN_COUNT) {
    return;
  }

  lights[index].strobe = strobe;
}

void LightManager::setAllStrobe(bool strobe) {
  for (uint8_t i = 0; i < PIN_COUNT; i++) {
    setStrobe(i, strobe);
  }
}

bool LightManager::getStrobe(uint8_t index) {
  if (index < 0 || index > PIN_COUNT) {
    return;
  }

  return lights[index].strobe;
}
