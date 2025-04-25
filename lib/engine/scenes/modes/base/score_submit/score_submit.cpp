#include "score_submit.hpp"



namespace Engine {
    const char* ScoreSubmitScene::confirm_choices[confirm_choices_count] = {"No, edit name", "Yes, submit score"};

    ScoreSubmitScene::ScoreSubmitScene() : Scene::Scene() {
        for (int i = 0; i < this->USERNAME_LENGTH; i++) {
            this->char_select_parts[i] = CharSelectScenePart();
            this->char_select_parts[i].init(0, this->get_char_col(i), 2);
        }
    }

    void ScoreSubmitScene::init(const char* table_name, int score) {
        this->confirm_menu.init(confirm_choices, confirm_choices_count, 3);
        this->table_name = table_name;
        this->score = score;
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

            scene_loader.switch_scene(&this->leaderboard_scene);
        }
    }

    void ScoreSubmitScene::tick_state_setting_username() {
        Drivers::display_driver.print_center(0, "New score!");

        String score_str = String("---- ") + this->score + " ----";
        Drivers::display_driver.print_center(1, score_str.c_str());


        Drivers::display_driver.print_at(0, 2, "Enter name:");

        for (int i = 0; i < this->USERNAME_LENGTH; i++) {
            this->char_select_parts[i].render();
        }
        this->char_select_parts[this->selected_char_idx].tick();

        Drivers::display_driver.print_char_at(this->get_char_col(0) - 2, 2, CustomChars::ARROW_UP_DOWN);
        Drivers::display_driver.print_char_at(this->get_char_col(this->USERNAME_LENGTH - 1) + 2, 2, CustomChars::ARROW_UP_DOWN);


        if (Drivers::button_driver_action.is_clicked()) {
            this->selected_char_idx++;
            if (this->selected_char_idx >= this->USERNAME_LENGTH) {
                this->selected_char_idx = 0;
                this->state = CONFIRM;
                return;
            }
        }

        Drivers::display_driver.clear_row(3);
        Drivers::display_driver.print_at(this->get_char_col(this->selected_char_idx), 3, "^");
    }

    void ScoreSubmitScene::tick_confirm() {
        Drivers::display_driver.print_center(0, "Is this correct?");

        String score_str = String(this->score) + " -- by " + this->get_username();
        Drivers::display_driver.print_center(1, score_str.c_str());

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

    void Engine::ScoreSubmitScene::submit_score() {
        String username = this->get_username();

        JsonDocument request_body;
        request_body["username"] = username.c_str();
        request_body["score"] = this->score;
        request_body["multiplier"] = 1.0F;

        JsonArray array = request_body.createNestedArray("mods");
        array.add("FF");
        array.add("SS");

        JsonDocument response = Drivers::api_driver.make_post_request(this->table_name, request_body);
        int id = response["moreInfo"]["id"].as<int>();

        this->leaderboard_scene.init(this->table_name, 10, id);
    }

    int ScoreSubmitScene::get_char_col(int idx) {
        return Drivers::display_driver.size_x - this->USERNAME_LENGTH - 2 + idx;
    }
}  // namespace Engine