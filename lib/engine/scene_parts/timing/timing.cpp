#include "timing.hpp"

#include <colors.hpp>



namespace Engine {
    TimingScenePart::TimingScenePart(
        int ticks_per_loop,
        int max_score,
        double curve,
        size_t goal_led_idx,
        int goal_led_flash_every,
        int stop_length_ticks,
        int stop_flash_every
    ) :
        ticks_per_loop(ticks_per_loop),
        max_score(max_score),
        curve(curve),
        goal_led_idx(goal_led_idx),
        goal_led_flash_every(goal_led_flash_every),
        stop_length_ticks(stop_length_ticks),
        stop_flash_every(stop_flash_every)
    {}

    void TimingScenePart::tick() {
        if (is_finished) return;
        if (state == State::ROTATING) tick_state_rotating();
        else if (state == State::STOPPED) tick_state_stopped();
    }

    void TimingScenePart::tick_state_rotating() {
        loop_interpolation += 1.0 / ticks_per_loop;
        if (loop_interpolation >= 1.0) loop_interpolation = 0;


        Drivers::lights_driver.clear_led_array();

        goal_led_timer++;
        int modulo = goal_led_timer % goal_led_flash_every;
        if (modulo < (goal_led_flash_every / 2)) {
            Drivers::lights_driver.led_array[this->goal_led_idx] = CRGB::GhostWhite;
        } else {
            Drivers::lights_driver.led_array[this->goal_led_idx] = CRGB::Black;
        }

        const CRGB led_color = this->get_shown_led_color();
        const size_t next_on_led_idx = this->get_shown_led_idx();

        Drivers::lights_driver.led_array[next_on_led_idx] = led_color;
        Drivers::lights_driver.show();

        Serial.print(this->goal_led_idx);
        Serial.print("\t");
        Serial.print(loop_interpolation);


        if (Drivers::button_driver_action.is_clicked()) {
            this->on_trigger_stop();
        }
    }

    void TimingScenePart::tick_state_stopped() {
        stop_timer--;
        this->is_stop_clicked = false;
        if (stop_timer <= 0) {
            is_finished = true;
            return;
        }

        if (Drivers::button_driver_action.is_clicked()) {
            this->is_finished = true;
            return;
        }

        const size_t current_led_idx = this->get_shown_led_idx();
        const int modulo = stop_timer % stop_flash_every;
        const int change_state_every = stop_flash_every / 2;

        if (this->goal_led_idx != current_led_idx) {
            Drivers::lights_driver.led_array[this->goal_led_idx] = ColorFromPalette(
                Gradients::rainbow_palette, stop_timer % 256,
                255U, LINEARBLEND_NOWRAP
            );

            if (modulo < change_state_every) {
                Drivers::lights_driver.led_array[current_led_idx] = this->get_shown_led_color();
            } else {
                Drivers::lights_driver.led_array[current_led_idx] = CRGB::Black;
            }
        } else {
            if (modulo < change_state_every) {
                Drivers::lights_driver.led_array[this->goal_led_idx] = CRGB::Blue;
                for (int idx = 0; idx < Drivers::lights_driver.lights_count; idx++) {
                    Drivers::lights_driver.led_array[idx] = CRGB(16, 16, 16);
                }
            } else {
                Drivers::lights_driver.clear_led_array();
                Drivers::lights_driver.led_array[this->goal_led_idx] = CRGB::White;
            }
        }

        Drivers::lights_driver.show();
    }

    void TimingScenePart::on_trigger_stop() {
        this->stop_timer = stop_length_ticks;
        this->state = State::STOPPED;
        this->is_stop_clicked = true;
        this->is_stopped = true;
    }


    size_t TimingScenePart::get_internal_led_idx() {
        return floor(this->loop_interpolation * Drivers::lights_driver.lights_count);
    }

    size_t TimingScenePart::get_shown_led_idx() {
        int result = this->get_internal_led_idx() + goal_led_idx;
        if (result >= Drivers::lights_driver.lights_count) result -= Drivers::lights_driver.lights_count;
        return result;
    }

    CRGB TimingScenePart::get_shown_led_color() {
        return ColorFromPalette(
            Gradients::timing_palette,
            floor((float)this->get_internal_led_idx() / (float)Drivers::lights_driver.lights_count * 255),
            255,
            LINEARBLEND_NOWRAP
        );
    }


    // Ex. [10, 7.5, 5, 0, 5, 7.5]
    int TimingScenePart::calculate_score_raw() {
        const int internal_led_idx = this->get_internal_led_idx();
        if (internal_led_idx == 0) return this->max_score;

        const int remaining_led_count = Drivers::lights_driver.lights_count - 1;
        const int led_on_remaining_idx = internal_led_idx - 1;

        if (remaining_led_count % 2 == 0) {
            const int steps = remaining_led_count / 2;
            const float step = (float)max_score / (float)steps;
            const int next_half_start_idx = remaining_led_count / 2;

            if (led_on_remaining_idx < next_half_start_idx) {
                return max_score - (step * (led_on_remaining_idx + 1));
            }
            else {
                return step * (led_on_remaining_idx - next_half_start_idx);
            }
        }
        else {
            const int steps = (remaining_led_count + 1) / 2;
            const float step = (float)max_score / (float)steps;
            const int center_idx = floor((float)remaining_led_count / 2.0F);

            if (led_on_remaining_idx < center_idx) {
                return max_score - (step * (led_on_remaining_idx + 1));
            }
            else if (led_on_remaining_idx == center_idx) {
                return 0;
            }
            else {
                return step * (led_on_remaining_idx - center_idx);
            }
        };
    }


    int TimingScenePart::calculate_score_weighted() {
        const int raw_score = this->calculate_score_raw();

        if (this->curve == 0) {
            if (raw_score == this->max_score) return this->max_score;
            else return 0;
        }

        return pow((float)raw_score / this->max_score, 1.0F / this->curve) * this->max_score;
    }
}
