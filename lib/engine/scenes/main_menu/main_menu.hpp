#pragma once

#include <drivers.hpp>
#include <Vector.h>
#include "../../scene_parts/scene_parts.hpp"
#include "../../base/base.hpp"


namespace Engine {
    class MainMenuScene : public Scene {
    public:
        SelectMenuScenePart select_menu;

        MainMenuScene();

        const Scene& tick() override;
    };
}