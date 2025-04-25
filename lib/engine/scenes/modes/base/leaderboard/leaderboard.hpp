#pragma once

#include <drivers.hpp>

#include <scene_parts/scene_parts.hpp>
#include <base/base.hpp>


namespace Engine {
    class LeaderboardScene : public Scene {
    public:
        enum State {
            DISPLAY_ENTRIES,
            CONFIRM_EXIT,
            EXIT
        };


        State state;


        static const size_t CHOICES_COUNT = 2;
        const char* choices[CHOICES_COUNT] = {
            "No", "Yes"
        };

        SelectMenuScenePart confirm_exit_menu{};


        int load_count = 10;
        int center_on = -1;

        int display_starting_entry_idx;
        const int DISPLAY_ROWS = Drivers::display_driver.size_y - 1;
        const int DISPLAY_OFFSET = 1;

        static const int ROW_TITLE = 0;

        LeaderboardScene();

        virtual void init(int load_count = 10, int center_on = -1);

        void begin() override;
        void tick() override;

        virtual const char* get_name() = 0;
        virtual void load_entries() = 0;
        virtual int get_entry_count() = 0;
        virtual int get_center_idx() = 0;

        void update_display_entries_controls();
        void render_entries(int center_idx = 0);
        virtual void render_one_entry(int x, int y, int entry_idx) = 0;

        void tick_confirm_exit_scene_part();

    };
}