#pragma once

#include <base/base.hpp>
#include <scenes/modes/base/score_submit/score_submit.hpp>
#include "../chart/chart.hpp"
#include "../rhythm_engine/rhythm_engine.hpp"
#include "../rhythm_complete/rhythm_complete.hpp"



namespace Engine {
    class RhythmModePlayScene : public Scene {
    public:
        RhythmEngineScenePart engine{};
        RhythmCompleteScene complete_scene{};

        int score = 0;
        int max_combo = 0;
        float accuracy = 0;

        static const int ROW_SCORE = 0;
        static const int ROW_JUDGEMENT = 1;
        static const int ROW_COMBO = 2;

        RhythmModePlayScene();

        void init(RhythmChart* chart);

        void tick() override;
    };
}