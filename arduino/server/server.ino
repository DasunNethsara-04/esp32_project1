#include <WiFi.h>
#include <WebServer.h>

#define WIFI_SSID "Mr.IPS"
#define WIFI_PWD "596FE8C1"

#define LED 23

WebServer server(80);

void handleLed() {
  if (!server.hasArg("state")) {
    server.send(400, "application/json", "Missing state parameter");
  }

  String state = server.arg("state");
  if (state == "ON") {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
  server.send(200, "application/json", "LED is " + state);
}

void setup() {
  pinMode(LED, OUTPUT);
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
  server.begin();
}

void loop() {
  server.handleClient();
}
