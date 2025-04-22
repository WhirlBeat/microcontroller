#include "main_menu.hpp"


const size_t choices_count = 10;
const char* choices[choices_count] = {
    "Start",
    "Settings",
    "About",
    "Exit",
    "More",
    "Moooorreee",
    "Lmao?",
    "wawa",
    "wawawawawawa",
    "wah"
};


namespace Engine {
    MainMenuScene::MainMenuScene() :
        Scene::Scene(),
        select_menu(choices, choices_count, 0)
    {}

    Scene* MainMenuScene::tick() {
        select_menu.tick();

        if (Drivers::button_driver_action.is_clicked()) {
            Drivers::display_driver.clear_row(1);
            Drivers::display_driver.print_center(1, select_menu.get_selected_str());
        }

        return nullptr;
    }

    MainMenuScene main_menu_scene{};
}
