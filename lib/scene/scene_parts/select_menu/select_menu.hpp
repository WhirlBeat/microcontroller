#pragma once

#include <managers.hpp>
#include <Vector.h>
#include "../../base/base.hpp"
#include "../arrow/arrow.hpp"


namespace SceneParts {
    class SelectMenu : public Scene::Part {
    public:
        bool rendered = false;

        int row;
        LCD::Display& display;
        SceneParts::Arrows arrows;

        Vector<const char*> choices;
        size_t select_idx = 0;
        size_t previous_select_idx = 1000;


        SelectMenu(Vector<const char*> choices, int row, LCD::Display& display);

        void render() override;

        void on_btn_select_click();

        const char* get_selected_str();
    };
}