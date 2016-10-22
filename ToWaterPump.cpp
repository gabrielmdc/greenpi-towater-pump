/*
  ToWaterPump.cpp - Defines a pump to water
By Near lg, 14/08/2016
Lanzado bajo licencia BSD--- 
*/
#include "ToWaterPump.h"
//#include "../HumeditySensor/HumeditySensor.h"
//#include "../LoopCounter/LoopCounter.h"

ToWaterPump::ToWaterPump(int pin)
{
    _pin = pin;
    _runBySensor = false;
    _eachTime = 0;
    _duringTime = 0;
    _count = 0;
    _humeditySensor = NULL;
    _sensorDamagedCounter = 0;
}

void ToWaterPump::run() {
    // When the _count is 'blocked', then, can't run
    // If you want to run this, you have to put the _counter >= 0
    if(_count < 0){
        return;
    }
    if(_runBySensor && _humeditySensor != NULL) {
        if(LoopCounter::isNowEach(_eachTime, _count)){
            _humeditySensor->on();
            _humeditySensor->takeMeasure();
            _humeditySensor->off();
        } else if(_humeditySensor->getMeasure() >= 600) {
            _humeditySensor->on();
            _humeditySensor->takeMeasure();
        }
        if(_humeditySensor->getMeasure() >= 600){
            // to water
            digitalWrite(_pin, HIGH);
            if(_sensorDamagedCounter++ > MAX_DAMAGE) {
                _runBySensor = false;
                digitalWrite(_pin, LOW);
                _count = 0;
            }
        } else {
            _humeditySensor->off();
            digitalWrite(_pin, LOW);
        }
    } else {
        // To water by time
        if(_duringTime > 0) {
            switch(LoopCounter::getMomentEachDuring(_eachTime, _duringTime, _count)) {
                case 0:
                    digitalWrite(_pin, HIGH);
                    break;
                case 1:
                    digitalWrite(_pin, LOW);
                    if(_eachTime == 0) {
                        this->stop();
                    }
                    break;
            }
        }
    }
}

long ToWaterPump::getCount() {
    return _count;
}

void ToWaterPump::addToCount(long miliSec) {
    if(_count >= 0) {
        _count += miliSec;
    }
}

void ToWaterPump::start() {
    _count = 0;
}

void ToWaterPump::on() {
    _count = -1;
    digitalWrite(_pin, HIGH);
}

void ToWaterPump::stop() {
    _count = -1;
    digitalWrite(_pin, LOW);
}

void ToWaterPump::setHumeditySensor(HumeditySensor *sensor) {
    _humeditySensor = sensor;
}

HumeditySensor ToWaterPump::getHumeditySensor() {
    return *_humeditySensor;
}

void ToWaterPump::setDuringTime(long time) {
    _duringTime = time;
    _count = 0;
}

void ToWaterPump::setEachTime(long time){
    _eachTime = time;
    _count = 0;
}

void ToWaterPump::setRunBySensor(bool isRunBySensor){
    _runBySensor = isRunBySensor;
    _count = 0;
}

int ToWaterPump::getPin() {
    return _pin;
}

long ToWaterPump::getDuringTime(){
    return _duringTime;
}

long ToWaterPump::getEachTime(){
    return _eachTime;
}

bool ToWaterPump::isRunningBySensor(){
    return _runBySensor;
}
