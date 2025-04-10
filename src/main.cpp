#include <Arduino.h>

#include <managers.hpp>
#include <pins.hpp>
#include "../lib/scene/scene.hpp"


ShiftRegister::LEDControl led_control(PIN_SHIFT_DATA, PIN_SHIFT_CLOCK, PIN_SHIFT_LATCH);

// LCD is always on pins A4 and A5
LCD::Display lcd_display{};


SceneSources::MainMenu main_menu = SceneSources::MainMenu(lcd_display);
Scene::Source& main_menu_ref = main_menu;

SceneSources::Timing timing(lcd_display, led_control);
Scene::Loader scene_loader(timing);


void setup() {
    Serial.begin(9600);
    delay(5000);
    lcd_display.begin();
}

void loop() {
    scene_loader.on_tick();
    delay(1);
}