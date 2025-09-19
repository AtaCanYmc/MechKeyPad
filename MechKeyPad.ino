// -----------------------------------------------------------------------------
// MechKeyPad.ino
//
// Main application file for the MechMacroPad.
// This file is responsible for:
// - Initializing hardware (OLED display, buttons).
// - Creating an instance of the MechMacro logic class.
// - Running the main loop to read button presses and update the display.
// -----------------------------------------------------------------------------

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "MechMacro.h" // Include our custom macro logic class

// --- Pin and Hardware Definitions ---
#define SENSOR_PIN A0
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

// --- Global Objects ---
// Create an instance of the OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Create an instance of our MechMacro class, selecting WINDOWS as the OS.
// You can change this to MAC if you are on a macOS.
MechMacro macroPad(WINDOWS);

// --- State Variables ---
int lastAnalogValue = -1; // Stores the last read analog value to detect changes

// -----------------------------------------------------------------------------
// SETUP: Runs once when the Arduino starts up.
// -----------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  initializeOLED();
  updateDisplay(); // Initial display update
}

// -----------------------------------------------------------------------------
// LOOP: Runs continuously after setup().
// -----------------------------------------------------------------------------
void loop() {
  // Read the current analog value from the buttons
  int currentAnalogValue = analogRead(SENSOR_PIN);

  // Check if the button state has changed (pressed or released)
  if (currentAnalogValue != lastAnalogValue) {
    // A button has been pressed. Let the MechMacro class handle it.
    // The class contains all the logic for debouncing and executing actions.
    macroPad.handleButtonPress(currentAnalogValue);

    // After handling the press, update the display with the new state
    updateDisplay();
    
    // Update the last known value
    lastAnalogValue = currentAnalogValue;
  }
  
  // Also, let the MechMacro class handle any time-based tasks, like the clicker mode.
  macroPad.updateClickerMode();
}

// --- Helper Functions ---

/**
 * @brief Initializes the OLED display.
 */
void initializeOLED() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("[OLED] - SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.display();
}

/**
 * @brief Clears the display and shows the current menu name.
 * It gets the menu name from our macroPad object.
 */
void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(2); // Use a larger font for the menu title
  display.setCursor(0, 8);
  
  // Get the current menu name from the MechMacro object and print it
  display.print(macroPad.getCurrentMenuName());
  
  display.display();
}