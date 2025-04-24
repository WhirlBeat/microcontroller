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
        this->select_menu.tick();
        int selected_idx = this->select_menu.get_selected_idx();

        if (selected_idx == TIMING_MOD_COUNT) {
            Drivers::display_driver.clear_row(this->ROW_DESC);
            Drivers::display_driver.clear_row(this->ROW_ENABLE_STATUS);

            Drivers::display_driver.print_center(this->ROW_DESC, "Confirm selection.");
            return;
        }

        Serial.println(selected_idx);
        Serial.println(this->mods[selected_idx]->get_description());
        const char* description = this->mods[selected_idx]->get_description();
        Drivers::display_driver.clear_row(this->ROW_DESC);
        Drivers::display_driver.print_center(this->ROW_DESC, description);

        if (Drivers::button_driver_action.is_clicked()) {
            this->mod_select_mask[selected_idx] = !this->mod_select_mask[selected_idx];
        }

        Drivers::display_driver.clear_row(this->ROW_ENABLE_STATUS);
        Drivers::display_driver.print_center(
            this->ROW_ENABLE_STATUS,
            this->mod_select_mask[selected_idx] ? "Enabled" : "Disabled"
        );
        Drivers::display_driver.print_char_at(0, this->ROW_ENABLE_STATUS, CustomChars::ACTION);
    }
}