#pragma once

#include <drivers.hpp>
#include "../../scene_parts/scene_parts.hpp"
#include "../../base/base.hpp"


namespace Engine {
    enum class TimingState {
        ROTATING, STOPPED
    };

    class OneTimingScene : public Scene {
    public:
        TimingState state = TimingState::ROTATING;

        // 0 means at goal led
        double loop_state = 0;
        int ticks_per_loop = 1000;

        int goal_led_idx = 50;
        size_t goal_led_timer = 0;
        size_t goal_led_flash_every = 100;

        size_t stop_length_ticks = 500;
        size_t stop_timer = 0;
        size_t stop_flash_every = 50;

        int max_score = 10000;
        double curve = 0.25;

        OneTimingScene();

        const Scene& tick() override;

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