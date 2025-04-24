#include "main_menu.hpp"


namespace Engine {
    MainMenuScene::MainMenuScene() :
        Scene::Scene()
    {}

    void MainMenuScene::begin() {
        this->select_menu.begin();
    }

    Scene* MainMenuScene::tick() {
        Drivers::display_driver.print_center(0, "** WhirlBeat! **");

        select_menu.tick();
        Drivers::display_driver.clear_row(this->DESCRIPTION_ROW);
        Drivers::display_driver.print_center(this->DESCRIPTION_ROW, descriptions[select_menu.get_selected_idx()]);

        if (Drivers::button_driver_action.is_clicked()) {
            
        }

        return nullptr;
    }

    MainMenuScene main_menu_scene{};
}
