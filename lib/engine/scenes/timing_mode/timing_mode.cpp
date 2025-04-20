#include "timing_mode.hpp"



namespace Engine {
    TimingModePlayScene::TimingModePlayScene() {}

    const Scene& TimingModePlayScene::tick() {
        this->current_timing_sp.tick();
        if (this->current_timing_sp.is_stop_clicked) {
            int score = this->current_timing_sp.calculate_score_weighted();

            this->total_score += score;

            Drivers::display_driver.clear_all();

            char score_str[10];
            itoa(score, score_str, 10);
            Drivers::display_driver.print_center(0, score_str);

            char total_score_str[30];
            itoa(this->total_score, total_score_str, 10);
            Drivers::display_driver.print_center(1, total_score_str);
        }

        if (this->current_timing_sp.is_finished) {
            this->current_timing_sp = TimingScenePart();
        }

        return blank_scene;
    }
}