#include <Wire.h>
#include <BH1750.h>
#include <Stepper.h>

const int steps_per_rev = 2038; 

#define lampPin 7
#define IN1 6
#define IN2 5
#define IN3 4
#define IN4 3


BH1750 lightMeter;
Stepper motor(steps_per_rev, IN1, IN3, IN2, IN4);


String lamp = "off";
int light = 0;
int curtain = 0;
int curtainValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(lampPin, OUTPUT);
//  pinMode(IN1, OUTPUT);
//  pinMode(IN2, OUTPUT);
//  pinMode(IN3, OUTPUT);
//  pinMode(IN4, OUTPUT);

  Serial1.begin(115200);

  Wire.begin();
  lightMeter.begin();
  motor.setSpeed(10);
}

void loop() {
  int newLight = lightMeter.readLightLevel();
//  Serial.println(newLight);

  if (newLight != light) {
    light = newLight;
    Serial1.println("light: " + String(light));
  }

  if (Serial1.available()) {
    String message = Serial1.readStringUntil('\n');
    if (message.startsWith("curtain:")) {
      curtain = message.substring(9).toInt();
      Serial1.println("curtain: " + String(curtain));
    } else if (message.startsWith("lamp:")) {
      lamp = message.substring(6);
      lamp.trim();
      if (lamp == "on") {
        Serial1.println("lamp: 1");
      } else {
        Serial1.println("lamp: 0");
      }
    }
  }

  if (curtainValue != curtain) {
    Serial.println("moving curtain");
    motor.setSpeed(10);
    motor.step((curtain - curtainValue) * steps_per_rev);
    curtainValue = curtain;
  }

  if (lamp == "on") {
    digitalWrite(lampPin, HIGH);
  } else {
    digitalWrite(lampPin, LOW);
  }
  
  delay(2000);
}
