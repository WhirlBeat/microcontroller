#include "timing_score_submit.hpp"



namespace Engine {
    TimingModeScoreSubmitScene::TimingModeScoreSubmitScene() {}

    void TimingModeScoreSubmitScene::init_sub(int score, TimingMod* selected_mods[TIMING_MOD_COUNT], size_t selected_mods_count) {
        this->score = score;

        for (int idx = 0; idx < TIMING_MOD_COUNT; idx++) {
            this->selected_mods[idx] = selected_mods[idx];
        }

        this->selected_mods_count = selected_mods_count;
    }

    void TimingModeScoreSubmitScene::render_score_summary() {
        String summary_str = String(this->score) + " (x" + get_timing_mod_total_multiplier(this->selected_mods, this->selected_mods_count) + ")";
        Drivers::display_driver.print_center(this->ROW_SCORE_SUMMARY, summary_str.c_str());
    }

    void TimingModeScoreSubmitScene::submit_score() {
        String username = this->get_username();

        JsonDocument request_body;
        request_body["username"] = username.c_str();
        request_body["score"] = this->score;
        request_body["multiplier"] = get_timing_mod_total_multiplier(this->selected_mods, this->selected_mods_count);

        JsonArray array = request_body["mods"].as<JsonArray>();
        for (int idx = 0; idx < this->selected_mods_count; idx++) {
            array.add(this->selected_mods[idx]->get_shorthand());
        }

        JsonDocument response = Drivers::api_driver.make_post_request(Drivers::timing_table_route, request_body);
        int id = response["moreInfo"]["id"].as<int>();

        this->leaderboard_scene.init(10, id);
        scene_loader.switch_scene(&this->leaderboard_scene);
    }
}