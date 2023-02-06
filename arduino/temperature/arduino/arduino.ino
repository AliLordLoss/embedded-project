#include <dht.h>


#define sensorPinDHT 13 // Defines pin number to which the sensor is connected
#define heaterLED 5 // Defines pin number to which the sensor is connected
#define coolerLED 4 // Defines pin number to which the sensor is connected
dht DHT; // Creats a DHT object
int heaterONThreshold = 15;
int heaterOFFThreshold = 20;
int coolerONThreshold = 30;
int coolerOFFThreshold = 25;

int heater = 0;
int cooler = 0;
int tpr = 0;
String state = "manual";

void setup() {
  Serial.begin(9600);

  Serial1.begin(115200);

  pinMode(sensorPinDHT, INPUT);
  pinMode(coolerLED, OUTPUT);
  pinMode(heaterLED, OUTPUT);
  
  digitalWrite(coolerLED, LOW);
  digitalWrite(heaterLED, LOW);
}

void loop() {
  int newT = readSensorTemperature();
  if (newT != tpr) {
    tpr = newT;
    Serial1.println("temperature: " + String(tpr));
  }

  if (Serial1.available()) {
    String message = Serial1.readStringUntil('\n');
    Serial.println(message);
    if (message.startsWith("cooler:")) {
      Serial.println(message.substring(8, 10));
      if (message.substring(8, 10) == "on") {
        Serial.println("cooler on");
        cooler = 1;
      } else if (message.substring(8, 11) == "off") {
        cooler = 0;
      }
    } else if (message.startsWith("heater:")) {
      if (message.substring(8, 10) == "on") {
        heater = 1;
      } else if (message.substring(8, 11) == "off") {
        heater = 0;
      }
    }
  }

  if (heater == 1) {
    digitalWrite(heaterLED, HIGH);
  } else {
    digitalWrite(heaterLED, LOW);
  }

  if (cooler == 1) {
    digitalWrite(coolerLED, HIGH);
  } else {
    digitalWrite(coolerLED, LOW);
  }

  delay(2000);
}

float readSensorTemperature() {
  int readData = DHT.read22(sensorPinDHT); // DHT22/AM2302


  float t = DHT.temperature; // Gets the values of the temperature
  float h = DHT.humidity; // Gets the values of the humidity

  // Printing the results on the serial monitor
//  Serial.print("Temperature = ");
//  Serial.print(t);
//  Serial.print(" ");
//  Serial.print((char)176);//shows degrees character
//  Serial.print("C | ");
//  Serial.print((t * 9.0) / 5.0 + 32.0);//print the temperature in Fahrenheit
//  Serial.print(" ");
//  Serial.print((char)176);//shows degrees character
//  Serial.println("F ");
//  Serial.print("Humidity = ");
//  Serial.print(h);
//  Serial.println(" % ");
  if (state == "auto") {
    if (t < heaterONThreshold)
      heater = 1;
    else if (t > heaterOFFThreshold)
      heater = 0;
    if (t > coolerONThreshold)
      cooler = 1;
    else if (t < coolerOFFThreshold)
      cooler = 0;
  }
  return t;
}
