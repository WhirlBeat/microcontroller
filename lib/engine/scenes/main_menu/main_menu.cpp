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
        Drivers::display_driver.print_center(0, "** WhirlBeat! **");

        select_menu.tick();
        Drivers::display_driver.clear_row(this->DESCRIPTION_ROW);
        Drivers::display_driver.print_center(this->DESCRIPTION_ROW, descriptions[select_menu.get_selected_idx()]);

        if (Drivers::button_driver_action.is_clicked()) {

        }
    }

    MainMenuScene main_menu_scene{};
}
