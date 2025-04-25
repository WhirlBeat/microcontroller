#include "timing_leaderboard.hpp"



namespace Engine {
    TimingLeaderboardScene::TimingLeaderboardScene() : LeaderboardScene() {}

    int TimingLeaderboardScene::get_entry_count() {
        JsonArray entries = this->response["moreInfo"].as<JsonArray>();
        return entries.size();
    }

    void TimingLeaderboardScene::init(int load_count, int center_on) {
        LeaderboardScene::init(load_count, center_on);
        this->response.clear();
    }

    int TimingLeaderboardScene::get_center_idx() {
        if (this->center_on <= 0) return 0;

        for (int idx = 0; idx < this->get_entry_count(); idx++) {
            if (this->response["moreInfo"][idx]["id"].as<int>() == this->center_on) {
                return idx;
            }
        }

        return 0;
    }

    const char* TimingLeaderboardScene::get_name() {
        return "Timing";
    }

    void TimingLeaderboardScene::load_entries() {
        JsonDocument response = Drivers::api_driver.get_table(Drivers::timing_table_route, this->load_count, this->center_on);
        this->response = response;
    }

    void TimingLeaderboardScene::render_one_entry(int x, int y, int entry_idx) {
        JsonObject entry = this->response["moreInfo"][entry_idx].as<JsonObject>();

        String render_str =
            String("#") + entry["placement"].as<String>() + " " +
            entry["username"].as<String>() + " " +
            entry["score"].as<int>() +
            "x" + String(entry["multiplier"].as<float>(), 2);

        Drivers::display_driver.print_at(x, y, render_str.c_str());
    }
}