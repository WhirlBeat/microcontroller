#include <Arduino.h>

#include <drivers.hpp>
#include <engine.hpp>
#include <tools.hpp>
#include <colors.hpp>



Engine::OneTimingScene scene{};

Engine::SceneLoader scene_loader{scene};

Tools::TPS tps;


void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW); // apparently LOW = on for esp8266 lmao

    Serial.begin(115200);
    Drivers::display_driver.begin();
    Drivers::lights_driver.show();
    delay(5000);


    digitalWrite(LED_BUILTIN, HIGH);
}

uint8_t a = 0;

void loop() {
    scene_loader.tick();
    tps.tick();

    delay(1);
}