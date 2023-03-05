#include <Arduino.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

class ESPWiFi {
  public:
    ESPWiFi(const char* _wiFiSSID, const char* _wiFiPassword, const String _wifiHostname = "");
    ESPWiFi();
    void connect();
    void reconnect();
    bool connected();
    void setLedToggle(bool _ledToggle = true);
    void setSSID(const char* _wiFiSSID);
    void setPassword(const char* _wiFiPassword);
    void setHostname(String _wifiHostname);
    IPAddress getLocalIp();
  private:
    const char* wiFiSSID;
    const char* wiFiPassword;
    String wifiHostname;
    bool prevWifiOnline = false;
    unsigned long previousMillis = 0;
    unsigned long interval = 30000;
    unsigned long lastLedToggle = 0;
    unsigned long ledToggleInterval = 1000;
    bool builtinLedIsOn = false;
    bool ledToggle = false;
    void builtinLedOn();
    void builtinLedOff();
    void builtinLedToggle();
};