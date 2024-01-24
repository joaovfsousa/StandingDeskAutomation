#include <Arduino.h>
#include "WiFi.h"
#include <fauxmoESP.h>
#include <map>

fauxmoESP fauxmo;

const char *ssid = "your_ssid_here";
const char *password = "your_password_here";

unsigned long reconnectPreviousMillis = 0;
unsigned long reconnectInterval = 30000;

typedef struct
{
  char *name;
  int pin;
} DeskButton;

DeskButton deskButtons[] = {
    {"Desk Position 1", 33},
    {"Desk Position 2", 32},
    {"Desk Position 3", 13},
    {"Desk Position 4", 14},
};

std::map<int, int> idToPinMap;

void connectToWifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(300);
  }

  Serial.print("Connected to the WiFi network, IP: ");
  Serial.println(WiFi.localIP());
}

void reconnectWifi()
{
  unsigned long currentMillis = millis();
  if (currentMillis - reconnectPreviousMillis >= reconnectInterval)
  {
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    reconnectPreviousMillis = currentMillis;
  }
}

void handleSetState(unsigned char device_id, const char *device_name, bool state, unsigned char value);

void setup()
{
  for (auto const &button : deskButtons)
  {
    auto pin = button.pin;
    auto name = button.name;

    digitalWrite(pin, LOW);
    pinMode(pin, OUTPUT);

    int id = fauxmo.addDevice(name);

    idToPinMap[id] = pin;
  }

  Serial.begin(9600);

  connectToWifi();

  fauxmo.setPort(80);
  fauxmo.enable(true);

  fauxmo.onSetState(handleSetState);
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    reconnectWifi();
  }
  fauxmo.handle();
}

void handleSetState(unsigned char device_id, const char *device_name, bool state, unsigned char value)
{
  auto pin = idToPinMap[device_id];

  Serial.println("Activated: " + String(device_name));

  digitalWrite(pin, HIGH);
  delay(1000);
  digitalWrite(pin, LOW);
}