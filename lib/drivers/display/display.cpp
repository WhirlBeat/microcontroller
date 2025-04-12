#include <global.hpp>
#include "display.hpp"



void fill_spaces(int size, char* buffer) {
    memset((void*)buffer, ' ', size);
    buffer[size] = '\0';
}


namespace CustomChars {
    byte arrow_left[] = {
        B11111,
        B00001,
        B00011,
        B00111,
        B01111,
        B00111,
        B00011,
        B00001
    };
    const int ARROW_LEFT = 0;

    byte arrow_right[] = {
        B10000,
        B11000,
        B11100,
        B11110,
        B11100,
        B11000,
        B10000,
        B11111
    };
    const int ARROW_RIGHT = 1;
}


namespace Drivers {
    DisplayDriver::DisplayDriver(int size_x, int size_y, int address) : size_x(size_x), size_y(size_y), address(address) {}



    LCDDisplayDriver::LCDDisplayDriver(int size_x, int size_y, int address) :
        DisplayDriver(size_x, size_y), lcd(address, size_x, size_y)
    {}


    void LCDDisplayDriver::begin() {
        lcd.init();
        lcd.backlight();

        lcd.createChar(CustomChars::ARROW_LEFT, CustomChars::arrow_left);
        lcd.createChar(CustomChars::ARROW_RIGHT, CustomChars::arrow_right);
    }

    void LCDDisplayDriver::go_to(int x, int y) {
        int final_x = x >= 0 ? x : size_x + x;
        int final_y = y >= 0 ? y : size_y + y;

        lcd.setCursor(final_x, final_y);
    }

    void LCDDisplayDriver::print_message(const char* message) {
        lcd.print(message);
    }

    void LCDDisplayDriver::print_custom_char(int char_id) {
        lcd.write(char_id);
    }


    void LCDDisplayDriver::print_at(int x, int y, const char* message) {
        this->go_to(x, y);
        this->print_message(message);
    }

    void LCDDisplayDriver::print_char_at(int x, int y, const int char_id) {
        go_to(x, y);
        lcd.write(char_id);
    }

    void LCDDisplayDriver::print_center(int y, const char* message) {
        int x = (size_x - strlen(message)) / 2;
        print_at(x, y, message);
    }

    void LCDDisplayDriver::clear_all() {
        lcd.clear();
    }

    void LCDDisplayDriver::clear_row(int y) {
        char buffer[size_x + 1];
        fill_spaces(size_x, buffer);
        print_at(0, y, buffer);
    }

    void LCDDisplayDriver::clear_specific(int x, int y, int length_x) {
        char buffer[length_x + 1];
        fill_spaces(length_x, buffer);
        print_at(x, y, buffer);
    }



    SerialDisplayDriver::SerialDisplayDriver() : DisplayDriver() {}

    void SerialDisplayDriver::begin() {
        Serial.println("Started display");
    }

    void SerialDisplayDriver::go_to(int x, int y) {
        Serial.print("-- go to");
        Serial.print(x);
        Serial.print(", ");
        Serial.println(y);
        Serial.println(".");
    }

    void SerialDisplayDriver::print_message(const char* message) {
        Serial.println(message);
    }

    void SerialDisplayDriver::print_custom_char(int char_id) {
        Serial.println(char_id);
    }

    void SerialDisplayDriver::print_at(int x, int y, const char* message) {
        Serial.print("--at ");
        Serial.print(x);
        Serial.print(", ");
        Serial.print(y);
        Serial.print(": ");
        Serial.println(message);
    }

    void SerialDisplayDriver::print_char_at(int x, int y, const int char_id) {
        Serial.print("--char at ");
        Serial.print(x);
        Serial.print(", ");
        Serial.print(y);
        Serial.print(": ");
        Serial.println(char_id);
    }

    void SerialDisplayDriver::print_center(int y, const char* message) {
        Serial.print("--center ");
        Serial.print(y);
        Serial.print(": ");
        Serial.println(message);
    }

    void SerialDisplayDriver::clear_all() {
        Serial.println("--clear all");
    }

    void SerialDisplayDriver::clear_row(int y) {
        Serial.print("--clear row ");
        Serial.println(y);
    }

    void SerialDisplayDriver::clear_specific(int x, int y, int size_x) {
        Serial.print("--clear specific ");
        Serial.print(x);
        Serial.print(", ");
        Serial.print(y);
        Serial.print(", ");
        Serial.println(size_x);
    }



    LCDDisplayDriver lcd_display_driver{
        ComponentParams::LCD_DISPLAY_X, ComponentParams::LCD_DISPLAY_Y,
        ComponentParams::LCD_DISPLAY_ADDRESS
    };
    SerialDisplayDriver serial_display_driver{};

    DisplayDriver &display_driver = lcd_display_driver;
}