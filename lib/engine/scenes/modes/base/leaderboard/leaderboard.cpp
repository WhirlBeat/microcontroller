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

    LeaderboardScene::LeaderboardScene() : Scene() {}

    void LeaderboardScene::init(const char* table_name, int load_count, int center_on) {
        this->confirm_exit_menu.init(this->choices, this->CHOICES_COUNT, 2);

        this->table_name = table_name;
        this->load_count = load_count;
        this->center_on = center_on;

        Serial.println("init");
        Serial.println(this->center_on);
    }

    void LeaderboardScene::begin() {
        this->load_entries();
    }

    void LeaderboardScene::tick() {
        if (this->state == DISPLAY_ENTRIES) {
            this->update_display_entries_controls();
            this->render_entries(this->current_center_idx);
        }
        else if (this->state == CONFIRM_EXIT) {
            this->tick_confirm_exit_scene_part();
        }
        else if (this->state == EXIT) {
            Drivers::display_driver.clear_all();
            scene_loader.go_back_to_scene(SceneIds::MAIN_MENU);
        }
    }

    void LeaderboardScene::load_entries() {
        Serial.println(this->center_on);
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

        for (int idx = 0; idx < this->actual_entry_count; idx++) {
            if (this->entries[idx].id == this->center_on) {
                this->current_center_idx = idx;
                break;
            }
        }
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

        for (int idx = start_idx; idx <= end_idx; idx++) {
            LeaderboardEntry entry = this->entries[idx];

            int current_row = idx - start_idx;
            if (idx == center_idx) {
                Drivers::display_driver.print_at(1, current_row, ">");
            }

            String placement_str = String("#") + entry.placement + " " + entry.username + " " + entry.score;
            Drivers::display_driver.print_at(2, current_row, placement_str.c_str());
        }
    }



    void LeaderboardScene::tick_confirm_exit_scene_part() {
        Drivers::display_driver.clear_all();
        Drivers::display_driver.print_center(0, "Exit leaderboard?");

        this->confirm_exit_menu.tick();

        if (Drivers::button_driver_action.is_clicked()) {
            if (this->confirm_exit_menu.get_selected_idx() == 1) {
                this->state = EXIT;
            }
            else {
                this->state = DISPLAY_ENTRIES;
            }
        }
    }
}