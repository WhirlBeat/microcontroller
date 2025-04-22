#pragma once

#include <global.hpp>



namespace Drivers {
    class APIDriver {
    public:
        const String base_url;
        const char* api_password;

        const String hello_route = "/hello";

        const int retry_after = 1000;

        APIDriver(
            const String base_url = NetworkParams::base_url,
            const char* api_password = NetworkParams::api_password
        );


        void ensure_connection();

        void begin();
    };


    extern APIDriver api_driver;
}