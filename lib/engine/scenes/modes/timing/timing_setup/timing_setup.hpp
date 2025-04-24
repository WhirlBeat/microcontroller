#pragma once

#include <base/base.hpp>
#include <scene_parts/scene_parts.hpp>
#include "../timing_mod_select/timing_mod_select.hpp"
#include "../timing_play/timing_play.hpp"



namespace Engine {
    class TimingModeModSelectScene;

    class TimingModeSetupScene : public Scene {
    public:
        static const int ROW_TITLE = 0;
        static const int ROW_SELECTED_MODS = 1;
        static const int ROW_MULTIPLIER = 2;
        static const int ROW_SELECT_MENU = 3;

        TimingModeModSelectScene mod_select_scene{};
        TimingModePlayScene play_scene{};

        static const int SELECT_MENU_CHOICES = 3;
        const char* select_menu_choices[SELECT_MENU_CHOICES] = {
            "Play",
            "Select Mods",
            "Info"
        };
        SelectMenuScenePart select_menu{};

        TimingModeSetupScene();

        const char* const get_id() override;

        void init();

        void tick() override;
    };
}