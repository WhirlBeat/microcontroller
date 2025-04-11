#include <global.hpp>

#include "lights.hpp"



namespace Drivers {
    LEDStripLightsDriver<ComponentParams::LED_COUNT> ledstrip_lights_driver{
        ComponentParams::LED_BRIGHTNESS
    };
    LightsDriver<ComponentParams::LED_COUNT> &lights_driver = ledstrip_lights_driver;
} 