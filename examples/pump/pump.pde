#include <HumeditySensor.h>
#include <LoopCounter.h>
#include <ToWaterPump.h>

ToWaterPump pump1(4);

void setup() {
  pinMode(4, OUTPUT);
    Serial.begin(9600);
    //pump1.setHumeditySensor(HumeditySensor sensor)
    pump1.setDuringTime(2000);
    pump1.setEachTime(5000);
    pump1.setRunBySensor(false);
}


void loop() {
  myDelay(1000);
  pump1.run();
  if(digitalRead(4) == HIGH) {
        Serial.println("Pump working");
    } else {
        Serial.println("Pump NOT working");
    }
}

void myDelay(long miliSec) {
    delay(miliSec);
    pump1.addToCount(miliSec);
}
