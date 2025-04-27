#pragma once

#include <global.hpp>



namespace Drivers {
    class BuzzerDriver {
    public:
        const int pin;

        BuzzerDriver(int pin = Pins::PIN_BUZZER);

        void play_tone(int freq, int duration_ms);
    };

    extern BuzzerDriver buzzer_driver;
}