#include "timing_mod_select.hpp"



namespace Engine {
    TimingModeModSelectScene::TimingModeModSelectScene() {}


    void TimingModeModSelectScene::init() {
        for (int idx = 0; idx < TIMING_MOD_COUNT; idx++) {
            this->mods[idx] = timing_mods[idx];
            this->mod_select_mask[idx] = false;
            this->choices[idx] = timing_mods[idx]->get_name();
        }

        this->choices[TIMING_MOD_COUNT] = "Back";

        this->select_menu.init(choices, TIMING_MOD_COUNT + 1, this->ROW_SELECT_MENU);
    }


    void TimingModeModSelectScene::tick() {
        if (this->is_mods_enabled()) Drivers::music_driver.play(SongIDs::SETUP_REMIX, true);
        else Drivers::music_driver.play(SongIDs::SETUP, true);

        this->select_menu.tick();
        int selected_idx = this->select_menu.get_selected_idx();



        if (selected_idx == TIMING_MOD_COUNT) {
            Drivers::display_driver.clear_row(this->ROW_DESC);
            Drivers::display_driver.clear_row(this->ROW_ENABLE_STATUS);

            Drivers::display_driver.print_center(this->ROW_DESC, "Confirm selection.");

            TimingMod* selected_mods[TIMING_MOD_COUNT];
            size_t selected_mods_count = 0;
            this->get_selected_mods(selected_mods, &selected_mods_count);

            String multiplier_str =
                String("Total Mult: ") +
                String(get_timing_mod_total_multiplier(selected_mods, selected_mods_count), 2) +
                "x";

            Drivers::display_driver.clear_row(this->ROW_MULTIPLIER);
            Drivers::display_driver.print_center(this->ROW_MULTIPLIER, multiplier_str.c_str());

            if (Drivers::button_driver_action.check_click()) {
                scene_loader.go_back();
            }
            return;
        }

        const char* description = this->mods[selected_idx]->get_description();
        Drivers::display_driver.clear_row(this->ROW_DESC);
        Drivers::display_driver.print_center(this->ROW_DESC, description);

        Drivers::display_driver.clear_row(this->ROW_MULTIPLIER);
        String multiplier_str = String("Mult Bonus: ") + String(this->mods[selected_idx]->get_multiplier(), 2) + "x";
        Drivers::display_driver.print_center(this->ROW_MULTIPLIER, multiplier_str.c_str());

        if (Drivers::button_driver_action.check_click()) {
            this->mod_select_mask[selected_idx] = !this->mod_select_mask[selected_idx];
        }

        Drivers::display_driver.clear_row(this->ROW_ENABLE_STATUS);
        Drivers::display_driver.print_center(
            this->ROW_ENABLE_STATUS,
            this->mod_select_mask[selected_idx] ? "ENABLED!" : "DISABLED!"
        );
        Drivers::display_driver.print_char_at(0, this->ROW_ENABLE_STATUS, CustomChars::ACTION);
    }

    void TimingModeModSelectScene::get_selected_mods(TimingMod** out_mods, size_t* out_size) {
        int current_idx = 0;
        for (int idx = 0; idx < TIMING_MOD_COUNT; idx++) {
            if (this->mod_select_mask[idx]) {
                out_mods[current_idx] = this->mods[idx];
                current_idx++;
            }
        }
        *out_size = current_idx;
    }

    bool TimingModeModSelectScene::is_mods_enabled() {
        bool mods_enabled = false;
        for (int idx = 0; idx < TIMING_MOD_COUNT; idx++) {
            if (this->mod_select_mask[idx]) {
                mods_enabled = true;
                break;
            }
        }
        return mods_enabled;
    }
}