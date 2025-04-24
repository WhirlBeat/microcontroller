#include <global.hpp>
#include "display.hpp"



void fill_spaces(int size, char* buffer) {
    memset((void*)buffer, ' ', size);
    buffer[size] = '\0';
}


namespace CustomChars {
    byte arrow_left[] = {
        B00001,
        B00011,
        B00111,
        B01111,
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
        B11110,
        B11100,
        B11000,
        B10000
    };
    const int ARROW_RIGHT = 1;

    byte action[] = {
        B00000,
        B00100,
        B01110,
        B11111,
        B11111,
        B01110,
        B00100,
        B00000
    };
    const int ACTION = 2;

    byte arrow_up[] = {
        B00000,
        B00000,
        B00100,
        B01110,
        B11111,
        B00000,
        B00000,
        B00000
    };
    const int ARROW_UP = 3;

    byte arrow_down[] = {
        B00000,
        B00000,
        B00000,
        B11111,
        B01110,
        B00100,
        B00000,
        B00000
    };
    const int ARROW_DOWN = 4;

    byte arrow_up_down[] = {
        B00100,
        B01110,
        B11111,
        B00000,
        B00000,
        B11111,
        B01110,
        B00100
    };
    const int ARROW_UP_DOWN = 5;
}


namespace Drivers {
    DisplayDriver::DisplayDriver(int size_x, int size_y, int address) : size_x(size_x), size_y(size_y), address(address) {}



    LCDDisplayDriver::LCDDisplayDriver(int size_x, int size_y, int address) :
        DisplayDriver(size_x, size_y), lcd(address, size_x, size_y)
    {
        for (int row_idx = 0; row_idx < MAX_SIZE_Y; row_idx++) {
            for (int col_idx = 0; col_idx < MAX_SIZE_X; col_idx++) {
                current_buffer[row_idx][col_idx] = ' ';
                current_buffer[row_idx][col_idx] = ' ';
            }
        }
    }


    void LCDDisplayDriver::begin() {
        lcd.init();
        lcd.backlight();

        lcd.createChar(CustomChars::ARROW_LEFT, CustomChars::arrow_left);
        lcd.createChar(CustomChars::ARROW_RIGHT, CustomChars::arrow_right);
        lcd.createChar(CustomChars::ACTION, CustomChars::action);
        lcd.createChar(CustomChars::ARROW_UP, CustomChars::arrow_up);
        lcd.createChar(CustomChars::ARROW_DOWN, CustomChars::arrow_down);
        lcd.createChar(CustomChars::ARROW_UP_DOWN, CustomChars::arrow_up_down);
    }

    void LCDDisplayDriver::render() {
        for (int row = 0; row < this->size_y; row++) {
            int col = 0;
            while (true) {
                if (col >= this->size_x) break;

                if (current_buffer[row][col] == previous_buffer[row][col]) {
                    col++;
                    continue;
                };

                int col_run_start = col;
                int col_run_end = col_run_start + 1;
                while (true) {
                    if (col_run_end >= this->size_x) break;
                    if (current_buffer[row][col_run_end] != previous_buffer[row][col_run_end]) {
                        col_run_end++;
                    } else {
                        break;
                    }
                }

                this->lcd.setCursor(col_run_start, row);
                for (int col_write = col_run_start; col_write < col_run_end; col_write++) {
                    lcd.write(current_buffer[row][col_write]);
                }
                col = col_run_end;
            }
        }

        for (int row = 0; row < this->size_y; row++) {
            for (int col = 0; col < this->size_x; col++) {
                previous_buffer[row][col] = current_buffer[row][col];
            }
        }
    }

    void LCDDisplayDriver::go_to(int x, int y) {
        this->cursor_x = x >= 0 ? x % this->size_x : this->size_x + x;
        this->cursor_y = y >= 0 ? y % this->size_y : this->size_y + y;
    }

    void LCDDisplayDriver::print_message(const char* message) {
        assert(message != nullptr);
        assert(strlen(message) <= this->size_x);

        int print_length = strlen(message);
        if (print_length > this->size_x) {
            print_length = this->size_x;
        }

        for (int i = 0; i < print_length; i++) {
            current_buffer[cursor_y][cursor_x + i] = message[i];
        }

        go_to(this->cursor_x + print_length, this->cursor_y);
    }

    void LCDDisplayDriver::print_custom_char(int char_id) {
        current_buffer[cursor_y][cursor_x] = char_id;
        go_to(this->cursor_x + 1, this->cursor_y);
    }


    void LCDDisplayDriver::print_at(int x, int y, const char* message) {
        this->go_to(x, y);
        this->print_message(message);
    }

    void LCDDisplayDriver::print_char_at(int x, int y, const int char_id) {
        go_to(x, y);
        print_custom_char(char_id);
    }

    void LCDDisplayDriver::print_center(int y, const char* message) {
        int x = (size_x - strlen(message)) / 2;
        print_at(x, y, message);
    }

    void LCDDisplayDriver::clear_all() {
        for (int row = 0; row < this->size_y; row++) {
            for (int col = 0; col < this->size_x; col++) {
                current_buffer[row][col] = ' ';
            }
        }
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

    void SerialDisplayDriver::render() {};

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