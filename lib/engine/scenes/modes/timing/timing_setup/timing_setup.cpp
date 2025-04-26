#include "timing_setup.hpp"



namespace Engine {
    TimingModeSetupScene::TimingModeSetupScene() {}

    const char* const TimingModeSetupScene::get_id() {
        return "timing_setup";
    }

    void TimingModeSetupScene::init() {
        this->mod_select_scene.init();
        this->select_menu.init(this->select_menu_choices, SELECT_MENU_CHOICES, this->ROW_SELECT_MENU);
    }

    void TimingModeSetupScene::tick() {
        if (this->mod_select_scene.is_mods_enabled()) Drivers::music_driver.play(SongIDs::SETUP_REMIX, true);
        else Drivers::music_driver.play(SongIDs::SETUP, true);

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

            selected_mods_shorthand_str = String();
            for (int idx = 0; idx < selected_mods_count; idx++) {
                selected_mods_shorthand_str += (String("+") + selected_mods_shorthands[idx]);
                if (idx != selected_mods_count - 1) {
                    selected_mods_shorthand_str += " ";
                }
            }
        }

        Drivers::display_driver.print_center(this->ROW_SELECTED_MODS, selected_mods_shorthand_str.c_str());


        String multiplier_str =
            String("Multiplier: ") +
            String(get_timing_mod_total_multiplier(selected_mods, selected_mods_count), 2) +
            "x";
        Drivers::display_driver.print_center(this->ROW_MULTIPLIER, multiplier_str.c_str());

        this->select_menu.tick();


        int selected_idx = this->select_menu.get_selected_idx();
        if (Drivers::button_driver_action.is_clicked()) {
            if (selected_idx == 0) {
                this->play_scene.init(selected_mods, selected_mods_count);
                scene_loader.switch_scene(&this->play_scene);
            } else if (selected_idx == 1) {
                scene_loader.switch_scene(&this->mod_select_scene);
            } else if (selected_idx == 3) {
                scene_loader.go_back_to_scene(SceneIds::MAIN_MENU);
            }
        }
    }
}