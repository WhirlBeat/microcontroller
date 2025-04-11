#include "main_menu.hpp"


const char* choices[] = {
    "Start",
    "Settings",
    "About",
    "Exit"
};
const size_t choices_count = 4;


namespace Engine {
    MainMenuScene::MainMenuScene() :
        Scene::Scene(),
        select_menu(choices, choices_count, 0)
    {}

    const Scene& MainMenuScene::tick() {
        select_menu.tick();

        if (Drivers::button_driver_action.is_clicked()) {
            Drivers::display_driver.clear_row(1);
            Drivers::display_driver.print_center(1, select_menu.get_selected_str());
        }

        return blank_scene;
    }
}
