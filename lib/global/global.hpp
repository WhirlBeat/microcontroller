#pragma once

#include <Arduino.h>



namespace ComponentParams {
    const int LED_COUNT = 144;
    const int LED_BRIGHTNESS = 64;

    const int LCD_DISPLAY_X = 20;
    const int LCD_DISPLAY_Y = 4;
    const int LCD_DISPLAY_ADDRESS = 0x27;

    const int DF_PLAYER_VOLUME = 15;
}


namespace Pins {
    const int PIN_BUTTON_LEFT = 27;
    const int PIN_BUTTON_ACTION = 26;
    const int PIN_BUTTON_RIGHT = 25;

    const int PIN_LEDSTRIP_DATA = 23;

    const int PIN_BUZZER = 19;
}



namespace NetworkParams {
    extern const char* ssid;
    extern const char* password;

    extern const String base_url;
    extern const char* api_password;
}