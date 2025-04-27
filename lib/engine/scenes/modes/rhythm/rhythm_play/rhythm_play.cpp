#include "rhythm_play.hpp"



namespace Engine {
    RhythmModePlayScene::RhythmModePlayScene() {}

    void RhythmModePlayScene::init(RhythmChart* chart) {
        this->engine.init(chart);
    }

    void RhythmModePlayScene::tick() {
        this->engine.tick();
    }
}