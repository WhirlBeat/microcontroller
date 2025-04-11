#include "timing.hpp"



CRGB interpolate_color(CRGB &start, CRGB &end, double t) {
    return CRGB(
        start.r + (end.r - start.r) * t,
        start.g + (end.g - start.g) * t,
        start.b + (end.b - start.b) * t
    );
}


CRGB gradient[] = {
    CRGB::Blue,
    CRGB::Red,
    CRGB::Orange,
    CRGB::Green,
    CRGB::GhostWhite
};
const size_t gradient_size = 5;

CRGB get_led_color(double t) {
    const size_t segments = gradient_size - 1;
    const size_t current_segment = floor(t * segments);

    return interpolate_color(
        gradient[current_segment],
        gradient[current_segment + 1],
        (t * segments) - current_segment
    );
}


namespace Engine {
    OneTimingScene::OneTimingScene() : Scene() {}

    const Scene& OneTimingScene::tick() {
        if (state == TimingState::ROTATING) tick_state_rotating();
        else if (state == TimingState::STOPPED) tick_state_stopped();
        return blank_scene;
    }

    void OneTimingScene::tick_state_rotating() {
        loop_state += 1.0 / ticks_per_loop;
        if (loop_state >= 1.0) loop_state = 0;


        const CRGB led_color = get_led_color(loop_state);
        const size_t next_on_led_idx = this->get_current_led_idx();

        if (this->previous_on_led_idx != next_on_led_idx) {
            if (this->previous_on_led_idx < ComponentParams::LED_COUNT) {
                Drivers::lights_driver.led_array[previous_on_led_idx] = Colors::BLACK;
            }
            Drivers::lights_driver.led_array[next_on_led_idx] = led_color;

            this->previous_on_led_idx = next_on_led_idx;
        }
        Drivers::lights_driver.show();

        if (Drivers::button_driver_action.is_clicked()) {
            this->on_trigger_stop();
        }
    }

    void OneTimingScene::tick_state_stopped() {
        stop_timer--;
        if (stop_timer <= 0) {
            loop_state = 0.4;
            state = TimingState::ROTATING;
            return;
        }

        const size_t current_led_idx = this->get_current_led_idx();
        size_t modulo = stop_timer % stop_flash_every;
        if (modulo < (stop_flash_every / 2)) {
            Drivers::lights_driver.led_array[current_led_idx] = get_led_color(loop_state);
        } else {
            Drivers::lights_driver.led_array[current_led_idx] = Colors::BLACK;
        }
    }

    void OneTimingScene::on_trigger_stop() {
        char score_str[30];
        itoa(calculate_score(), score_str, 10);
        Drivers::display_driver.clear_all();
        Drivers::display_driver.print_center(0, score_str);

        stop_timer = stop_length_ticks;
        state = TimingState::STOPPED;
    }

    size_t OneTimingScene::get_current_led_idx() {
        return floor(loop_state * ComponentParams::LED_COUNT);
    }

    int OneTimingScene::calculate_score() {
        return abs(loop_state - 0.5) * max_score;
    }
}
