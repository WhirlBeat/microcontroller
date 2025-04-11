#include "arrow.hpp"



namespace Engine {
    ArrowsScenePart::ArrowsScenePart(int row) {
        this->row = row;
    }

    void ArrowsScenePart::tick() {
        if (rendered) return;

        Drivers::display_driver.print_char_at(0, 0, CustomChars::ARROW_LEFT);
        Drivers::display_driver.print_char_at(-1, 0, CustomChars::ARROW_RIGHT);
        rendered = true;
    }

    void ArrowsScenePart::clear_without_arrows() {
        Drivers::display_driver.clear_specific(1, row, Drivers::display_driver.size_x - 2);
    }
}