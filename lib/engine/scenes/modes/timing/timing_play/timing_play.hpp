#pragma once

#include <base/base.hpp>
#include "../timing_engine/timing_engine.hpp"
#include "../timing_mods/timing_mods.hpp"



namespace Engine {
    class TimingModePlayScene : public Scene {
    public:
        TimingMod* selected_mods[TIMING_MOD_COUNT];
        size_t selected_mods_count = 0;

        TimingEngineScenePart timing_engine{};
        int total_score = 0;

        TimingModePlayScene();

        void init(TimingMod** selected_mods, size_t selected_mods_count);
        void restart_engine();

        void tick() override;
    };
}