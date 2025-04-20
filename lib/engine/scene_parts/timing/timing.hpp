#pragma once

#include <drivers.hpp>
#include "../../scene_parts/scene_parts.hpp"
#include "../../base/base.hpp"


namespace Engine {
    class TimingScenePart : public ScenePart {
    public:
        enum State {
            ROTATING, STOPPED
        };

        State state = State::ROTATING;

        // 0 means at goal led
        double loop_interpolation = 0;
        int ticks_per_loop;

        int max_score;
        double curve;

        size_t goal_led_idx;
        int goal_led_flash_every;
        int goal_led_timer = 0;

        int stop_length_ticks = 500;
        int stop_timer = 0;
        int stop_flash_every = 50;

        bool is_finished = false;
        bool is_stop_clicked = false;
        bool is_stopped = false;

        TimingScenePart(
            int ticks_per_loop = 200,
            int max_score = 10000,
            double curve = 0.15,
            size_t goal_led_idx = floor(Drivers::lights_driver.lights_count / 2.0F),
            int goal_led_flash_every = 100,
            int stop_length_ticks = 500,
            int stop_flash_every = 50
        );

        void tick() override;

        void tick_state_rotating();
        void tick_state_stopped();

        void on_trigger_stop();

        size_t get_internal_led_idx();

        size_t get_shown_led_idx();
        CRGB get_shown_led_color();

        int calculate_score_raw();
        int calculate_score_weighted();
    };
}