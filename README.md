# Firebase OLED Display with ESP32

This ESP32-based project connects to Firebase Realtime Database, listens for live updates, and displays messages + timestamps on an OLED screen. It also includes a WiFi configuration portal (AP mode) and stores credentials using EEPROM.

---

## 📂 File Overview

### `FirebaseOLEDDisplay.ino`
Main sketch:
- Initializes display, WiFi, and Firebase
- Connects to saved WiFi or enters AP config mode
- Begins listening to Firebase changes

### `display_utils.h`
OLED display handling:
- `initDisplay()`: initializes screen
- `showStartupScreen()`: intro splash
- `updateDisplay(a, b, c)`: prints 3 lines of text

### `firebase_utils.h`
Firebase logic:
- Connects and authenticates with Firebase
- Starts real-time stream on `/texts/sample_text`
- Pulls `/texts/last_updated` and displays both
- Includes `updateTimestamp()` helper

### `wifi_utils.h`
WiFi management:
- Connects to stored WiFi or launches AP mode
- Uses GPIO 0 button as config mode trigger

### `eeprom_utils.h`
EEPROM storage:
- Saves/loads SSID, password, and device ID
- Clearable via web interface

### `web_server.h`
Web configuration portal:
- Runs in AP mode
- HTML form to input WiFi credentials
- Saves to EEPROM and restarts ESP

---

## 🛠 Usage

1. Upload to your ESP32
2. First boot: press GPIO 0 to launch AP mode
3. Connect to WiFi `ESP32_eeprom`, go to `192.168.4.1`
4. Submit WiFi & device ID settings
5. ESP connects to Firebase and displays updates live on OLED

---

## 🧪 Firebase Notes

Expected Realtime Database structure:
```json
{
  "texts": {
    "sample_text": "Hello!",
    "last_updated": "2025-05-09 03:00"
  }
}
```

Update from your web app, and ESP32 will reflect the message + timestamp.
