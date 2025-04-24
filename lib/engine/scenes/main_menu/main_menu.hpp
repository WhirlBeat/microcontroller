#pragma once

#include <drivers.hpp>
#include "../../scene_parts/scene_parts.hpp"
#include "../../base/base.hpp"


namespace Engine {
    class MainMenuScene : public Scene {
    public:
        static const size_t choices_count = 4;
        const char* choices[choices_count] = {
            "Timing", "Rhythm", "Leaderboards", "About"
        };
        const char* descriptions[choices_count] = {
            "The running light!",
            "Test your rhythm!",
            "View leaderboards!",
            "About this project!"
        };


        static const int CHOICE_ROW = 2;
        static const int DESCRIPTION_ROW = 3;

        SelectMenuScenePart select_menu{choices, choices_count, CHOICE_ROW};

        MainMenuScene();

        void begin() override;
        Scene* tick() override;
    };


    extern MainMenuScene main_menu_scene;
}