// Main sketch 

#include "display_utils.h"
#include "firebase_utils.h"
#include "wifi_utils.h"
#include "eeprom_utils.h"
#include "web_server.h"

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_SDA, I2C_SCL);
  initDisplay();
  showStartupScreen();
  readCredentialsFromEEPROM();
  pinMode(0, INPUT_PULLUP);

  if (digitalRead(0) == 0) {
    startAccessPointMode();
  } else {
    if (connectToWiFi()) {
      initFirebase();
      startFirebaseStream();
    } else {
      startAccessPointMode();
    }
  }
}

void loop() {
  if (isInAPMode()) {
    handleWebRequests();
  }
  maintainFirebaseConnection();
}
