#pragma once

#include <drivers.hpp>

#include "../../scene_parts/scene_parts.hpp"
#include "../../base/base.hpp"

#include "../leaderboard/leaderboard.hpp"
#include "../main_menu/main_menu.hpp"


namespace Engine {
    class ScoreSubmitScene : public Scene {
    public:
        enum State {
            SETTING_USERNAME,
            CONFIRM,
            SUBMIT
        };


        State state = SETTING_USERNAME;
        LeaderboardScene leaderboard_scene{};

        const char* table_name = nullptr;
        int score = 0;

        static const int USERNAME_LENGTH = 3;
        CharSelectScenePart char_select_parts[USERNAME_LENGTH];
        
        size_t selected_char_idx = 0;

        static const size_t confirm_choices_count = 2;
        static const char* confirm_choices[confirm_choices_count];
        SelectMenuScenePart confirm_menu{};

        ScoreSubmitScene();
        void init(const char* table_name, int score);

        void begin() override;
        void tick() override;


        void tick_state_setting_username();
        void tick_confirm();

        String get_username();
        void submit_score();

    private:
        int get_char_col(int idx);
    };
}