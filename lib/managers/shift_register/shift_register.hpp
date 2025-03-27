#pragma once

#include <Arduino.h>

namespace ShiftRegister {
    class LEDControl {
    public:
        int data_pin;
        int clock_pin;
        int latch_pin;

        LEDControl(int data_pin, int clock_pin, int latch_pin);
        void start();
        
        void write(byte value);
    };
}