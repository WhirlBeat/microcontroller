#include "score_submit.hpp"



namespace Engine {
    const char* ScoreSubmitScene::confirm_choices[confirm_choices_count] = {"No, edit name", "Yes, submit score"};

    ScoreSubmitScene::ScoreSubmitScene() : Scene::Scene() {}

    void ScoreSubmitScene::init() {
        this->confirm_menu.init(confirm_choices, confirm_choices_count, 3);

        this->state = SETTING_USERNAME;
        for (int i = 0; i < this->USERNAME_LENGTH; i++) {
            this->char_select_parts[i] = CharSelectScenePart();
            this->char_select_parts[i].init(0, this->get_char_col(i), this->ROW_USERNAME);
        }

        this->selected_char_idx = 0;
    }

    void ScoreSubmitScene::begin() {
        for (int i = 0; i < this->USERNAME_LENGTH; i++) {
            this->char_select_parts[i].begin();
        }
    }

    void ScoreSubmitScene::tick() {
        Drivers::display_driver.clear_all();
        if (this->state == SETTING_USERNAME) {
            this->tick_state_setting_username();
        } else if (this->state == CONFIRM) {
            this->tick_confirm();
        } else if (this->state == SUBMIT) {
            this->submit_score();
        }
    }

    void ScoreSubmitScene::tick_state_setting_username() {
        Drivers::display_driver.print_center(0, "New score!");

        this->render_score_summary();

        Drivers::display_driver.print_at(0, this->ROW_USERNAME, "Enter name:");

        for (int i = 0; i < this->USERNAME_LENGTH; i++) {
            this->char_select_parts[i].render();
        }
        this->char_select_parts[this->selected_char_idx].tick();

        Drivers::display_driver.print_char_at(this->get_char_col(0) - 2, this->ROW_USERNAME, CustomChars::ARROW_UP_DOWN);
        Drivers::display_driver.print_char_at(this->get_char_col(this->USERNAME_LENGTH - 1) + 2, this->ROW_USERNAME, CustomChars::ARROW_UP_DOWN);


        if (Drivers::button_driver_action.is_clicked()) {
            this->selected_char_idx++;
            if (this->selected_char_idx >= this->USERNAME_LENGTH) {
                this->selected_char_idx = 0;
                this->state = CONFIRM;
                return;
            }
        }

        Drivers::display_driver.clear_row(this->ROW_SELECT);
        Drivers::display_driver.print_at(this->get_char_col(this->selected_char_idx), this->ROW_SELECT, "^");
    }

    void ScoreSubmitScene::tick_confirm() {
        Drivers::music_driver.play(SongIDs::HIGHSCORE);

        Drivers::display_driver.print_center(0, "Is this correct?");

        this->render_score_summary();

        String username_str = String("by ") + this->get_username();
        Drivers::display_driver.print_center(this->ROW_USERNAME, username_str.c_str());

        this->confirm_menu.tick();

        if (Drivers::button_driver_action.is_clicked()) {
            if (this->confirm_menu.get_selected_idx() == 0) {
                this->state = SETTING_USERNAME;
                return;
            } else {
                this->state = SUBMIT;
                return;
            }
        }
    }

    String ScoreSubmitScene::get_username() {
        String result = "";
        for (int i = 0; i < this->USERNAME_LENGTH; i++) {
            result += this->char_select_parts[i].get_selected_char();
        }

        return result;
    }

    int ScoreSubmitScene::get_char_col(int idx) {
        return Drivers::display_driver.size_x - this->USERNAME_LENGTH - 2 + idx;
    }
}  // namespace Engine