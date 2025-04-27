#pragma once

#include <base/base.hpp>
#include <scenes/modes/base/score_submit/score_submit.hpp>



namespace Engine {
    class RhythmCompleteScene : public Scene {
    public:
        int score;
        int max_combo;
        float accuracy;

        static const int ROW_CONGRATS = 0;
        static const int ROW_SCORE = 1;
        static const int ROW_STATISTICS = 2;
        static const int ROW_EXIT = 3;

        RhythmCompleteScene();

        void init(int score, int max_combo, float accuracy);

        void tick() override;
    };
}