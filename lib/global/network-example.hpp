#pragma once

#include <Arduino.h>


// RENAME THIS FILE TO network.hpp TO USE


namespace Network {
    // Wifi information

    // The SSID of the network to connect to.
    const char* ssid = "YOUR_SSID";

    // The password of the network to connect to.
    const char* password = "YOUR_PASSWORD";


    // The base url for the API.
    const String base_url = "http://example.com/api";

    // The API key for authentication.
    const char* api_password = "YOUR_API_PASSWORD";
}