//
// Created by Ata Can Yaymacı on 1.04.2025.
//

#include "MechMacro.h"

MechMacro::MechMacro(int selectedOS, int motorPin) {
    this->motorPin = motorPin;
    this->currentOS = selectedOS % 2;
    pinMode(motorPin, OUTPUT);
    digitalWrite(motorPin, LOW);
}

void MechMacro::pressButton(int analogValue, int releaseDelay) {
    if (this->currentMenuIndex < 0) return;

    for (int i = 0; i < sizeof(buttonAnalogValues) / sizeof(buttonAnalogValues[0]); i++) {
        if (analogValue != buttonAnalogValues[i]) continue;

        Menu menu = menus[this->currentMenuIndex];
        Macro macro = menu.macros[this->currentMacroSetIndex];
        uint8_t* keys = this->currentOS == WINDOWS ? macro.winKeys : macro.macKeys;

        for (int j = 0; j < sizeof(keys) / sizeof(keys[0]); j++) {
            if (keys[j] == 0) continue;
            Keyboard.press(keys[j]);
        }

        // press delay
        delay(releaseDelay);
        Keyboard.releaseAll();
        return;
    }

    this->lastButtonIndex = -1;
}

void MechMacro::clickerMode() {
    if (this->currentMenuIndex == 0 && (millis() - now > CONTROL_TIME)) {
        now = millis();
        Keyboard.press(KEY_LEFT_GUI);
        delay(50);
        Keyboard.releaseAll();
    }
}

// private functions

void MechMacro::hapticFeedback(int value) {
    int motorPower = map(value, 0, 1023, 0, 255);
    analogWrite(motorPin, motorPower);
}

void MechMacro::cancelMenu() {
    this->currentMenuIndex = -1;
    this->currentMacroSetIndex = 0;
    this->lastButtonIndex = -1;
}

void MechMacro::nextMacroSet() {
    if (this->lastButtonIndex == sizeof(buttonAnalogValues) / sizeof(buttonAnalogValues[0]) - 1) {
        cancelMenu();
        return;
    }

    this->currentMacroSetIndex++;
    if (this->currentMacroSetIndex >= sizeof(menus) / sizeof(menus[0])) {
        this->currentMacroSetIndex = 0;
    }
}