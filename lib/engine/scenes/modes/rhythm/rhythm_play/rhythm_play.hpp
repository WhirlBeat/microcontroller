#pragma once

#include <base/base.hpp>
#include <scenes/modes/base/score_submit/score_submit.hpp>
#include "../chart/chart.hpp"
#include "../rhythm_engine/rhythm_engine.hpp"



namespace Engine {
    class RhythmModePlayScene : public Scene {
    public:
        RhythmEngineScenePart engine{};

        RhythmModePlayScene();

        void init(RhythmChart* chart);

        void tick() override;
    };
}