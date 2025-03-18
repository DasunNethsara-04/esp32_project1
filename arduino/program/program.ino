#include <WiFi.h>
#include <WebServer.h>

#define WIFI_SSID "test"
#define WIFI_PWD "123456789"

const int delayTime = 250;
const int pins[] = {18, 19, 21, 22, 23};
const int arrayLength = sizeof(pins) / sizeof(pins[0]);

WebServer server(80);

void pattern() {
  for (int i = 0; i < arrayLength; i++) {
    if (i != 20) {
      digitalWrite(pins[i], HIGH);
      delay(delayTime);
    }
  }

  delay(delayTime);

  for (int i = 0; i < arrayLength; i++) {
    if (i != 20) {
      digitalWrite(pins[i], LOW);
      delay(delayTime);
    }
  }

  delay(delayTime);

  for (int i = arrayLength; i >= 0; i--) {
    digitalWrite(pins[i], HIGH);
    delay(delayTime);
  }

  delay(delayTime);

  for (int i = arrayLength; i >= 0; i--) {
    digitalWrite(pins[i], LOW);
    delay(delayTime);
  }
}

void handleAllLeds() {
  if (!server.hasArg("state")) {
    server.send(400, "application/json", "Missing state parameter");
  }

  String state = server.arg("state");
  if (state == "ON") {
    for (int i = 0; i < arrayLength; i++) {
      digitalWrite(pins[i], HIGH);
    }
  } else {
    for (int i = 0; i < arrayLength; i++) {
      digitalWrite(pins[i], LOW);
    }
  }
  server.send(200, "application/json", "LED is " + state);
}

void handlePatterns() {
  if (!server.hasArg("state")) {
    server.send(400, "application/json", "Missing state parameter");
  }

  String state = server.arg("state");
  server.send(200, "application/json", "Pattern is " + state);
  if (state == "ON") {
    pattern();
  } else {
    for (int i = 0; i < arrayLength; i++) {
      digitalWrite(pins[i], LOW);
    }
  }
}

void handleLed() {
  if (!server.hasArg("state") || !server.hasArg("led")) {
    server.send(400, "application/json", "Missing state or led parameter");
  }

  String state = server.arg("state");
  int led = (server.arg("led")).toInt();
  if (state == "ON") {
    digitalWrite(pins[led - 1], HIGH);
  } else {
    digitalWrite(pins[led - 1], LOW);
  }
  server.send(200, "application/json", "LED is " + state);
}

void setup() {
  for (int i = 0; i < arrayLength; i++) {
    pinMode(pins[i], OUTPUT);
  }
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PWD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.printf("\nConencted to WiFi: %s\n", WIFI_SSID);
  Serial.printf("IP: %s\n", WiFi.localIP().toString().c_str());

  server.on("/led", handleLed);
  server.on("/led/all", handleAllLeds);
  server.on("/led/pattern", handlePatterns);
  server.begin();
}

void loop() {
  server.handleClient();
}
