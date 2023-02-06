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

int light;
int curtain;
int lamp;

void handleRoot() {
  server.send(200, "application/json", "{\"light\":" + String(light) + ",\"curtain\":" + String(curtain) + ",\"lamp\":" + String(lamp) + "}");
}

void turnOnLamp() {
  Serial.println("lamp: on");
  server.send(200, "text/plain", "done");
}

void turnOffLamp() {
  Serial.println("lamp: off");
  server.send(200, "text/plain", "done");
}

void closeCurtain() {
  if (curtain <= 0) {
    server.send(400, "text/plain", "can't close the curtain any further!");
    return;
  }
  Serial.println("curtain: " + String(curtain - 1));
  server.send(200, "text/plain", "done");
}

void openCurtain() {
  if (curtain >= 10) {
    server.send(400, "text/plain", "can't open the curtain any further!");
    return;
  }
  Serial.println("curtain: " + String(curtain + 1));
  server.send(200, "text/plain", "done");
}

void handleNotFound() {
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
}

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  if (MDNS.begin("esp8266")) { }

  server.on("/", handleRoot);

  server.on("/close-curtain", closeCurtain);
  server.on("/open-curtain", openCurtain);
  server.on("/lamp-on", turnOnLamp);
  server.on("/lamp-off", turnOffLamp);

  server.onNotFound(handleNotFound);

  server.begin();
  server.enableCORS(true);
}

void loop(void) {
  server.handleClient();
  MDNS.update();
  if (Serial.available()) {
    String message = Serial.readStringUntil('\n');
    if (message.startsWith("light:")) {
      light = message.substring(7).toInt();
    } else if (message.startsWith("curtain:")) {
      curtain = message.substring(9).toInt();
    } else if (message.startsWith("lamp:")) {
      lamp = message.substring(6).toInt();
    }
  }
}
