#include <HTTPClient.h>

#include <scoped_http.hpp>
#include "../display/display.hpp"

#include "api.hpp"



namespace Drivers {
    APIDriver::APIDriver(
        const String base_url,
        const char* api_password
    ) : base_url(base_url), api_password(api_password) {}


    void APIDriver::ensure_connection() {
        Serial.println("Ensuring connection to backend:");
        Serial.print("Base URL: ");
        Serial.println(this->base_url);
        Serial.print("API Password: ");
        Serial.println(this->api_password);
        Serial.println("");

        int tries = 1;
        while (true) {
            display_driver.clear_all();
            display_driver.print_center(0, "Connecting backend:");
            display_driver.print_center(1, this->base_url.substring(0, 20).c_str());
            display_driver.print_center(2, (String(tries) + " tries").c_str());

            ScopedHTTPClient scoped_http{NetworkParams::base_url + this->hello_route + "?password=" + this->api_password};
            int responseCode = scoped_http.client.GET();

            if (responseCode == HTTP_CODE_OK) {
                Serial.println("Connected.");
                break;
            }

            if (responseCode == HTTP_CODE_FORBIDDEN) {
                Serial.println("Forbidden. Wrong API password.");
            } else {
                Serial.print("Unknown error occurred. Status Code: ");
                Serial.println(responseCode);
            }

            display_driver.print_center(3, String(responseCode).c_str());

            tries++;
            delay(this->retry_after);
        }

        display_driver.clear_all();
    }

    void APIDriver::begin() {
        this->ensure_connection();
    }


    APIDriver api_driver{};
}