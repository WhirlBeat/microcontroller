#pragma once

#include <Vector.h>
#include <FastLED.h>

#include <global.hpp>


namespace Colors {
    const CRGB BLACK = CRGB(0, 0, 0);
    const CRGB WHITE = CRGB(255, 255, 255);

    const CRGB RED = CRGB(255, 0, 0);
    const CRGB ORANGE = CRGB(255, 165, 0);
    const CRGB YELLOW = CRGB(255, 255, 0);
    const CRGB GREEN = CRGB(0, 255, 0);
    const CRGB LIGHT_BLUE = CRGB(0, 255, 255);
    const CRGB BLUE = CRGB(0, 0, 255);
    const CRGB DARK_BLUE = CRGB(0, 0, 128);
    const CRGB PURPLE = CRGB(128, 0, 128);
}


namespace Drivers {
    template <unsigned int LightsCount>
    class LightsDriver {
    public:
        int lights_count;
        CRGB led_array[LightsCount];

        LightsDriver() : lights_count(LightsCount) {};

        virtual void show() = 0;
    };



    template <unsigned int LightsCount>
    class LEDStripLightsDriver : public LightsDriver<LightsCount> {
    public:
        LEDStripLightsDriver(int brightness = 128) : LightsDriver<LightsCount>() {
            FastLED.addLeds<WS2812B, Pins::PIN_LEDSTRIP_DATA, GRB>(this->led_array, LightsCount);
            FastLED.setBrightness(brightness);
        }

        void show() override {
            FastLED.show();
        }
    };



    extern LightsDriver<ComponentParams::LED_COUNT> &lights_driver;
}