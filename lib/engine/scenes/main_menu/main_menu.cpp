#include "main_menu.hpp"


namespace Engine {
    MainMenuScene::MainMenuScene() :
        Scene::Scene()
    {}

    const char* const MainMenuScene::get_id() {
        return SceneIds::MAIN_MENU;
    }


    void MainMenuScene::init() {
        this->select_menu.init(this->choices, this->choices_count, this->ROW_SELECT_MENU);
    }

    void MainMenuScene::begin() {
        this->select_menu.begin();
    }


    void MainMenuScene::tick() {
        Drivers::music_driver.play(SongIDs::MAIN_MENU, true);

        Drivers::display_driver.print_center(0, "** WhirlBeat! **");

        select_menu.tick();
        Drivers::display_driver.clear_row(this->DESCRIPTION_ROW);
        Drivers::display_driver.print_center(this->DESCRIPTION_ROW, descriptions[select_menu.get_selected_idx()]);

        if (Drivers::button_driver_action.check_click()) {
            if (this->select_menu.get_selected_idx() == 0) {
                this->timing_mode_scene.init();
                scene_loader.switch_scene(&this->timing_mode_scene);
            } else if (this->select_menu.get_selected_idx() == 1) {
                this->rhythm_mode_scene.init();
                scene_loader.switch_scene(&this->rhythm_mode_scene);
            }
        }
    }

    MainMenuScene main_menu_scene{};
}
