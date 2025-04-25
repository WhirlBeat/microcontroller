#pragma once

#include <drivers.hpp>

#include <scene_parts/scene_parts.hpp>
#include <base/base.hpp>
#include <scenes/main_menu/main_menu.hpp>
#include <scenes/modes/base/base.hpp>


namespace Engine {
    class TimingLeaderboardScene : public LeaderboardScene {
    public:
        JsonDocument response;

        TimingLeaderboardScene();

        const char* get_name() override;
        int get_entry_count() override;
        int get_center_idx() override;
        void load_entries() override;
        void render_one_entry(int x, int y, int entry_idx) override;
    };
}