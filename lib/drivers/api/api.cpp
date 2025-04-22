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



    JsonDocument APIDriver::get_table(const char* table_name, int load_count, int center_on) {
        this->ensure_connection();

        String result_url = NetworkParams::base_url + this->scores_route + "?tableName=" + table_name;
        if (load_count > 0) {
            result_url += "&loadCount=" + String(load_count);
        }

        if (center_on > 0) {
            result_url += "&centerOn=" + String(center_on);
        }

        int responseCode = HTTP_CODE_CONTINUE;

        String response_str;
        while (true) {
            Serial.println("Attempting to get table from URL: " + result_url);

            ScopedHTTPClient scoped_http{result_url};
            int response_code = scoped_http.client.GET();

            if (response_code == HTTP_CODE_OK) {
                response_str = scoped_http.client.getString();
                break;
            }

            Serial.println("Error occurred. Status Code: " + String(response_code));
            Serial.println("Response body: " + scoped_http.client.getString());
            delay(this->retry_after);
        }

        Serial.println("Finished.");
        Serial.println(response_str);

        JsonDocument response;
        deserializeJson(response, response_str);
        return response["moreInfo"];
    }

    JsonDocument APIDriver::post_score(const char* table_name, const char* username, int score) {
        this->ensure_connection();
        String result_url = NetworkParams::base_url + this->scores_route;

        JsonDocument request;
        request["tableName"] = table_name;
        request["username"] = username;
        request["score"] = score;
        request["password"] = this->api_password;

        String request_str;
        serializeJson(request, request_str);

        String response_str;
        while (true) {
            Serial.println("Attempting to post score to URL: " + result_url);
            Serial.println("Request body: " + request_str);

            ScopedHTTPClient scoped_http{result_url};
            scoped_http.client.addHeader("Content-Type", "application/json");

            int response_code = scoped_http.client.POST(request_str.c_str());

            if (response_code == HTTP_CODE_OK) {
                response_str = scoped_http.client.getString();
                break;
            }

            Serial.println("Error occurred. Status Code: " + String(response_code));
            Serial.println("Response body: " + scoped_http.client.getString());
            delay(this->retry_after);
        }

        JsonDocument response;
        deserializeJson(response, response_str);
        return response["moreInfo"];
    }

    const char* timing_table_name = "timing";

    APIDriver api_driver{};
}