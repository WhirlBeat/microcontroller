#include <Arduino.h>

#include "tps.hpp"


namespace Tools {
    void TPS::tick() {
        unsigned long current_millis = millis();
        unsigned long elapsed_millis = current_millis - previous_millis;

        Serial.print("Ticks per MS: ");
        Serial.println(elapsed_millis);
        previous_millis = current_millis;
    }
}