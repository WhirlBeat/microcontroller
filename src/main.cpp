#include <Arduino.h>

#include <drivers.hpp>
#include <engine.hpp>
#include <tools.hpp>
#include <colors.hpp>



Engine::TimingModeModSelectScene scene{};

Tools::TPS tps;


void setup() {
    Drivers::display_driver.begin();
    Drivers::lights_driver.show();

    Serial.begin(115200);
    while (!Serial) delay(100);

    Drivers::api_driver.begin();

    Drivers::button_driver_action.tick();
    if (Drivers::button_driver_action.is_held()) {
        Drivers::display_driver.print_center(0, "Boot stopped.");
        Drivers::display_driver.print_center(1, "Reset power");
        Drivers::display_driver.print_center(2, "to boot again.");

        Drivers::display_driver.render();

        while (true) { delay(10000); }
    }

    scene.init();
    Engine::scene_loader.switch_scene(&scene);
}

void loop() {
    Engine::scene_loader.tick();
    // tps.tick();

    delay(1);
}