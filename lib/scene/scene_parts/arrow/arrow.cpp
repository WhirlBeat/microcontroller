#include "arrow.hpp"

namespace SceneParts {
    Arrows::Arrows(int row, LCD::Display& display) : display(display) {
        this->row = row;
    }

    void Arrows::render() {
        if (rendered) return;

        display.print_char_at(0, 0, LCD::CustomChars::ARROW_LEFT);
        display.print_char_at(-1, 0, LCD::CustomChars::ARROW_RIGHT);
        rendered = true;
    }

    void Arrows::clear_without_arrows() {
        display.clear_row_specific(1, row, display.size_x - 2);
    }
}