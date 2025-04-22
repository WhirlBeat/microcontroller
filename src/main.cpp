#include <Arduino.h>

#include <drivers.hpp>
#include <engine.hpp>
#include <tools.hpp>
#include <colors.hpp>



Engine::LeaderboardScene scene{Drivers::timing_table_name, 10, 3};

Engine::SceneLoader scene_loader{&scene};

Tools::TPS tps;


void setup() {
    Drivers::display_driver.begin();
    Drivers::lights_driver.show();

    Serial.begin(115200);
    while (!Serial) delay(100);

    Drivers::api_driver.begin();
}

void loop() {
    scene_loader.tick();
    // tps.tick();

    delay(1);
}


// #include <WiFi.h>
// #include <HTTPClient.h>


// void setup() {
//     Serial.begin(115200); 

//     Drivers::network_driver.begin();
// }

// void loop() {
//     if (WiFi.status() != WL_CONNECTED) {
//         Serial.println("WiFi not connected, reconnecting...");
//         WiFi.disconnect();
//         WiFi.begin(NetworkParams::ssid, NetworkParams::password);
//         while(WiFi.status() != WL_CONNECTED) {
//             delay(500);
//             Serial.print(".");
//         }
//     }

//     HTTPClient http;
//     http.begin((NetworkParams::base_url + "/hello").c_str());

//     int httpResponseCode = http.GET();
//     String payload = http.getString();
//     Serial.println(payload);

//     http.end();

//     Serial.println("Connected.");
//     delay(5000);
// }