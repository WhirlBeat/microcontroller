#include "timing_setup.hpp"



namespace Engine {
    TimingModeSetupScene::TimingModeSetupScene() {}

    void TimingModeSetupScene::init() {
        this->mod_select_scene.init();
        this->select_menu.init(this->select_menu_choices, SELECT_MENU_CHOICES, this->ROW_SELECT_MENU);
    }

    void TimingModeSetupScene::tick() {
        Drivers::display_driver.print_center(this->ROW_TITLE, "T I M I N G");


        TimingMod* selected_mods[TIMING_MOD_COUNT];
        size_t selected_mods_count = 0;
        this->mod_select_scene.get_selected_mods(selected_mods, &selected_mods_count);

        String selected_mods_shorthand_str = String("No mods selected");

        if (selected_mods_count > 0) {
            String selected_mods_shorthands[TIMING_MOD_COUNT];
            for (int idx = 0; idx < selected_mods_count; idx++) {
                selected_mods_shorthands[idx] = String(selected_mods[idx]->get_shorthand());
            }

            String selected_mods_shorthand_str = String();
            for (int idx = 0; idx < selected_mods_count; idx++) {
                selected_mods_shorthand_str += (String("+") + selected_mods_shorthands[idx]);
                if (idx != selected_mods_count - 1) {
                    selected_mods_shorthand_str += " ";
                }
            }
        }

        Drivers::display_driver.print_center(this->ROW_SELECTED_MODS, selected_mods_shorthand_str.c_str());


        String multiplier_str = String("Multiplier: ") + String(this->mod_select_scene.get_total_multiplier(), 2) + "x";
        Drivers::display_driver.print_center(this->ROW_MULTIPLIER, multiplier_str.c_str());

        this->select_menu.tick();
    }
}