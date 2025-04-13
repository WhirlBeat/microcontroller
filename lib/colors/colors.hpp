#pragma once

#include <FastLED.h>


uint8_t percent_to_byte(float percent) {
    return (uint8_t)floor(percent / 100.0F * 255);
}


DEFINE_GRADIENT_PALETTE(rainbow_gp) {
    percent_to_byte(0), 255, 0, 0,
    percent_to_byte(10), 255, 154, 0,
    percent_to_byte(20), 208, 222, 33,
    percent_to_byte(30), 79, 220, 74,
    percent_to_byte(40), 63, 218, 216,
    percent_to_byte(50), 47, 201, 226,
    percent_to_byte(60), 28, 127, 238,
    percent_to_byte(70), 95, 21, 242,
    percent_to_byte(80), 186, 12, 248,
    percent_to_byte(90), 251, 7, 217,
    percent_to_byte(100), 255, 0, 0
};


DEFINE_GRADIENT_PALETTE(timing_gp) {
    percent_to_byte(0), 0, 0, 255,
    percent_to_byte(25), 255, 0, 0,
    percent_to_byte(50), 255, 165, 0,
    percent_to_byte(75), 0, 255, 0,
    percent_to_byte(100), 255, 255, 255,
};


namespace Gradients {
    CRGBPalette16 rainbow_palette = rainbow_gp;
    CRGBPalette16 timing_palette = timing_gp;
}