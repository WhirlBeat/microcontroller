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

        const char* get_authorization_header();
        String get_full_url(String route);


        JsonDocument make_get_request(String url, JsonDocument query_params);
        JsonDocument get_table(String url, int load_count = -1, int center_on = -1);

        JsonDocument make_post_request(String url, JsonDocument body);
    };


    extern const char* timing_table_name;


    extern APIDriver api_driver;
}