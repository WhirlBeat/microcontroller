#include "rhythm_play.hpp"



namespace Engine {
    RhythmModePlayScene::RhythmModePlayScene() {}

    void RhythmModePlayScene::init(RhythmChart* chart) {
        this->engine.init(chart);
    }

    void RhythmModePlayScene::tick() {
        this->engine.tick();


        Drivers::display_driver.clear_all();

        String score_str = String(this->engine.score);
        Drivers::display_driver.print_center(this->ROW_SCORE, score_str.c_str());

        Drivers::display_driver.print_center(this->ROW_JUDGEMENT, this->engine.previous_judgement);

        String combo_str = String(this->engine.combo) + "x";
        Drivers::display_driver.print_center(this->ROW_COMBO, combo_str.c_str());
    }
}