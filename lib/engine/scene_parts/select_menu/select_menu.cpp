#include "select_menu.hpp"


namespace Engine {
    SelectMenuScenePart::SelectMenuScenePart(const char *const choices[], const size_t choices_count, int row) :
        ScenePart(),
        row(row),
        choices(choices), choices_count(choices_count),
        arrows(row)
    {}

    void SelectMenuScenePart::tick() {
        this->arrows.tick();

        if (Drivers::button_driver_left.is_clicked()) {
            select_idx--;
            if (select_idx < 0) select_idx = choices_count - 1;
        }

        if (Drivers::button_driver_right.is_clicked()) {
            select_idx++;
            if (select_idx >= (int)choices_count) select_idx = 0;
        }

        if (select_idx != previous_select_idx) {
            arrows.clear_without_arrows();
            Drivers::display_driver.print_center(0, choices[select_idx]);
            previous_select_idx = select_idx;
        }
    }


    const char * SelectMenuScenePart::get_selected_str()
    {
        return choices[select_idx];
    }
}