#include <Arduino.h>
#include <LightSensor.h>
#include <LightSensorController.h>

LightSensorController lights;

void setup() {
  Serial.begin(9600);
  lights.setup();
}

void loop() {
  lights.update();
}