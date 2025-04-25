#include "leaderboard.hpp"



namespace Engine {
    LeaderboardScene::LeaderboardScene() : Scene() {}

    void LeaderboardScene::init(int load_count, int center_on) {
        this->confirm_exit_menu.init(this->choices, this->CHOICES_COUNT, 2);

        this->load_count = load_count;
        this->center_on = center_on;

        this->state = DISPLAY_ENTRIES;
        this->display_starting_entry_idx = 0;
    }

    void LeaderboardScene::begin() {
        this->load_entries();
        this->display_starting_entry_idx = this->get_center_idx();
    }

    void LeaderboardScene::tick() {
        if (this->state == DISPLAY_ENTRIES) {
            this->update_display_entries_controls();
            this->render_entries(this->display_starting_entry_idx);
        }
        else if (this->state == CONFIRM_EXIT) {
            this->tick_confirm_exit_scene_part();
        }
        else if (this->state == EXIT) {
            Drivers::display_driver.clear_all();
            scene_loader.go_back_to_scene(SceneIds::MAIN_MENU);
        }
    }

    void LeaderboardScene::update_display_entries_controls() {
        if (Drivers::button_driver_left.is_click_repeated()) {
            this->display_starting_entry_idx--;
            if (this->display_starting_entry_idx < 0) this->display_starting_entry_idx = this->get_entry_count() - 1;
        }

        if (Drivers::button_driver_right.is_click_repeated()) {
            this->display_starting_entry_idx++;
            if (this->display_starting_entry_idx >= this->get_entry_count()) this->display_starting_entry_idx = 0;
        }

        if (Drivers::button_driver_action.is_clicked()) {
            this->state = CONFIRM_EXIT;
        }
    }

    void LeaderboardScene::render_entries(int center_idx) {
        Drivers::display_driver.clear_all();

        String title_str = String(this->get_name()) + " scores";
        Drivers::display_driver.print_center(this->ROW_TITLE, title_str.c_str());

        Drivers::display_driver.print_char_at(0, this->DISPLAY_OFFSET, CustomChars::ARROW_UP);
        Drivers::display_driver.print_char_at(0, this->DISPLAY_OFFSET + this->DISPLAY_ROWS - 1, CustomChars::ARROW_DOWN);

        int end_idx = this->display_starting_entry_idx + (this->DISPLAY_ROWS - 1);
        if (end_idx >= this->get_entry_count()) end_idx = this->get_entry_count() - 1;

        for (int idx = this->display_starting_entry_idx; idx <= end_idx; idx++) {
            int display_row_idx = idx - this->display_starting_entry_idx;
            this->render_one_entry(1, display_row_idx + this->DISPLAY_OFFSET, idx);
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