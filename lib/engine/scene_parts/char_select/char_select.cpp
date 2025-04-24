#include <colors.hpp>

#include "char_select.hpp"



namespace Engine {
    CharSelectScenePart::CharSelectScenePart() {}

    void CharSelectScenePart::init(int selected_idx, int x, int y) {
        this->selected_idx = selected_idx;
        this->x = x;
        this->y = y;

        if (selected_idx >= CHAR_SELECT_CHOICES_SIZE) {
            selected_idx = 0;
        }
    }


    void CharSelectScenePart::begin() {
        this->render();
    }


    void CharSelectScenePart::tick() {
        if (Drivers::button_driver_left.is_click_repeated(50, 500)) {
            selected_idx--;
            if (selected_idx < 0) {
                selected_idx = CHAR_SELECT_CHOICES_SIZE - 1;
            }
        }

        if (Drivers::button_driver_right.is_click_repeated(50, 500)) {
            selected_idx++;
            if (selected_idx >= CHAR_SELECT_CHOICES_SIZE) {
                selected_idx = 0;
            }
        }

        this->render();
    }


    void CharSelectScenePart::render() {
        char c_str[2];
        c_str[0] = this->get_selected_char();
        c_str[1] = '\0';
        Drivers::display_driver.print_at(x, y, c_str);
    }

    char CharSelectScenePart::get_selected_char() {
        return CHAR_SELECT_CHOICES[selected_idx];
    }
}  // namespace Engine