#pragma once

#include <drivers.hpp>
#include <Vector.h>
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
        int ticks_per_loop = 500;

        size_t previous_on_led_idx = 10000;

        size_t stop_length_ticks = 3000;
        size_t stop_timer = 0;
        size_t stop_flash_every = 500;

        int max_score = 10000;

        OneTimingScene();

        const Scene& tick() override;

        void tick_state_rotating();
        void tick_state_stopped();

        void on_trigger_stop();

        size_t get_current_led_idx();

        int calculate_score();
    };
}