#pragma once

#include <base/base.hpp>
#include <scenes/modes/base/score_submit/score_submit.hpp>
#include "../timing_engine/timing_engine.hpp"
#include "../timing_mods/timing_mods.hpp"
#include "../timing_score_submit/timing_score_submit.hpp"



namespace Engine {
    class TimingModePlayScene : public Scene {
    public:
        TimingMod* selected_mods[TIMING_MOD_COUNT];
        size_t selected_mods_count;

        TimingEngineScenePart timing_engine{};
        int total_score;
        int perfects;

        const int attempts = 5;
        int attempt_idx = 0;

        TimingModeScoreSubmitScene score_submit{};


        static const int ROW_ATTEMPTS = 0;
        static const int ROW_PERFECTS = 1;
        static const int ROW_SCORE_SINGLE = 2;
        static const int ROW_SCORE_TOTAL = 3;

        TimingModePlayScene();

        void init(TimingMod* selected_mods_arg[TIMING_MOD_COUNT], size_t selected_mods_count);
        void restart_engine();

        void tick() override;
    };
}