#include "rhythm_play.hpp"



namespace Engine {
    RhythmModePlayScene::RhythmModePlayScene() {}

    void RhythmModePlayScene::init(RhythmChart* chart) {
        this->engine.init(chart);

        this->score = 0;
        this->max_combo = 0;
        this->accuracy = 0;
    }

    void RhythmModePlayScene::tick() {
        this->engine.tick();

        if (this->engine.state == RhythmEngineScenePart::FINISHED) {
            delay(1000);
            this->complete_scene.init(this->score, this->max_combo, this->accuracy);
            scene_loader.switch_scene(&this->complete_scene);
            return;
        }


        Drivers::display_driver.clear_all();

        this->score = this->engine.score;
        String score_str = String(this->engine.score);
        Drivers::display_driver.print_center(this->ROW_SCORE, score_str.c_str());

        this->accuracy = ((float)engine.unweighted_score) / (float)((float)engine.note_count * (float)engine.perfect_base_score);
        String judgement_str = String(this->engine.previous_judgement) + " | " + String(this->accuracy * 100, 2) + "%";
        Drivers::display_driver.print_center(this->ROW_JUDGEMENT, judgement_str.c_str());

        if (this->engine.combo > this->max_combo) this->max_combo = this->engine.combo;
        String combo_str = String(this->engine.combo) + "x (" + this->max_combo + "x)";
        Drivers::display_driver.print_center(this->ROW_COMBO, combo_str.c_str());
    }
}