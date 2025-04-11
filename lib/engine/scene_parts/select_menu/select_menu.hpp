#pragma once

#include <drivers.hpp>
#include <Vector.h>
#include "../../base/base.hpp"
#include "../arrow/arrow.hpp"


namespace Engine {
    
    class SelectMenuScenePart : public ScenePart {
    public:
        bool rendered = false;

        int row;

        const char* const *choices;
        const size_t choices_count;

        ArrowsScenePart arrows;

        int select_idx = 0;
        int previous_select_idx = 1000;


        SelectMenuScenePart(const char* const choices[], const size_t choices_count, int row);

        void tick() override;

        const char * get_selected_str();
    };
}