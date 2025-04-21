#pragma once

#include <global.hpp>



namespace Drivers {
    class NetworkDriver {
    public:
        const char* ssid;
        const char* password;

        const int retry_after = 500;
        const int retry_count = 10;

        NetworkDriver(
            const char* ssid = NetworkParams::ssid,
            const char* password = NetworkParams::password
        );

        bool is_connected();

        bool begin();
    };


    extern NetworkDriver network_driver;
}