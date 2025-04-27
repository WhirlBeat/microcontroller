#include <Arduino.h>
#include <pitch.hpp>

#include "../buzzer/buzzer.hpp"

#include "buttons.hpp"



namespace Drivers {
    ButtonDriver::ButtonDriver(int pin, int pitch) : pin(pin), pitch(pitch) {
        this->set_pin_mode(pin);
    }

    bool ButtonDriver::read_value() {
        return digitalRead(this->pin) == LOW;
    }

    void ButtonDriver::tick() {
        bool button_state = this->read_value();

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

    bool ButtonDriver::check_hold() const {
        bool result = this->is_hold();
        if (result) this->play_tone();
        return result;
    }

    bool ButtonDriver::check_click() const {
        bool result = this->is_click();
        if (result) this->play_tone();
        return result;
    }

    bool ButtonDriver::check_repeat_clicks(int repeat_rate, int before_delay) const {
        bool result = this->is_repeat_click(repeat_rate, before_delay);
        if (result) this->play_tone();
        return result;
    }

    bool ButtonDriver::is_hold() const {
        return held_state;
    }

    bool ButtonDriver::is_click() const {
        return clicked_state;
    }

    bool ButtonDriver::is_repeat_click(int repeat_rate, int before_delay) const {
        if (ticks_since_press == 0) return false;
        if (ticks_since_press == 1) return true;

        if (ticks_since_press > before_delay) {
            return ((ticks_since_press - before_delay) % repeat_rate) == 0;
        } else {
            return false;
        }
    }

    void ButtonDriver::play_tone() const {
        buzzer_driver.play_tone(this->pitch, 50);
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

    void ButtonDriver::set_pin_mode(int pin) {
        pinMode(pin, INPUT_PULLUP);
    }

    ButtonDriver button_driver_left{Pins::PIN_BUTTON_LEFT, PITCH_C4};
    ButtonDriver button_driver_action{Pins::PIN_BUTTON_ACTION, PITCH_C5};
    ButtonDriver button_driver_right{Pins::PIN_BUTTON_RIGHT, PITCH_G4};
}