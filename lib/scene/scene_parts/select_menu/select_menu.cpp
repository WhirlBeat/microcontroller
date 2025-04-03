#include "select_menu.hpp"


namespace SceneParts {
    SelectMenu::SelectMenu(Vector<const char*> choices, int row, LCD::Display &display):
        row(row), display(display),
        arrows(row, display),
        choices(choices)
    {}

    void SelectMenu::render() {
        arrows.render();

        if (select_idx != previous_select_idx) {
            arrows.clear_without_arrows();
            display.print_center(0, choices[select_idx]);
            previous_select_idx = select_idx;
        }
    }

    void SelectMenu::on_btn_select_click() {
        select_idx++;
        if (select_idx >= choices.size()) select_idx = 0;
    }

    const char *SelectMenu::get_selected_str()
    {
        return choices[select_idx];
    }
}