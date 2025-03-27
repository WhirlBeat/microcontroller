#include "lcd_display.hpp"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>



void fill_spaces(int size, char* buffer) {
    memset((void*)buffer, ' ', size);
    buffer[size] = '\0';
}

namespace LCD {
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



    Display::Display(int size_x, int size_y) : lcd(0x27, size_x, size_y) {
        this->size_x = size_x;
        this->size_y = size_y;
    }

    void Display::begin() {
        lcd.init();
        lcd.backlight();

        lcd.createChar(CustomChars::ARROW_LEFT, CustomChars::arrow_left);
        lcd.createChar(CustomChars::ARROW_RIGHT, CustomChars::arrow_right);
    }


    void Display::go_to(int x, int y) {
        int final_x = x >= 0 ? x : size_x + x;
        int final_y = y >= 0 ? y : size_y + y;

        lcd.setCursor(final_x, final_y);
    }


    void Display::print_at(int x, int y, const char* message) {
        go_to(x, y);
        lcd.print(message);
    }

    void Display::print_char_at(int x, int y, int char_id) {
        go_to(x, y);
        lcd.write(char_id);
    }

    void Display::clear() {
        lcd.clear();
    }

    void Display::print_center(int y, const char* message) {
        int x = (size_x - strlen(message)) / 2;
        print_at(x, y, message);
    }

    void Display::clear_row(int y) {
        char buffer[size_x + 1];
        fill_spaces(size_x, buffer);
        print_at(0, y, buffer);
    }

    void Display::clear_row_specific(int x, int y, int length_x) {
        char buffer[length_x + 1];
        fill_spaces(length_x, buffer);
        print_at(x, y, buffer);
    }
}
