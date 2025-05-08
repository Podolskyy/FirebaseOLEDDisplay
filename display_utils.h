//For OLED Display
#ifndef DISPLAY_UTILS_H
#define DISPLAY_UTILS_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define I2C_SDA 4
#define I2C_SCL 15

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  display.clearDisplay();
  display.display();
  Serial.println("OLED initialized");
}

void showStartupScreen() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("LCD Firebase Display");
  display.setCursor(0, 10);
  display.println("Developed By");
  display.setCursor(0, 20);
  display.println("Wan Ikmal");
  display.display();
  delay(2000);
}

void updateDisplay(String a, String b, String c) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(a);
  display.setCursor(0, 10);
  display.println(b);
  display.setCursor(0, 20);
  display.println(c);
  display.display();
}

#endif
