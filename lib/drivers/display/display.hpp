#pragma once


#include <Arduino.h>
#include <LiquidCrystal_I2C.h>



namespace CustomChars {
    extern byte arrow_left[];
    extern const int ARROW_LEFT;

    extern byte arrow_right[];
    extern const int ARROW_RIGHT;

    extern byte arrow_up[];
    extern const int ARROW_UP;

    extern byte arrow_down[];
    extern const int ARROW_DOWN;

    extern byte arrow_up_down[];
    extern const int ARROW_UP_DOWN;
}

namespace Drivers {
    class DisplayDriver {
    public:
        int size_x;
        int size_y;
        int address;

        explicit DisplayDriver(int size_x = 20, int size_y = 4, int address = 0x27);

        virtual void begin() = 0;
        virtual void render() = 0;

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

        static const int MAX_SIZE_X = 30;
        static const int MAX_SIZE_Y = 10;

        char current_buffer[MAX_SIZE_Y][MAX_SIZE_X];
        char previous_buffer[MAX_SIZE_Y][MAX_SIZE_X];

        int cursor_x = 0;
        int cursor_y = 0;

        LCDDisplayDriver(int size_x = 20, int size_y = 4, int address = 0x27);

        void begin() override;
        void render() override;

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
        void render() override;

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