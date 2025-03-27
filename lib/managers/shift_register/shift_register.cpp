#include "shift_register.hpp"

namespace ShiftRegister {
    LEDControl::LEDControl(int data_pin, int clock_pin, int latch_pin) {
        this->data_pin = data_pin;
        pinMode(data_pin, OUTPUT);

        this->clock_pin = clock_pin;
        pinMode(clock_pin, OUTPUT);
        
        this->latch_pin = latch_pin;
        pinMode(latch_pin, OUTPUT);
    }

    void LEDControl::start() {
        write(0);
    }

    void LEDControl::write(byte value) {
        digitalWrite(latch_pin, LOW);
        shiftOut(data_pin, clock_pin, MSBFIRST, value);
        digitalWrite(latch_pin, HIGH);
    }
}