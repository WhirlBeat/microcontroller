#include <HTTPClient.h>

#include <scoped_http.hpp>
#include "../display/display.hpp"
#include "../network/network.hpp"

#include "api.hpp"



namespace Drivers {
    APIDriver::APIDriver(
        const String base_url,
        const char* api_password
    ) : base_url(base_url), api_password(api_password) {}


    void APIDriver::ensure_connection() {
        network_driver.ensure_connection();

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

            String tries_str = String(tries) + " tries";
            display_driver.print_center(2, tries_str.c_str());
            display_driver.render();

            ScopedHTTPClient scoped_http{NetworkParams::base_url + this->hello_route};
            scoped_http.client.addHeader("Authorization", this->get_authorization_header());

            int response_code = scoped_http.client.GET();

            if (response_code == HTTP_CODE_OK) {
                Serial.println("Connected.");
                break;
            }

            if (response_code == HTTP_CODE_FORBIDDEN) {
                Serial.println("Forbidden. Wrong API password.");
            } else {
                Serial.print("Unknown error occurred. Status Code: ");
                Serial.println(response_code);
            }

            String response_code_str = String(response_code);
            display_driver.print_center(3, response_code_str.c_str());
            display_driver.render();

            tries++;
            delay(this->retry_after);
        }

        display_driver.clear_all();
        display_driver.render();
    }

    void APIDriver::begin() {
        this->ensure_connection();
    }

    const char* APIDriver::get_authorization_header() {
        String result = String("Bearer ") + this->api_password;
        return result.c_str();
    }

    JsonDocument APIDriver::get_table(String route, int load_count, int center_on) {
        JsonDocument query_params;

        if (load_count != -1) {
            query_params["load_count"] = load_count;
        }
        if (center_on != -1) {
            query_params["center_on"] = center_on;
        }

        return this->make_get_request(route, query_params);
    }

    JsonDocument APIDriver::make_get_request(String route, JsonDocument query_params) {
        this->ensure_connection();

        String url = this->get_full_url(route);

        JsonObject obj = query_params.as<JsonObject>();
        int idx = 0;
        for (JsonPair kv : obj) {
            String key = kv.key().c_str();
            String value = kv.value().as<String>();
            url += (idx == 0 ? "?" : "&") + key + "=" + value;

            idx++;
        }

        String response_str;
        Drivers::display_driver.clear_all();
        while (true) {
            Serial.println("Attempting to GET from URL: " + url);
            Drivers::display_driver.clear_row(0);
            Drivers::display_driver.print_center(0, "Fetching...");
            Drivers::display_driver.render();

            ScopedHTTPClient scoped_http{url};
            int response_code = scoped_http.client.GET();

            if (response_code == HTTP_CODE_OK) {
                response_str = scoped_http.client.getString();
                break;
            }

            Serial.println("Error occurred. Status Code: " + String(response_code));
            Serial.println("Response body: " + scoped_http.client.getString());
            Drivers::display_driver.clear_row(0);
            Drivers::display_driver.print_center(0, "Error! Retrying...");
            Drivers::display_driver.render();
            delay(this->retry_after);
        }

        Serial.println("Response body: " + response_str);

        JsonDocument response;
        deserializeJson(response, response_str);
        return response;
    }

    String APIDriver::get_full_url(String route) {
        return this->base_url + route;
    }

    JsonDocument APIDriver::make_post_request(String route, JsonDocument body) {
        this->ensure_connection();

        String url = this->get_full_url(route);

        String request_str;
        serializeJson(body, request_str);

        String response_str;
        Drivers::display_driver.clear_all();
        while (true) {
            Serial.println("Attempting to post score to URL: " + url);
            Serial.println("Request body: " + request_str);
            Drivers::display_driver.clear_row(0);
            Drivers::display_driver.print_center(0, "Posting...");
            Drivers::display_driver.render();

            ScopedHTTPClient scoped_http{url};
            scoped_http.client.addHeader("Content-Type", "application/json");
            scoped_http.client.addHeader("Authorization", this->get_authorization_header());

            int response_code = scoped_http.client.POST(request_str.c_str());

            if (response_code == HTTP_CODE_OK) {
                response_str = scoped_http.client.getString();
                break;
            }

            Serial.println("Error occurred. Status Code: " + String(response_code));
            Serial.println("Response body: " + scoped_http.client.getString());
            Drivers::display_driver.clear_row(0);
            Drivers::display_driver.print_center(0, "Error! Retrying...");
            Drivers::display_driver.render();
            delay(this->retry_after);
        }

        Serial.println("Response body: " + response_str);

        JsonDocument response;
        deserializeJson(response, response_str);
        return response;
    }

    const char* timing_table_route = "/scores/timing";

    APIDriver api_driver{};
}