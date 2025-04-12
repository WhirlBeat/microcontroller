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
        const int lights_count;
        CRGB led_array[LightsCount];

        LightsDriver() : lights_count(LightsCount) {};

        void clear_led_array() {
            for (int idx = 0; idx < this->lights_count; idx++) {
                this->led_array[idx] = Colors::BLACK;
            }
        }

        virtual void show() = 0;
    };



    template <unsigned int LightsCount>
    class LEDStripLightsDriver : public LightsDriver<LightsCount> {
    public:
        int brightness;

        LEDStripLightsDriver(int brightness = 128) : LightsDriver<LightsCount>(), brightness(brightness) {
            FastLED.addLeds<WS2812B, Pins::PIN_LEDSTRIP_DATA, GRB>(this->led_array, LightsCount);
            FastLED.setBrightness(this->brightness);
        }

        void show() override {
            FastLED.setBrightness(this->brightness);
            FastLED.show();
        }
    };



    extern LightsDriver<ComponentParams::LED_COUNT> &lights_driver;
}