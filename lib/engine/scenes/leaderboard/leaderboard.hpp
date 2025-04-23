#pragma once

#include <drivers.hpp>

#include "../../scene_parts/scene_parts.hpp"
#include "../../base/base.hpp"
#include "../main_menu/main_menu.hpp"


namespace Engine {
    class LeaderboardEntry {
    public:
        int id;
        String username;
        int score;
        int placement;

        LeaderboardEntry(int id, String username, int score, int placement);
        LeaderboardEntry();
    };



    class LeaderboardScene : public Scene {
    public:
        enum State {
            DISPLAY_ENTRIES,
            CONFIRM_EXIT,
            EXIT
        };


        State state = DISPLAY_ENTRIES;


        static const size_t choices_count = 2;
        const char* choices[choices_count] = {
            "No", "Yes"
        };

        SelectMenuScenePart confirm_exit_scene_part{choices, choices_count, 2};


        const char* table_name = nullptr;
        int load_count = 10;
        int center_on = -1;

        static const int MAX_ENTRY_COUNT = 20;
        LeaderboardEntry entries[MAX_ENTRY_COUNT];
        int actual_entry_count = 0;

        int current_center_idx = 0;

        LeaderboardScene();

        void init(const char* table_name, int load_count, int center_on = -1);

        void begin() override;
        Scene* tick() override;

        void load_entries();
        void update_display_entries_controls();
        void render_entries(int center_idx = 0);

        void tick_confirm_exit_scene_part();
    };
}