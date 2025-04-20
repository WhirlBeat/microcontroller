#include <Arduino.h>

#include <drivers.hpp>
#include <engine.hpp>
#include <tools.hpp>
#include <colors.hpp>



Engine::TimingModePlayScene scene{};

Engine::SceneLoader scene_loader{scene};

Tools::TPS tps;


void setup() {
    Drivers::display_driver.begin();
    Drivers::lights_driver.show();

    Serial.begin(115200);
    while (!Serial) delay(100);
}

void loop() {
    scene_loader.tick();
    tps.tick();

    delay(1);
}