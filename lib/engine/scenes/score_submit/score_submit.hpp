#pragma once

#include <drivers.hpp>

#include "../../scene_parts/scene_parts.hpp"
#include "../../base/base.hpp"
#include "../main_menu/main_menu.hpp"


namespace Engine {
    class ScoreSubmitScene : public Scene {
    public:
        const char* table_name;
        int score;

        static const int USERNAME_LENGTH = 5;
        CharSelectScenePart char_select_parts[USERNAME_LENGTH];

        const int row = 1;

        ScoreSubmitScene(const char* table_name, int score);

        Scene* tick() override;
    };
}