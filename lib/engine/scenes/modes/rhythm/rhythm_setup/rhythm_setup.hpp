#pragma once

#include <base/base.hpp>
#include <scene_parts/scene_parts.hpp>

#include "../rhythm_play/rhythm_play.hpp"



namespace Engine {
    class RhythmModeSetupScene : public Scene {
    public:
        static const int ROW_TITLE = 0;
        static const int ROW_BETA = 1;
        static const int ROW_INSTRUCTIONS = 2;
        static const int ROW_SELECT_MENU = 3;

        const char* choices[CHART_COUNT];
        SelectMenuScenePart select_menu{};

        RhythmModePlayScene play_scene{};

        RhythmModeSetupScene();

        const char* const get_id() override;

        void init();

        void tick() override;
    };
}