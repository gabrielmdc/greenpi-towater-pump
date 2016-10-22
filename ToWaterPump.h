/*
  ToWaterPump.h - Defines a pump to water
By Near lg, 14/08/2016
Lanzado bajo licencia BSD--- 
*/
#ifndef ToWaterPump_h
#define ToWaterPump_h
#include "Arduino.h"
#include "../HumeditySensor/HumeditySensor.h"
#include "../LoopCounter/LoopCounter.h"

#define MAX_DAMAGE 10

class ToWaterPump {
    public:
        ToWaterPump(int pin);
        void setDuringTime(long time);
        void setEachTime(long time);
        void setRunBySensor(bool isRunningBySensor);
        void setHumeditySensor(HumeditySensor *sensor);
        HumeditySensor getHumeditySensor();
        long getDuringTime();
        long getEachTime();
        int getPin();
        int getPhMax();
        int getPhMin();
        void addToCount(long miliSec);
        bool isRunningBySensor();
        void start();
        void run();
        void on();
        void stop();
        
        long getCount();
    private:
        bool _runBySensor;
        long _eachTime;
        long _duringTime;
        long _count;
        int _pin;
        int _sensorDamagedCounter;
        HumeditySensor *_humeditySensor = NULL;
};
#endif
