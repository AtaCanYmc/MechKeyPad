#include "MechMacro.h"

// --- Macro and Menu Data Definitions ---
// The data for macros is defined here. It's clean and easy to modify.

// Common shortcuts
const Macro COMMON_MACROS[5] = {
    {"Copy", {KEY_LEFT_CTRL, 'c', 0}, {KEY_LEFT_GUI, 'c', 0}},
    {"Paste", {KEY_LEFT_CTRL, 'v', 0}, {KEY_LEFT_GUI, 'v', 0}},
    {"Cut", {KEY_LEFT_CTRL, 'x', 0}, {KEY_LEFT_GUI, 'x', 0}},
    {"Undo", {KEY_LEFT_CTRL, 'z', 0}, {KEY_LEFT_GUI, 'z', 0}},
    {"Save", {KEY_LEFT_CTRL, 's', 0}, {KEY_LEFT_GUI, 's', 0}}
};

// Shortcuts for coding
const Macro CODING_MACROS[5] = {
    {"Comment", {KEY_LEFT_CTRL, 'k', 'c'}, {KEY_LEFT_GUI, '/', 0}},
    {"Format", {KEY_LEFT_SHIFT, KEY_LEFT_ALT, 'f'}, {KEY_LEFT_SHIFT, KEY_LEFT_ALT, 'f'}},
    {"Find All", {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'f'}, {KEY_LEFT_GUI, KEY_LEFT_SHIFT, 'f'}},
    {"Debug", {KEY_F5, 0, 0}, {KEY_F5, 0, 0}},
    {"Build", {KEY_F7, 0, 0}, {KEY_F7, 0, 0}}
};

// Menu definitions that tie everything together
const Menu MENUS[MENU_COUNT] = {
    {"Clicker", CLICKER_MODE, NULL},
    {"Common", COMMONS_MODE, COMMON_MACROS},
    {"Coding", CODING_MODE, CODING_MACROS}
};

// --- Private Variables ---
static unsigned long lastClickTime = 0;

// -----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
// -----------------------------------------------------------------------------

/**
 * @brief Constructs the MechMacro object.
 * @param selectedOS The operating system (WINDOWS or MAC) for key mappings.
 */
MechMacro::MechMacro(OperatingSystem selectedOS) {
    this->currentOS = selectedOS;
    this->currentMode = COMMONS_MODE; // Start with Common macros by default
    this->lastButtonPressTime = 0;
    pinMode(HAPTIC_FEEDBACK_PIN, OUTPUT);
    digitalWrite(HAPTIC_FEEDBACK_PIN, LOW);
}

/**
 * @brief Handles button press logic, including debouncing.
 * @param analogValue The raw analog reading from the button pin.
 */
void MechMacro::handleButtonPress(int analogValue) {
    // Debounce: Ignore presses that are too close together
    if (millis() - lastButtonPressTime < DEBOUNCE_DELAY_MS) {
        return;
    }

    int buttonIndex = getButtonIndex(analogValue);

    // If no valid button was detected, do nothing.
    if (buttonIndex == -1) return;

    // A valid button was pressed, so update the time
    lastButtonPressTime = millis();

    // Button 5 (the 6th button) is dedicated to switching menus
    if (buttonIndex == 5) {
        switchMacroSet();
    } else {
        executeMacro(buttonIndex);
    }
}

/**
 * @brief Updates the clicker mode functionality.
 */
void MechMacro::updateClickerMode() {
    if (currentMode == CLICKER_MODE && millis() - lastClickTime >= CLICKER_MODE_INTERVAL_MS) {
        lastClickTime = millis();
        Keyboard.press(' '); // Example: send a spacebar press
        delay(RELEASE_DELAY_MS);
        Keyboard.releaseAll();
    }
}

/**
 * @brief Returns the name of the currently active menu.
 * @return A const char* to the menu name.
 */
const char* MechMacro::getCurrentMenuName() {
    return MENUS[currentMode].name;
}


// -----------------------------------------------------------------------------
// PRIVATE (HELPER) FUNCTIONS
// -----------------------------------------------------------------------------

/**
 * @brief Executes a specific macro.
 * @param buttonIndex The index (0-4) of the pressed button.
 */
void MechMacro::executeMacro(int buttonIndex) {
    const Menu& currentMenu = MENUS[currentMode];

    // Check if the current menu has macros and the index is valid
    if (currentMenu.macros == NULL || buttonIndex >= 5) {
        return;
    }

    const Macro& selectedMacro = currentMenu.macros[buttonIndex];
    const uint8_t* keys = (currentOS == WINDOWS) ? selectedMacro.winKeys : selectedMacro.macKeys;

    for (int i = 0; i < 3 && keys[i] != 0; i++) {
        Keyboard.press(keys[i]);
    }
    delay(RELEASE_DELAY_MS);
    Keyboard.releaseAll();

    provideHapticFeedback(50); // Provide a short feedback pulse
}

/**
 * @brief Switches to the next available menu.
 */
void MechMacro::switchMacroSet() {
    currentMode = (MenuMode)((currentMode + 1) % MENU_COUNT);
    provideHapticFeedback(100); // Provide a longer pulse for menu change

    Serial.print("Switched to mode: "); // For debugging
    Serial.println(MENUS[currentMode].name);
}

/**
 * @brief Provides haptic feedback by vibrating the motor.
 * @param durationMs The duration of the vibration in milliseconds.
 */
void MechMacro::provideHapticFeedback(int durationMs) {
    digitalWrite(HAPTIC_FEEDBACK_PIN, HIGH);
    delay(durationMs);
    digitalWrite(HAPTIC_FEEDBACK_PIN, LOW);
}

/**
 * @brief Finds the button index corresponding to an analog value using ranges.
 * @param analogValue The analog reading to check.
 * @return The index of the button (0-5) or -1 if no match is found.
 */
int MechMacro::getButtonIndex(int analogValue) {
    if (analogValue >= 900) return 2;      // Target: 1023
    if (analogValue >= 700) return 1;      // Target: 819
    if (analogValue >= 500) return 0;      // Target: 614
    if (analogValue >= 300) return 3;      // Target: 408
    if (analogValue >= 100) return 4;      // Target: 203
    if (analogValue >= 0)   return 5;      // Target: 0
    return -1; // No button press detected
}