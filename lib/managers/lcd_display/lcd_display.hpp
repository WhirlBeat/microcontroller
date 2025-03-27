#pragma once

#include <LiquidCrystal_I2C.h>
#include <Arduino.h>


namespace LCD {
    namespace CustomChars {
        extern byte arrow_left[];
        extern const int ARROW_LEFT;
        
        extern byte arrow_right[];
        extern const int ARROW_RIGHT;
    }

    class Display {
    public:
        LiquidCrystal_I2C lcd;
        int size_x;
        int size_y;

        explicit Display(int size_x = 16, int size_y = 2);

        void begin();

        void go_to(int x, int y);

        void print_at(int x, int y, const char* message);
        void print_char_at(int x, int y, int char_id);
        void clear();

        void print_center(int y, const char* message);

        void clear_row(int y);
        void clear_row_specific(int x, int y, int size_x);
    };
}