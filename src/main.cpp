#include <Arduino.h>

#include <drivers.hpp>
#include <engine.hpp>





Engine::MainMenuScene scene{};

Engine::SceneLoader scene_loader{scene};


void setup() {
    Serial.begin(115200);
    delay(5000);

    Drivers::display_driver.begin();
}

void loop() {
    scene_loader.tick();
    delay(1);
}