#include "main_menu.hpp"


namespace SceneSources {
    MainMenu::MainMenu(LCD::Display &display) : Source::Source(), display(display), arrows(0, display) {}

    const Scene::Source& MainMenu::render() {
        arrows.render();

        if (select_idx != previous_select_idx) {
            arrows.clear_without_arrows();
            display.print_center(0, choices[select_idx]);
            previous_select_idx = select_idx;
        }

        return Scene::blank_source;
    }

    void MainMenu::on_btn_action_click() {
        display.clear_row(1);
        display.print_center(1, choices[select_idx]);
    }

    void MainMenu::on_btn_up_click() {
        select_idx++;
        if (select_idx >= choices_length) select_idx = 0;
    }

    void MainMenu::on_btn_down_click() {
        select_idx--;
        if (select_idx < 0) select_idx = choices_length - 1;
    }
}
