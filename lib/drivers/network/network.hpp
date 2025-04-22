#pragma once

#include <global.hpp>



namespace Drivers {
    class NetworkDriver {
    public:
        const char* ssid;
        const char* password;

        const int retry_after = 500;

        NetworkDriver(
            const char* ssid = NetworkParams::ssid,
            const char* password = NetworkParams::password
        );

        void ensure_connection();

        void begin();
    };


    extern NetworkDriver network_driver;
}