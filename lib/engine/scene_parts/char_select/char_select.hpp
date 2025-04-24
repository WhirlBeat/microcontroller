#pragma once

#include <drivers.hpp>
#include "../../base/base.hpp"
#include "../arrow/arrow.hpp"


namespace Engine {
    const size_t CHAR_SELECT_CHOICES_SIZE = 36;
    const char CHAR_SELECT_CHOICES[CHAR_SELECT_CHOICES_SIZE] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
        'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
        'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3',
        '4', '5', '6', '7', '8', '9'
    };

    class CharSelectScenePart : public ScenePart {
    public:
        int selected_idx = 0;
        int x = 0;
        int y = 0;

        CharSelectScenePart();

        void init(int selected_idx = 0, int x = 0, int y = 0);

        void begin() override;
        void tick() override;

        void render();

        char get_selected_char();
    };
}