# Arduino Pro Micro Macropad

A 6-key mechanical macropad powered by an Arduino Pro Micro, featuring an OLED display, haptic feedback, and multiple, easily swappable macro layers.

This project is built with a focus on modular, readable, and easily customizable code.

<div align="center">
    <img src="https://miro.medium.com/v2/resize:fit:1400/format:webp/1*iJYBHWuJ6YqIQgAisH7_4w@2x.jpeg" height="250" width="400" alt="languages graph"  />
</div>

## Features

- **6 Programmable Keys:** Five keys for macros and one dedicated key to cycle through menus.
- **OLED Status Display:** A 128x32 SSD1306 OLED screen shows the currently active macro menu (e.g., "Common", "Coding").
- **Haptic Feedback:** A small vibration motor provides physical confirmation on key presses and menu changes.
- **Multiple Macro Layers:** Switch between different sets of macros on-the-fly. The code includes pre-configured layers for common shortcuts and coding tasks.
- **Modular C++ Code:** The logic is encapsulated in a `MechMacro` class, making it easy to understand, maintain, and extend.
- **Cross-Platform Support:** Macro definitions include key mappings for both Windows and macOS.

## Hardware Required

- Arduino Pro Micro (or a compatible ATmega32U4-based board)
- 1x SSD1306 I2C OLED Display (128x32)
- 6x Mechanical Keyboard Switches
- 1x Small Vibration Motor (e.g., pancake or cylindrical)
- Resistors to create a resistor ladder for analog button input.
- Wires, a breadboard, or a custom PCB.

## Software & Libraries

- [Arduino IDE](https://www.arduino.cc/en/software) or [PlatformIO](https://platformio.org/)
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit SSD1306 Library](https://github.com/adafruit/Adafruit_SSD1306)

Install the libraries using the Arduino IDE's Library Manager.

## Installation & Setup

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/AtaCanYmc/MechKeyPad
    ```
2.  **Hardware Assembly:** Connect the components to the Arduino Pro Micro as defined in the code:
    - **OLED Display:** Connect via I2C (VCC, GND, SCL, SDA).
    - **Buttons:** Wire the 6 buttons using a resistor ladder, with the output connected to pin `A0`.
    - **Vibration Motor:** Connect to pin `5` (or `HAPTIC_FEEDBACK_PIN`).
3.  **Configure:** Open `MechKeyPad.ino`. At the top, select your target operating system:
    ```cpp
    // Change to MAC if you are on macOS
    MechMacro macroPad(WINDOWS); 
    ```
4.  **Upload:** Select "Arduino Leonardo" or "SparkFun Pro Micro" from the board menu in the Arduino IDE and upload the sketch.

## How to Use

- **Press Buttons 1-5:** Trigger the corresponding macro for the currently active menu.
- **Press Button 6:** Cycle through the available menus (e.g., "Clicker" -> "Common" -> "Coding").
- The OLED display will update to show the name of the current menu.

## Customization

Customizing macros is straightforward:

1.  Open the `MechMacro.cpp` file.
2.  Locate the `COMMON_MACROS` and `CODING_MACROS` arrays.
3.  Modify the existing entries or add new ones. Each macro has a name, a set of Windows keys, and a set of macOS keys.

```cpp
// Example macro definition:
// {"Name", {WIN_KEY_1, WIN_KEY_2, 0}, {MAC_KEY_1, MAC_KEY_2, 0}}
{"Copy", {KEY_LEFT_CTRL, 'c', 0}, {KEY_LEFT_GUI, 'c', 0}},
```

If your button readings are inconsistent, you may need to calibrate the analog value ranges in the `getButtonIndex()` function inside `MechMacro.cpp`. Use the Arduino Serial Monitor to see the values your hardware produces for each key press.