#include "timing_play.hpp"



namespace Engine {
    TimingModePlayScene::TimingModePlayScene() {}

    void TimingModePlayScene::init(TimingMod* selected_mods_arg[TIMING_MOD_COUNT], size_t selected_mods_count) {
        for (int idx = 0; idx < selected_mods_count; idx++) {
            this->selected_mods[idx] = selected_mods_arg[idx];
        }
        this->selected_mods_count = selected_mods_count;

        this->total_score = 0;
        this->perfects = 0;
        this->attempt_idx = 0;

        this->restart_engine();
    }

    void TimingModePlayScene::restart_engine() {
        TimingSettings settings{};

        for (int idx = 0; idx < selected_mods_count; idx++) {
            settings = selected_mods[idx]->modify_settings(settings);
        }

        this->timing_engine = TimingEngineScenePart();
        this->timing_engine.init(settings);
    }

    void TimingModePlayScene::tick() {
        this->timing_engine.tick();

        Drivers::display_driver.clear_row(this->ROW_ATTEMPTS);

        String attempts_str = String("Attempt ") + (this->attempt_idx + 1) + "/" + this->attempts;
        Drivers::display_driver.print_center(this->ROW_ATTEMPTS, attempts_str.c_str());


        if (this->timing_engine.is_stop_clicked) {
            int score = this->timing_engine.calculate_score_weighted();

            float multiplier = get_timing_mod_total_multiplier(this->selected_mods, this->selected_mods_count);
            this->total_score += floor((float)score * multiplier);

            Drivers::display_driver.clear_all();

            if (score == this->timing_engine.max_score) {
                this->perfects++;
            }

            if (this->perfects != 0) {
                String perfects_str = String("PERFECTS: ") + this->perfects;
                Drivers::display_driver.print_center(this->ROW_PERFECTS, perfects_str.c_str());
            }

            String score_str =
                (
                    score == this->timing_engine.max_score
                        ? String("PERFECT +") + score
                        : String ("Prev: +") + score
                ) +
                " x" + String(multiplier, 2);
            Drivers::display_driver.print_center(this->ROW_SCORE_SINGLE, score_str.c_str());

            String total_score_str = String("TOTAL: ") + this->total_score;
            Drivers::display_driver.print_center(this->ROW_SCORE_TOTAL, total_score_str.c_str());
        }

        if (this->timing_engine.is_finished) {
            this->restart_engine();
            this->attempt_idx++;

            if (this->attempt_idx >= this->attempts) {
                this->score_submit.init();
                this->score_submit.init_sub(this->total_score, this->selected_mods, this->selected_mods_count);
                this->score_submit.begin();

                scene_loader.switch_scene(&this->score_submit);
            }
        }
    }
}