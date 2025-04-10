#pragma once

#include <managers.hpp>
#include <Vector.h>
#include "../../scene_parts/scene_parts.hpp"
#include "../../base/base.hpp"


namespace SceneSources {
    enum class TimingState {
        ROTATING, STOPPED
    };

    class Timing : public Scene::Source {
    public:
        LCD::Display& display;
        ShiftRegister::LEDControl& led_control;

        TimingState state = TimingState::ROTATING;

        // 0 means at goal led
        double loop_state = 0;
        int ticks_per_loop = 500;
        byte led_byte = 0b00000000;

        size_t stop_length_ticks = 3000;
        size_t stop_timer = 0;
        size_t stop_flash_every = 500;

        int max_score = 10000;

        Timing(LCD::Display& display, ShiftRegister::LEDControl& led_control);

        const Scene::Source& render() override;

        void state_rotating();
        void state_stopped();

        void on_btn_action_click() override;

        int calculate_score();


        size_t previous_shift = 1000;
    };
}