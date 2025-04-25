#pragma once

#include <drivers.hpp>

#include <scene_parts/scene_parts.hpp>
#include <base/base.hpp>
#include <scenes/main_menu/main_menu.hpp>
#include <scenes/modes/base/base.hpp>

#include "../timing_mods/timing_mods.hpp"
#include "../timing_leaderboard/timing_leaderboard.hpp"


namespace Engine {
    class TimingModeScoreSubmitScene : public ScoreSubmitScene {
    public:
        TimingLeaderboardScene leaderboard_scene{};

        TimingMod* selected_mods[TIMING_MOD_COUNT];
        size_t selected_mods_count;

        int score = 0;

        TimingModeScoreSubmitScene();
        void init_sub(int score, TimingMod* selected_mods[TIMING_MOD_COUNT], size_t selected_mods_count);

        void render_score_summary() override;

        void submit_score() override;
    };
}