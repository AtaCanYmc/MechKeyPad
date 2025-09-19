#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "MechMacro.h"

#define SENSOR_PIN A0
#define MOTOR_PIN 5

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

#define CONTROL_TIME 1000

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int now = 0;
int readKey = 0;


void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_PIN, OUTPUT);
  startOLED();
}

void loop() {

}

int getKeyIndex() {
  int keyValue = analogRead(SENSOR_PIN);
  switch(keyValue) {
    case 614:
      hapticFeedback(512);
      return 1;
    case 819:
      hapticFeedback(512);
      return 2;
    case 1023:
      hapticFeedback(512);
      return 3;
    case 408:
      hapticFeedback(512);
      return 4;
    case 203:
      hapticFeedback(512);
      return 5;
    case 0:
      hapticFeedback(512);
      return 6;
    default:
      hapticFeedback(0);
      return 0;
  }
}

void hapticFeedback(int value) {
  int motorPower = map(value, 0, 1023, 0, 255); 
  analogWrite(MOTOR_PIN, motorPower);
}

void startOLED() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("[OLED] - SSD1306 OLED başlatılamadı!");
  } else {
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
  }
}

void writeText(int x, int y, int font, String text, int color) {
  display.setCursor(x, y);
  display.setTextSize(font);
  display.setTextColor(color);
  display.print(text);
  display.display();
}

void writeText(int x, int y, int font, String text) {
  writeText(x, y, font, text, SSD1306_WHITE);
}

void writeText(int x, int y, String text) {
  writeText(x, y, 1, text);
}

void checkButtons() {
  readKey = getKeyIndex();
  if (now + CONTROL_TIME < millis()) {
    now = millis();
  }
}
