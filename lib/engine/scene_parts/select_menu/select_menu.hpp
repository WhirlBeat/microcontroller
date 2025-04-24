#pragma once

#include <drivers.hpp>
#include "../../base/base.hpp"
#include "../arrow/arrow.hpp"


namespace Engine {
    class SelectMenuScenePart : public ScenePart {
    public:
        int row = 0;

        const char* *choices = nullptr;
        size_t choices_count = 0;

        ArrowsScenePart arrows{};


        SelectMenuScenePart();

        void init(const char* choices[], size_t choices_count, int row);

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