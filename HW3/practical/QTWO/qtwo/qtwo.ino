#include <WiFi.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <Preferences.h>
#include "esp_system.h"

const char* ssid = "ParsaTCL";           
const char* password = "255252343334";           
const char* firmwareURL = "http://192.168.1.100/newfirm.bin";

#define FIRMWARE_VERSION "1.0.1"             

Preferences preferences;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Booting ESP32...");
  Serial.printf("Current Firmware Version: %s\n", FIRMWARE_VERSION);

  esp_reset_reason_t resetReason = esp_reset_reason();
  Serial.print("Reset Reason: ");
  printResetReason(resetReason);

  connectToWiFi();

  checkAndUpdateFirmware();
}

void loop() {
  delay(1000);
}

void connectToWiFi() {
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());
}

void checkAndUpdateFirmware() {
  preferences.begin("ota", false);
  String storedVersion = preferences.getString("version", "0.0.0");

  if (storedVersion != FIRMWARE_VERSION) {
    Serial.println("New Firmware Detected. Performing OTA Update...");
    if (performOTAUpdate()) {
      Serial.println("Updating stored firmware version...");
      preferences.putString("version", FIRMWARE_VERSION);
    } else {
      Serial.println("OTA update failed or no update available.");
    }
  } else {
    Serial.println("Firmware is up to date.");
  }
  preferences.end();
}

bool performOTAUpdate() {
  WiFiClient client;
  Serial.println("Starting OTA update...");

  t_httpUpdate_return result = httpUpdate.update(client, firmwareURL);

  switch (result) {
    case HTTP_UPDATE_FAILED:
      Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
      return false;

    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("HTTP_UPDATE_NO_UPDATES");
      return false;

    case HTTP_UPDATE_OK:
      Serial.println("HTTP_UPDATE_OK: Update successful!");
      delay(1000);
      ESP.restart();  
      return true;
  }
  return false;
}

void printResetReason(esp_reset_reason_t reason) {
  switch (reason) {
    case ESP_RST_POWERON: Serial.println("Power-on reset"); break;
    case ESP_RST_EXT: Serial.println("External reset"); break;
    case ESP_RST_SW: Serial.println("Software reset"); break;
    case ESP_RST_PANIC: Serial.println("Exception/panic reset"); break;
    case ESP_RST_WDT: Serial.println("Watchdog reset"); break;
    case ESP_RST_DEEPSLEEP: Serial.println("Deep sleep reset"); break;
    case ESP_RST_BROWNOUT: Serial.println("Brownout reset"); break;
    case ESP_RST_SDIO: Serial.println("SDIO reset"); break;
    default: Serial.println("Unknown reset reason"); break;
  }
}
