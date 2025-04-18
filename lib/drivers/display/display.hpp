#pragma once


#include <Arduino.h>
#include <LiquidCrystal_I2C.h>



namespace CustomChars {
    extern byte arrow_left[];
    extern const int ARROW_LEFT;

    extern byte arrow_right[];
    extern const int ARROW_RIGHT;
}

namespace Drivers {
    class DisplayDriver {
    public:
        int size_x;
        int size_y;
        int address;

        explicit DisplayDriver(int size_x = 20, int size_y = 4, int address = 0x27);

        virtual void begin() = 0;

        virtual void go_to(int x, int y) = 0;
        virtual void print_message(const char* message) = 0;
        virtual void print_custom_char(int char_id) = 0;

        virtual void print_at(int x, int y, const char* message) = 0;
        virtual void print_char_at(int x, int y, const int char_id) = 0;

        virtual void print_center(int y, const char* message) = 0;

        virtual void clear_all() = 0;
        virtual void clear_row(int y) = 0;
        virtual void clear_specific(int x, int y, int size_x) = 0;
    };


    class LCDDisplayDriver : public DisplayDriver {
    public:
        LiquidCrystal_I2C lcd;

        explicit LCDDisplayDriver(int size_x = 20, int size_y = 4, int address = 0x27);

        void begin() override;

        void go_to(int x, int y) override;
        void print_message(const char* message) override;
        void print_custom_char(int char_id) override;

        void print_at(int x, int y, const char* message) override;
        void print_char_at(int x, int y, const int char_id) override;

        void print_center(int y, const char* message) override;

        void clear_all() override;
        void clear_row(int y) override;
        void clear_specific(int x, int y, int size_x) override;
    };


    class SerialDisplayDriver : public DisplayDriver {
    public:
        SerialDisplayDriver();

        void begin() override;

        void go_to(int x, int y) override;
        void print_message(const char* message) override;
        void print_custom_char(int char_id) override;

        void print_at(int x, int y, const char* message) override;
        void print_char_at(int x, int y, const int char_id) override;

        void print_center(int y, const char* message) override;

        void clear_all() override;
        void clear_row(int y) override;
        void clear_specific(int x, int y, int size_x) override;
    };



    extern DisplayDriver &display_driver;
}