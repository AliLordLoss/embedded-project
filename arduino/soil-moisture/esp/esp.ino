#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "mfary"
#define STAPSK "P@ssword"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

const int led = 13;

int gas = 0;
int moisture = 0;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "application/json", "{\"moisture\":" + String(moisture) + ",\"gas\":" + String(gas) + "}");
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) { message += " " + server.argName(i) + ": " + server.arg(i) + "\n"; }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  if (MDNS.begin("esp8266")) { }

  server.on("/", handleRoot);

  server.onNotFound(handleNotFound);

  server.begin();
  server.enableCORS(true);
}

void loop(void) {
  server.handleClient();
  MDNS.update();
  if (Serial.available()) {
    String message = Serial.readStringUntil('\n');
    if (message.startsWith("moisture:")) {
      moisture = message.substring(10).toInt();
    } else if (message.startsWith("gas")) {
      gas = message.substring(5).toInt();
    }
  }
}
