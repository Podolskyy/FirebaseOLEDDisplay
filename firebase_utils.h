//For firebase related processes
#ifndef FIREBASE_UTILS_H
#define FIREBASE_UTILS_H

#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include "display_utils.h"
#include "eeprom_utils.h"

#define FIREBASE_HOST "https://datadisplaysystem-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define API_KEY "AIzaSyDPB0OzHrhuRJOz8ZgXd4o0Cb26pl1D0UM"
#define USER_EMAIL "testuser@example.com"
#define USER_PASSWORD "TestPassword123"

FirebaseData fbdo;
FirebaseData metaFbdo;
FirebaseAuth auth;
FirebaseConfig config;
bool firebaseReady = false;

void initFirebase() {
  config.api_key = API_KEY;
  config.database_url = FIREBASE_HOST;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  configTime(28800, 0, "pool.ntp.org", "time.nist.gov");
  while (time(nullptr) < 8 * 3600 * 2) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nTime synchronized");

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  while (auth.token.uid == "") {
    Serial.print(".");
    delay(500);
  }
  firebaseReady = true;
  Serial.println("\nFirebase Ready!");
}



void streamCallback(FirebaseStream data) {
  if (data.dataType() == "string") {
    Serial.println("[Stream] " + data.stringData());
    String message = data.stringData();
    String timestamp = "-";

    if (Firebase.RTDB.getString(&metaFbdo, "/texts/last_updated")) {
      timestamp = metaFbdo.stringData();
      Serial.println(timestamp);
      Serial.println(devid);
    } else {
      Serial.println("Failed to get timestamp: " + metaFbdo.errorReason());
    }

    updateDisplay("Device ID: " + devid, message, "At: " + timestamp);

  }
}

void streamTimeoutCallback(bool timeout) {
  if (timeout) {
    Serial.println("[Stream] Timeout occurred");
  }
}

void startFirebaseStream() {
  if (!Firebase.RTDB.beginStream(&fbdo, "/texts/sample_text")) {
    Serial.println("Could not begin stream");
    Serial.println(fbdo.errorReason());
    return;
  }
  Firebase.RTDB.setStreamCallback(&fbdo, streamCallback, streamTimeoutCallback);
}

void maintainFirebaseConnection() {
  if (!Firebase.ready() && Firebase.isTokenExpired()) {
    Serial.println("Refreshing token...");
    Firebase.begin(&config, &auth);
  }
}

#endif
