#include "main_menu.hpp"


Vector<const char*> get_choices() {
    const char* choices_storage[3];
    Vector<const char*> choices(choices_storage);
    choices.push_back("wawa");
    choices.push_back("wawa 2");
    choices.push_back("wew");

    return choices;
}


namespace SceneSources {
    MainMenu::MainMenu(LCD::Display &display) :
        Source::Source(),
        display(display),
        select_menu(get_choices(), 0, display)
    {}

    const Scene::Source& MainMenu::render() {
        select_menu.render();

        return Scene::blank_source;
    }

    void MainMenu::on_btn_action_click() {
        display.clear_row(1);
        display.print_center(1, select_menu.get_selected_str());
    }

    void MainMenu::on_btn_select_click() {
        select_menu.on_btn_select_click();
    }
}
