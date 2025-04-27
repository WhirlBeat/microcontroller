#pragma once

#include <global.hpp>



namespace Drivers {
    class SoundDriver {
    public:
        const int pin;

        SoundDriver(int pin = Pins::PIN_BUZZER);

        void play_tone(int freq, int duration_ms);
    };

    extern SoundDriver sound_driver;
}