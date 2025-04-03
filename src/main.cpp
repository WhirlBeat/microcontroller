#include <Arduino.h>

#include <managers.hpp>
#include <pins.hpp>
#include "../lib/scene/scene.hpp"


ShiftRegister::LEDControl led_control(PIN_SHIFT_DATA, PIN_SHIFT_CLOCK, PIN_SHIFT_LATCH);

// LCD is always on pins A4 and A5
LCD::Display lcd_display{};


SceneSources::MainMenu main_menu = SceneSources::MainMenu(lcd_display);
Scene::Source& main_menu_ref = main_menu;
Scene::Loader scene_loader(main_menu_ref);

void setup() {
    Serial.begin(9600);
    lcd_display.begin();
}

byte beans = 1;
BtnManager::Button button(PIN_BTN_ACTION);

void loop() {
    scene_loader.on_tick();

    led_control.write(beans);

    button.on_tick();
    if (button.is_clicked) beans = beans << 1;

    if (beans == 0) beans = 1;
    delay(1);
}