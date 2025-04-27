#include "rhythm_setup.hpp"



namespace Engine {
    RhythmModeSetupScene::RhythmModeSetupScene() {}

    const char* const RhythmModeSetupScene::get_id() {
        return "rhythm_setup";
    }

    void RhythmModeSetupScene::init() {
        for (int idx = 0; idx < CHART_COUNT; idx++) {
            this->choices[idx] = charts[idx]->name;
        }
        this->choices[CHART_COUNT] = "Back";
        this->select_menu.init(this->choices, CHART_COUNT + 1, this->ROW_SELECT_MENU);
    }

    void RhythmModeSetupScene::tick() {
        Drivers::music_driver.play(SongIDs::SETUP_REMIX, true);
        this->select_menu.tick();

        Drivers::display_driver.print_center(this->ROW_TITLE, "R H Y T H M");
        Drivers::display_driver.print_center(this->ROW_BETA, "Beta mode.");
        Drivers::display_driver.print_center(this->ROW_INSTRUCTIONS, "Select a chart.");


        if (Drivers::button_driver_action.check_click()) {
            int selected_idx = this->select_menu.get_selected_idx();
            if (selected_idx == CHART_COUNT) {
                scene_loader.go_back_to_scene(SceneIds::MAIN_MENU);
                return;
            }

            this->play_scene.init(charts[selected_idx]);
            Drivers::music_driver.stop();
            scene_loader.switch_scene(&this->play_scene);
        }
    }
}