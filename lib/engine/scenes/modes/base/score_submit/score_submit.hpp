#pragma once

#include <drivers.hpp>

#include <scene_parts/scene_parts.hpp>
#include <base/base.hpp>

#include "../leaderboard/leaderboard.hpp"


namespace Engine {
    class ScoreSubmitScene : public Scene {
    public:
        enum State {
            SETTING_USERNAME,
            CONFIRM,
            SUBMIT
        };


        State state;

        static const int USERNAME_LENGTH = 3;
        CharSelectScenePart char_select_parts[USERNAME_LENGTH];

        size_t selected_char_idx;

        static const size_t confirm_choices_count = 2;
        static const char* confirm_choices[confirm_choices_count];
        SelectMenuScenePart confirm_menu{};


        static const int ROW_MESSAGE = 0;
        static const int ROW_SCORE_SUMMARY = 1;
        static const int ROW_USERNAME = 2;
        static const int ROW_SELECT = 3;

        ScoreSubmitScene();
        void init();

        void begin() override;
        void tick() override;

        void tick_state_setting_username();
        void tick_confirm();

        virtual void render_score_summary() = 0;

        String get_username();
        virtual void submit_score() = 0;

    private:
        int get_char_col(int idx);
    };
}