#include "rhythm_complete.hpp"



namespace Engine {
    RhythmCompleteScene::RhythmCompleteScene() {}

    void RhythmCompleteScene::init(int score, int max_combo, float accuracy) {
        this->score = score;
        this->max_combo = max_combo;
        this->accuracy = accuracy;
    }

    void RhythmCompleteScene::tick() {
        Drivers::music_driver.play(SongIDs::LEADERBOARD, true);

        Drivers::display_driver.print_center(this->ROW_CONGRATS, "Congratulations!");

        String score_str = String(this->score);
        Drivers::display_driver.print_center(this->ROW_SCORE, score_str.c_str());

        String stat_str = String(this->max_combo) + "x " + String(this->accuracy * 100, 2);
        Drivers::display_driver.print_center(this->ROW_STATISTICS, stat_str.c_str());

        Drivers::display_driver.print_char_at(0, this->ROW_EXIT, CustomChars::ACTION);
        Drivers::display_driver.print_center(this->ROW_EXIT, "Return to menu.");

        if (Drivers::button_driver_action.check_click()) {
            scene_loader.go_back_to_scene(SceneIds::MAIN_MENU);
        }
    }
}