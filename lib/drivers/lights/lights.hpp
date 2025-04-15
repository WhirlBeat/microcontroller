#pragma once

#include <FastLED.h>

#include <global.hpp>



namespace Drivers {
    template <unsigned int LightsCount>
    class LightsDriver {
    public:
        const int lights_count;
        CRGB led_array[LightsCount];

        LightsDriver() : lights_count(LightsCount) {};

        void clear_led_array() {
            for (int idx = 0; idx < this->lights_count; idx++) {
                this->led_array[idx] = CRGB::Black;
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
            FastLED.setMaxRefreshRate(0);
            FastLED.setBrightness(this->brightness);
        }

        void show() override {
            FastLED.setBrightness(this->brightness);
            FastLED.show();
        }
    };



    extern LightsDriver<ComponentParams::LED_COUNT> &lights_driver;
}