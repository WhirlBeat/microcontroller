#pragma once

#include <ArduinoJson.h>

#include <global.hpp>



namespace Drivers {
    class APIDriver {
    public:
        const String base_url;
        const char* api_password;

        const String hello_route = "/hello";
        const String scores_route = "/scores";

        const int retry_after = 1000;

        APIDriver(
            const String base_url = NetworkParams::base_url,
            const char* api_password = NetworkParams::api_password
        );


        void ensure_connection();

        void begin();


        JsonDocument get_table(const char* table_name, int load_count = -1, int center_on = -1);
    };


    extern const char* timing_table_name;


    extern APIDriver api_driver;
}