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

        size_t selected_char_idx = 0;

        const int row = 1;

        ScoreSubmitScene(const char* table_name, int score);

        void begin() override;
        Scene* tick() override;

    private:
        int get_char_col(int idx);
    };
}