#include <WiFi.h>

#include "../display/display.hpp"

#include "network.hpp"



namespace Drivers {
    NetworkDriver::NetworkDriver(
        const char* ssid,
        const char* password
    ) : ssid(ssid), password(password) {}

    void NetworkDriver::ensure_connection() {
        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("Already connected to WiFi.");
            return;
        }

        Serial.println("Ensuring connection to WiFi:");
        Serial.print("SSID: ");
        Serial.println(this->ssid);
        Serial.print("Password: ");
        Serial.println(this->password);
        Serial.println("");

        int tries = 1;
        while (true) {
            display_driver.clear_all();
            display_driver.print_center(0, "Connecting to WiFi:");
            display_driver.print_center(1, ssid);
            display_driver.print_center(2, (String(tries) + " tries").c_str());
            display_driver.render();

            WiFi.begin(NetworkParams::ssid, NetworkParams::password);
            while (
                WiFi.status() != WL_CONNECTED &&
                WiFi.status() != WL_CONNECT_FAILED &&
                WiFi.status() != WL_CONNECTION_LOST
            ) {
                Serial.print("Idle status: ");
                Serial.println(WiFi.status());
                delay(100);
            }

            Serial.print("Finished status: ");
            Serial.println(WiFi.status());

            if (WiFi.status() == WL_CONNECTED) {
                Serial.println("Connected!");
                break;
            }

            display_driver.print_center(3, String(WiFi.status()).c_str());
            display_driver.render();

            tries++;
            delay(this->retry_after);
            Serial.println("Reconnecting...");
        };

        display_driver.clear_all();
        display_driver.render();
    }

    void NetworkDriver::begin() {
        this->ensure_connection();

        Serial.println("");
        Serial.print("Connected to WiFi network with IP Address: ");
        Serial.println(WiFi.localIP());
    }

    NetworkDriver network_driver{};
}