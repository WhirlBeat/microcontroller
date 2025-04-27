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

        long init_start_time = 0;
        int offset = 0;

        int visible_before_hit_ms = 2000;
        int timing_window_ms = 90;

        RhythmNote* notes[RhythmChart::MAX_NOTES];
        int note_count = -1;
        int visible_notes_start_idx = 0;
        int visible_notes_end_idx = 0;

        int goal_led_idx = floor((float)(Drivers::lights_driver.lights_count - 1) * 0.75F);


        int target_note_idx = 0;

        const int perfect_base_score = 300;
        const int good_base_score = 100;
        const int ok_base_score = 50;

        const char* previous_judgement = "";
        int combo = 0;
        int score = 0;


        RhythmEngineScenePart();

        void init(RhythmChart *chart);

        void tick() override;

        int get_total_offset();

        void on_perfect();
        void on_good();
        void on_ok();
        void on_miss();
        void add_score(int base_score);
    };
}