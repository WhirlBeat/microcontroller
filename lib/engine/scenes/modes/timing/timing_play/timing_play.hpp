#pragma once

#include <base/base.hpp>
#include "../timing_engine/timing_engine.hpp"



namespace Engine {
    class TimingModePlayScene : public Scene {
    public:
        TimingEngineScenePart current_timing_sp{};
        int total_score = 0;

        TimingModePlayScene();

        void init(TimingMod** selected_mods, size_t selected_mods_count);

        void tick() override;
    };
}