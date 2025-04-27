#pragma once

#include <drivers.hpp>
#include <scene_parts/scene_parts.hpp>
#include <base/base.hpp>

#include "../chart/chart.hpp"


namespace Engine {
    class RhythmEngineScenePart : public ScenePart {
    public:
        enum State {
            STARTING,
            PLAYING
        };

        State state = STARTING;

        int song_id = 0;

        long start_time = 0;

        int visible_before_hit_ms = 1000;
        int timing_window_ms = 500;

        RhythmNote* notes[RhythmChart::MAX_NOTES];
        int note_count = -1;
        int visible_notes_start_idx = 0;
        int visible_notes_end_idx = 0;

        int goal_led_idx = floor((float)(Drivers::lights_driver.lights_count - 1) * 0.75F);


        RhythmEngineScenePart();

        void init(RhythmChart *chart);

        void tick() override;
    };
}