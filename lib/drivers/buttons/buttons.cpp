#include <Arduino.h>

#include "buttons.hpp"



namespace Drivers {
    ButtonDriver::ButtonDriver(int pin) : pin(pin) {
        pinMode(pin, INPUT_PULLUP);
    }

    void ButtonDriver::tick() {
        bool button_state = digitalRead(this->pin) == LOW;
        if (button_state) {
            this->held_state = true;
            this->on_held();
        }
        else {
            if (this->held_state) {
                this->on_release();
            }
            this->held_state = false;
        }
    }

    bool ButtonDriver::is_held() const {
        return held_state;
    }

    bool ButtonDriver::is_clicked() const {
        return clicked_state;
    }

    bool ButtonDriver::is_click_repeated(int repeat_rate, int before_delay) {
        if (ticks_since_press == 0) return false;

        if (ticks_since_press > before_delay) {
            return (ticks_since_press - before_delay) % repeat_rate == 0;
        } else {
            return false;
        }
    }

    void ButtonDriver::on_held() {
        ticks_since_press += 1;
        clicked_state = ticks_since_press == 1;
    }

    void ButtonDriver::on_release() {
        this->held_state = false;
        this->clicked_state = false;
        ticks_since_press = 0;
    }


    ButtonDriver button_driver_left{Pins::PIN_BUTTON_LEFT};
    ButtonDriver button_driver_action{Pins::PIN_BUTTON_ACTION};
    ButtonDriver button_driver_right{Pins::PIN_BUTTON_RIGHT};
}