#pragma once

#include <base/base.hpp>
#include <scene_parts/scene_parts.hpp>
#include "../timing_mods/timing_mods.hpp"



namespace Engine {
    class TimingModeModSelectScene : public Scene {
    public:
        TimingMod* mods[TIMING_MOD_COUNT];
        bool mod_select_mask[TIMING_MOD_COUNT];

        SelectMenuScenePart select_menu{};
        const char* choices[TIMING_MOD_COUNT + 1];

        static const int ROW_SELECT_MENU = 0;
        static const int ROW_DESC = 1;
        static const int ROW_ENABLE_STATUS = 3;

        TimingModeModSelectScene();

        void init();

        void tick() override;
    };
}