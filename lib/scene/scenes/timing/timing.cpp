#include "timing.hpp"


namespace SceneSources {
    Timing::Timing(LCD::Display &display, ShiftRegister::LEDControl &led_control) :
        display(display), led_control(led_control)
    {}

    const Scene::Source &Timing::render() {
        if (state == TimingState::ROTATING) state_rotating();
        else if (state == TimingState::STOPPED) state_stopped();
        return Scene::blank_source;
    }

    void Timing::state_rotating() {
        loop_state += 1.0 / ticks_per_loop;
        if (loop_state >= 1.0) loop_state = 0;


        double loop_state_shifted = loop_state - (1.0 / 8.0 / 2.0);
        if (loop_state_shifted < 0) loop_state_shifted += 1;

        led_byte = 0b00000001;
        size_t shifts;
        if (loop_state < 1.0 / (2.0 * 8.0)) {
            shifts = floor((loop_state * 8.0) + 8.0 - 1);
        } else {
            shifts = floor((loop_state * 8.0) - (1.0 / 8.0));
        }
        led_byte = led_byte << shifts;
        led_control.write(led_byte);

        Serial.print(shifts);
        Serial.print("\t");
        Serial.print(loop_state < 1.0 / (2.0 * 8.0));
        Serial.print("\t");
        Serial.print(loop_state);
        Serial.println();
        
        // if (previous_shift != shifts) {
        //     char score_str[30];
        //     itoa(calculate_score(), score_str, 10);
        //     display.clear();
        //     display.print_center(0, score_str);

        //     previous_shift = shifts;
        // }
        
    }

    void Timing::state_stopped() {
        stop_timer--;
        if (stop_timer == 0) {
            loop_state = 0.4;
            state = TimingState::ROTATING;
            return;
        }

        size_t modulo = stop_timer % stop_flash_every;
        if (modulo < (stop_flash_every / 2)) {
            led_control.write(led_byte);
        } else {
            led_control.write(0);
        }
    }

    void Timing::on_btn_action_click() {
        char score_str[30];
        itoa(calculate_score(), score_str, 10);
        display.clear();
        display.print_center(0, score_str);

        stop_timer = stop_length_ticks;
        state = TimingState::STOPPED;
    }

    int Timing::calculate_score() {
        return abs(loop_state - 0.5) * max_score;
    }
}
