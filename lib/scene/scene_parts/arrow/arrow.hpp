#pragma once

#include <managers.hpp>
#include "../../base/base.hpp"


namespace SceneParts {
    class Arrows : public Scene::Part {
    public:
        bool rendered = false;
        int row;
        LCD::Display& display;

        Arrows(int row, LCD::Display& display);

        void render() override;

        void clear_without_arrows();
    };
}