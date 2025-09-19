#ifndef MECHMACRO_H
#define MECHMACRO_H

#include <Arduino.h>
#include <Keyboard.h>

// General Constants
#define HAPTIC_FEEDBACK_PIN 5
#define RELEASE_DELAY_MS 50
#define CLICKER_MODE_INTERVAL_MS 1000
#define DEBOUNCE_DELAY_MS 150
#define MACRO_COUNT 15
#define BUTTON_COUNT 6

enum OperatingSystem { WINDOWS = 0, MAC = 1 };
enum MenuMode { CLICKER_MODE = 0, COMMONS_MODE = 1, CODING_MODE = 2, MENU_COUNT = 3 };

struct Macro {
    const char* name;
    uint8_t winKeys[3];
    uint8_t macKeys[3];
};

struct Menu {
    const char* name;
    MenuMode mode;
    const Macro* macros;
};

class MechMacro {
public:
    MechMacro(OperatingSystem selectedOS);
    void handleButtonPress(int analogValue);
    void updateClickerMode();
    const char* getCurrentMenuName();

private:
    OperatingSystem currentOS;
    MenuMode currentMode;
    unsigned long lastButtonPressTime;

    void executeMacro(int buttonIndex);
    void switchMacroSet();
    void provideHapticFeedback(int durationMs);
    int getButtonIndex(int analogValue);
};

#endif // MECHMACRO_H