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

    Drivers::display_driver.begin();
    Drivers::lights_driver.show();

    Serial.begin(115200);
    while (!Serial) delay(100);


    digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
    scene_loader.tick();
    tps.tick();

    delay(1);
}