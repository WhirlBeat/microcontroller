#include <Arduino.h>

#include "buzzer.hpp"



namespace Drivers {
    BuzzerDriver::BuzzerDriver(int pin) :
        pin(pin)
    {}

    void BuzzerDriver::play_tone(int pitch, int duration_ms) {
        tone(this->pin, pitch, duration_ms);
    }

    BuzzerDriver buzzer_driver{};
}