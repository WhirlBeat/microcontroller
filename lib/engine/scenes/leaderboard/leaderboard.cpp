#include "leaderboard.hpp"



namespace Engine {
    LeaderboardEntry::LeaderboardEntry(int id, String username, int score, int placement) :
        id(id),
        username(username),
        score(score),
        placement(placement)
    {}
    LeaderboardEntry::LeaderboardEntry() :
        username(""),
        score(0),
        placement(0)
    {}

    LeaderboardScene::LeaderboardScene(const char* table_name, int load_count, int center_on) :
        Scene::Scene(),
        table_name(table_name),
        load_count(load_count),
        center_on(center_on)
    {}

    Scene* LeaderboardScene::tick() {
        if (!this->is_entries_loaded) {
            this->load_entries();

            for (int idx = 0; idx < this->actual_entry_count; idx++) {
                if (this->entries[idx].id == this->center_on) {
                    this->current_center_idx = idx;
                    break;
                }
            }
        }

        if (this->state == DISPLAY_ENTRIES) {
            this->update_display_entries_controls();
            this->render_entries(this->current_center_idx);
            return nullptr;
        }
        if (this->state == CONFIRM_EXIT) {
            this->tick_confirm_exit_scene_part();
            return nullptr;
        }
        if (this->state == EXIT) {
            Drivers::display_driver.clear_all();
            return &main_menu_scene;
        }

        return nullptr;
    }

    void LeaderboardScene::load_entries() {
        JsonDocument result = Drivers::api_driver.get_table(this->table_name, this->load_count, this->center_on);
        JsonArray more_info = result["moreInfo"].as<JsonArray>();

        this->actual_entry_count = more_info.size();
        for (int idx = 0; idx < this->actual_entry_count; idx++) {
            JsonObject obj = more_info[idx].as<JsonObject>();

            this->entries[idx] = LeaderboardEntry(
                obj["id"].as<int>(),
                String(obj["username"].as<const char*>()),
                obj["score"].as<int>(),
                obj["placement"].as<int>()
            );
        }

        this->is_entries_loaded = true;
    }

    void LeaderboardScene::update_display_entries_controls() {
        if (Drivers::button_driver_left.is_click_repeated()) {
            this->current_center_idx--;
            if (this->current_center_idx < 0) this->current_center_idx = this->actual_entry_count - 1;
        }

        if (Drivers::button_driver_right.is_click_repeated()) {
            this->current_center_idx++;
            if (this->current_center_idx >= this->actual_entry_count) this->current_center_idx = 0;
        }

        if (Drivers::button_driver_action.is_clicked()) {
            this->state = CONFIRM_EXIT;
        }
    }

    void LeaderboardScene::render_entries(int center_idx) {
        Drivers::display_driver.clear_all();

        int start_idx = center_idx - floor((float)(Drivers::display_driver.size_y - 1) / 2.0F);
        if (start_idx < 0) start_idx = 0;

        int end_idx = start_idx + (Drivers::display_driver.size_y - 1);
        if (end_idx >= this->actual_entry_count) {
            end_idx = this->actual_entry_count - 1;
            start_idx = end_idx - (Drivers::display_driver.size_y - 1);
        }

        Serial.println(String("a ") + start_idx + " b " + end_idx + " c " + center_idx);

        for (int idx = start_idx; idx <= end_idx; idx++) {
            LeaderboardEntry entry = this->entries[idx];

            int current_row = idx - start_idx;
            Serial.println(current_row);
            if (idx == center_idx) {
                Drivers::display_driver.print_at(1, current_row, ">");
            }

            Drivers::display_driver.print_at(
                2, current_row,
                (String("#") + entry.placement + " " + entry.username + " " + entry.score).c_str()
            );
        }
    }



    void LeaderboardScene::tick_confirm_exit_scene_part() {
        Drivers::display_driver.clear_all();
        Drivers::display_driver.print_center(0, "Exit leaderboard?");

        this->confirm_exit_scene_part.tick();

        if (Drivers::button_driver_action.is_clicked()) {
            if (this->confirm_exit_scene_part.get_selected_idx() == 1) {
                this->state = EXIT;
            }
            else {
                this->state = DISPLAY_ENTRIES;
            }
        }
    }
}