#include <Arduino.h>
#include "ESPWiFi.h"

ESPWiFi::ESPWiFi(const char* _wiFiSSID, const char* _wiFiPassword, const String _wifiHostname) {
  wiFiSSID = _wiFiSSID;
  wiFiPassword = _wiFiPassword;
  WiFi.mode(WIFI_STA);
  #if defined(ESP8266)
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  #endif
  WiFi.hostname(_wifiHostname);
}

ESPWiFi::ESPWiFi() {
  WiFi.mode(WIFI_STA);
  #if defined(ESP8266)
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  #endif
}

void ESPWiFi::connect() {
  Serial.print("\nConnecting to WiFi");
  WiFi.begin(wiFiSSID, wiFiPassword);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    if (ledToggle) {
      builtinLedToggle();
    }
    delay(1000);
  }
  Serial.println("ok");
  prevWifiOnline = true;
  if (ledToggle) {
    builtinLedOff();
  }
}

void ESPWiFi::reconnect() {
  unsigned long currentMillis = millis();

  if (ledToggle && (WiFi.status() != WL_CONNECTED) && (currentMillis - lastLedToggle >= ledToggleInterval)) {
    builtinLedToggle();
    lastLedToggle = currentMillis;
  }

  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >= interval)) {
    prevWifiOnline = false;
    Serial.println("Connecting to WiFi...");
    WiFi.disconnect();
    WiFi.begin(wiFiSSID, wiFiPassword);
    previousMillis = currentMillis;
  } else if (WiFi.status() == WL_CONNECTED && prevWifiOnline == false) {
    Serial.println("WiFi Connection OK");
    prevWifiOnline = true;
    if (ledToggle) {
      builtinLedOff();
    }
  }
}

bool ESPWiFi::connected() {
  return WiFi.status() == WL_CONNECTED;
}

void ESPWiFi::setLedToggle(bool _ledToggle) {
  ledToggle = _ledToggle;
}

void ESPWiFi::setSSID(const char* _wiFiSSID) {
  wiFiSSID = _wiFiSSID;
}

void ESPWiFi::setPassword(const char* _wiFiPassword) {
  wiFiPassword = _wiFiPassword;
}

void ESPWiFi::setHostname(String _wifiHostname) {
  wifiHostname = _wifiHostname;
}

void ESPWiFi::getLocalIp() {
  return WiFi.localIP();
}

void ESPWiFi::builtinLedOn() {
  digitalWrite(BUILTIN_LED, LOW);
  builtinLedIsOn = true;
}

void ESPWiFi::builtinLedOff() {
  digitalWrite(BUILTIN_LED, HIGH);
  builtinLedIsOn = false;
}

void ESPWiFi::builtinLedToggle() {
  digitalWrite(BUILTIN_LED, builtinLedIsOn ? HIGH : LOW);
  builtinLedIsOn = !builtinLedIsOn;
}