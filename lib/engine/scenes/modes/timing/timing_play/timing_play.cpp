#include "timing_play.hpp"



namespace Engine {
    TimingModePlayScene::TimingModePlayScene() {}

    void TimingModePlayScene::init(TimingMod** selected_mods, size_t selected_mods_count) {
        this->selected_mods = selected_mods;
        this->selected_mods_count = selected_mods_count;

        this->restart_engine();
    }

    void TimingModePlayScene::restart_engine() {
        TimingSettings settings{};

        for (int idx = 0; idx < selected_mods_count; idx++) {
            settings = selected_mods[idx]->modify_settings(settings);
        }

        this->timing_engine.init(settings);
        this->timing_engine.begin();
    }

    void TimingModePlayScene::tick() {
        this->timing_engine.tick();
        if (this->timing_engine.is_stop_clicked) {
            int score = this->timing_engine.calculate_score_weighted();

            this->total_score += score;

            Drivers::display_driver.clear_all();

            String score_str = String(score);
            Drivers::display_driver.print_center(0, score_str.c_str());

            String total_score_str = String(this->total_score);
            Drivers::display_driver.print_center(1, total_score_str.c_str());
        }

        if (this->timing_engine.is_finished) {
            this->restart_engine();
        }
    }
}