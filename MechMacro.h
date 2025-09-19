//
// Created by Ata Can Yaymacı on 1.04.2025.
//
#include <Keyboard.h>

#ifndef MECHMENU_H
#define MECHMENU_H

#define CONTROL_TIME 1000

enum Mode {
    CLICKER = 0,
    COMMONS = 1,
    CODING = 2
};

enum OS {
    WINDOWS = 0,
    MAC = 1
};

struct Macro {
    const char* name;      // Macro name
    uint8_t winKeys[3];    // Windows/Linux
    uint8_t macKeys[3];    // Mac
};

struct Menu {
    const char* name;     // Menu name
    Mode mode;            // Mod
    const Macro* macros;  // Makro list
};

const Macro DEFAULT_MACROS[15] = {
    {"Copy", {KEY_LEFT_CTRL, 'C', 0}, {KEY_LEFT_GUI, 'C', 0}}, // 1
    {"Paste", {KEY_LEFT_CTRL, 'V', 0}, {KEY_LEFT_GUI, 'V', 0}}, // 2
    {"Cut", {KEY_LEFT_CTRL, 'X', 0}, {KEY_LEFT_GUI, 'X', 0}}, // 3
    {"Undo", {KEY_LEFT_CTRL, 'Z', 0}, {KEY_LEFT_GUI, 'Z', 0}}, // 4
    {"Redo", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'Z'}, {KEY_LEFT_GUI, KEY_LEFT_SHIFT, 'Z'}}, // 5
    {"Select All", {KEY_LEFT_CTRL, 'A', 0}, {KEY_LEFT_GUI, 'A', 0}}, // 6
    {"Find", {KEY_LEFT_CTRL, 'F', 0}, {KEY_LEFT_GUI, 'F', 0}}, // 7
    {"Replace", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'H'}, {KEY_LEFT_GUI, KEY_LEFT_SHIFT, 'H'}}, // 8
    {"New Tab", {KEY_LEFT_CTRL, 'T', 0}, {KEY_LEFT_GUI, 'T', 0}}, // 9
    {"Close Tab", {KEY_LEFT_CTRL, 'W', 0}, {KEY_LEFT_GUI, 'W', 0}}, // 10
    {"New Window", {KEY_LEFT_CTRL, 'N', 0}, {KEY_LEFT_GUI, 'N', 0}}, // 11
    {"Close Window", {KEY_LEFT_CTRL, 'Q', 0}, {KEY_LEFT_GUI, 'Q', 0}}, // 12
    {"Save", {KEY_LEFT_CTRL, 'S', 0}, {KEY_LEFT_GUI, 'S', 0}}, // 13
    {"Print", {KEY_LEFT_CTRL, 'P', 0}, {KEY_LEFT_GUI, 'P', 0}}, //14
    {"Screenshot", {KEY_PRINT_SCREEN, 0, 0}, {KEY_PRINT_SCREEN, 0, 0}} //15
};

const Macro CODING_MACROS[15] = {
    {"Comment", {KEY_LEFT_CTRL, KEY_KP_SLASH, 0}, {KEY_LEFT_GUI, KEY_KP_SLASH, 0}}, // 1
    {"Uncomment", {KEY_LEFT_CTRL, KEY_KP_SLASH, 0}, {KEY_LEFT_GUI, KEY_KP_SLASH, 0}}, // 2
    {"Format", {KEY_LEFT_CTRL, 'K', 'D'}, {KEY_LEFT_GUI, 'K', 'D'}}, // 3
    {"Find Next", {KEY_LEFT_CTRL, 'G', 0}, {KEY_LEFT_GUI, 'G', 0}}, // 4
    {"Find Previous", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'G'}, {KEY_LEFT_GUI, KEY_LEFT_SHIFT, 'G'}}, // 5
    {"Go to Line", {KEY_LEFT_CTRL, 'G', 0}, {KEY_LEFT_GUI, 'G', 0}}, // 6
    {"Rename Symbol", {KEY_F2, 0, 0}, {KEY_F2, 0, 0}}, // 7
    {"Go to Definition", {KEY_F12, 0, 0}, {KEY_F12, 0, 0}}, // 8
    {"Go to Implementation", {KEY_LEFT_SHIFT, KEY_F12}, {KEY_LEFT_SHIFT, KEY_F12}}, //9
    {"Show References", {KEY_LEFT_SHIFT, KEY_F12}, {KEY_LEFT_SHIFT, KEY_F12}}, //10
    {"Debug", {KEY_F5, 0, 0}, {KEY_F5, 0, 0}}, //11
    {"Step Over", {KEY_F10, 0, 0}, {KEY_F10, 0, 0}}, //12
    {"Step Into", {KEY_F11, 0, 0}, {KEY_F11, 0, 0}}, //13
    {"Step Out", {KEY_LEFT_SHIFT, KEY_F11}, {KEY_LEFT_SHIFT, KEY_F11}}, //14
    {"Run to Cursor", {KEY_LEFT_CTRL | KEY_LEFT_SHIFT | KEY_LEFT_SHIFT | KEY_F10}, {KEY_LEFT_CTRL | KEY_LEFT_SHIFT | KEY_LEFT_SHIFT | KEY_F10}} //15
};

const Menu menus[3] = {
    {"Clicker", CLICKER, NULL}, // 0
    {"Default", COMMONS, DEFAULT_MACROS}, // 1
    {"Coding", CODING, CODING_MACROS}     // 2
};

const int buttonAnalogValues[6] = {614, 819, 1023, 408, 203, 0};

class MechMacro {
protected:
    unsigned long now = 0;
  	int currentMenuIndex = -1;
	int currentMacroSetIndex = 0;
    int lastButtonIndex = -1;
    int motorPin = 5;
    int currentOS = 0;
public:
    MechMacro(int selectedOS, int motorPin=5);
    void pressButton(int analogValue, int releaseDelay=100);
    void clickerMode();
private:
    void getMacro(int value);
    void cancelMenu();
    void hapticFeedback(int value);
    void nextMacroSet();
};

#endif //MECHMENU_H
