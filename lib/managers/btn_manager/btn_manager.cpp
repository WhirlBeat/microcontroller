#include <Arduino.h>
#include "btn_manager.hpp"


namespace BtnManager {
    Button::Button(int pin, int repeat_delay_ms) {
        pinMode(pin, INPUT_PULLUP);
        this->pin = pin;
        this->repeat_delay_ms = repeat_delay_ms;
    }

    void Button::on_tick() {
        bool is_pressed_now = digitalRead(this->pin) == LOW;
        if (is_pressed_now) {
            this->is_pressed = true;
            this->on_held();
        }
        else {
            if (this->is_pressed) {
                this->on_release();
            }
            this->is_pressed = false;
        }
    }

    void Button::on_held() {
        ticks_since_press += 1;
        is_clicked = ticks_since_press == 1;

        if (ticks_since_press > repeat_delay_ms) {
            is_held_repeated = true;
        } else {
            is_held_repeated = is_clicked;
        }
    }

    void Button::on_release() {
        this->is_pressed = false;
        this->is_clicked = false;
        this->is_held_repeated = false;
        ticks_since_press = 0;
    }
}