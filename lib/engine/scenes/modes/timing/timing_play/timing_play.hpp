#pragma once

#include <base/base.hpp>
#include "../timing_engine/timing_engine.hpp"



namespace Engine {
    class TimingModePlayScene : public Scene {
    public:
        TimingEngineScenePart current_timing_sp{};
        int total_score = 0;

        TimingModePlayScene();

        void tick() override;
    };
}