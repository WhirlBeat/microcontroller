#include <Arduino.h>

#include "buzzer.hpp"



namespace Drivers {
    SoundDriver::SoundDriver(int pin) :
        pin(pin)
    {}

    void SoundDriver::play_tone(int pitch, int duration_ms) {
        tone(this->pin, pitch, duration_ms);
    }

    SoundDriver sound_driver{};
}