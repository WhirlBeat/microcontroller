#include <WiFi.h>

#include "network.hpp"



namespace Drivers {
    NetworkDriver::NetworkDriver(
        const char* ssid,
        const char* password
    ) : ssid(ssid), password(password) {}

    bool NetworkDriver::is_connected() {
        return WiFi.status() == WL_CONNECTED;
    }

    bool NetworkDriver::begin() {
        WiFi.begin(NetworkParams::ssid, NetworkParams::password);
        Serial.println("Connecting");

        bool limit_reached = true;
        for (int retry_idx = 0; retry_idx < this->retry_count; retry_idx++) {
            Serial.print("Try #");
            Serial.print(retry_idx + 1);
            Serial.print(" of ");
            Serial.print(this->retry_count);
            Serial.print("... ");

            delay(this->retry_after);

            if (this->is_connected()) {
                limit_reached = false;
                break;
            }
        }

        Serial.println("");

        if (limit_reached) {
            Serial.println("Failed to connect to WiFi network.");
            return false;
        };


        Serial.print("Connected to WiFi network with IP Address: ");
        Serial.println(WiFi.localIP());

        return true;
    }

    NetworkDriver network_driver{};
}