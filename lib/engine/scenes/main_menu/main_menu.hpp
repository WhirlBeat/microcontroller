#pragma once

#include <drivers.hpp>
#include <scene_parts/scene_parts.hpp>
#include <base/base.hpp>
#include "../modes/modes.hpp"


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


        TimingModeSetupScene timing_mode_scene;
        RhythmModeSetupScene rhythm_mode_scene;


        static const int ROW_SELECT_MENU = 2;
        static const int DESCRIPTION_ROW = 3;

        SelectMenuScenePart select_menu{};

        MainMenuScene();

        const char* const get_id() override;

        void init();

        void begin() override;
        void tick() override;
    };


    extern MainMenuScene main_menu_scene;
}