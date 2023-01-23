#pragma once

#include "Arduino.h"

class WeatherData
{
    uint64_t dt_;
    int8_t temp_;
    int8_t humidity_;
    int8_t pop_;

    public:

    WeatherData* dt(uint64_t dt){
        this->dt_ = dt;
        return this;
    }
    uint64_t dt(){
        return this->dt_;
    }

    WeatherData* temp(int8_t temp){
        this->temp_ = temp;
        return this;
    }
    int8_t temp(){
        return this->temp_;
    }

    WeatherData* humidity(int8_t hum){
        this->humidity_ = hum;
        return this;
    }
    int8_t humidity(){
        return this->humidity_;
    }

    WeatherData* pop(int8_t pop){
        this->pop_ = pop;
        return this;
    }
    int8_t pop(){
        return this->pop_;
    }
};