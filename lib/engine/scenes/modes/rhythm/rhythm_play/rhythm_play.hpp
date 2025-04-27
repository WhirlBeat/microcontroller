#pragma once

#include <base/base.hpp>
#include <scenes/modes/base/score_submit/score_submit.hpp>
#include "../chart/chart.hpp"
#include "../rhythm_engine/rhythm_engine.hpp"



namespace Engine {
    class RhythmModePlayScene : public Scene {
    public:
        RhythmEngineScenePart engine{};

        static const int ROW_SCORE = 0;
        static const int ROW_JUDGEMENT = 1;
        static const int ROW_COMBO = 2;

        RhythmModePlayScene();

        void init(RhythmChart* chart);

        void tick() override;
    };
}