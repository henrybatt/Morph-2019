#include <Arduino.h>
#include <tssp.h>
#include <Timer.h>

Tssp tssps;

Timer tsspTimer(833 * TSSP_TIMER_PERIOD_NUMBER);


void setup() {
  Serial.begin(9600);
  Serial.println("Setup"); 
  tssps.init();
}

void loop() {
  tssps.updateOnce();
  // Serial.println("LOOP");
  if (tsspTimer.timeHasPassed()){
    tssps.finishRead();


    tsspTimer.resetTime();
  }
  // Serial.println((uint16_t)tssps.getAngle());
}