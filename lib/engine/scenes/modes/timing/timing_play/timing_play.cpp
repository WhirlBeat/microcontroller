#include "timing_play.hpp"



namespace Engine {
    TimingModePlayScene::TimingModePlayScene() {}

    void TimingModePlayScene::tick() {
        this->current_timing_sp.tick();
        if (this->current_timing_sp.is_stop_clicked) {
            int score = this->current_timing_sp.calculate_score_weighted();

            this->total_score += score;

            Drivers::display_driver.clear_all();

            String score_str = String(score);
            Drivers::display_driver.print_center(0, score_str.c_str());

            String total_score_str = String(this->total_score);
            Drivers::display_driver.print_center(1, total_score_str.c_str());
        }

        if (this->current_timing_sp.is_finished) {
            this->current_timing_sp = TimingEngineScenePart();
        }
    }
}