#pragma once

#include <drivers.hpp>
#include "../../base/base.hpp"
#include "../arrow/arrow.hpp"


namespace Engine {
    class SelectMenuScenePart : public ScenePart {
    public:
        int row;

        const char* const *choices;
        const size_t choices_count;

        ArrowsScenePart arrows;


        SelectMenuScenePart(const char* const choices[], const size_t choices_count, int row);

        void begin() override;
        void tick() override;

        void render();

        const char* get_selected_str();
        int get_selected_idx();


    private:
        int select_idx = 0;

        void render_lights();
    };
}