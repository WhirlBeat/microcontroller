#include "score_submit.hpp"



namespace Engine {
    ScoreSubmitScene::ScoreSubmitScene(const char* table_name, int score) :
        Scene::Scene(),
        table_name(table_name),
        score(score)
    {
        for (int i = 0; i < this->USERNAME_LENGTH; i++) {
            this->char_select_parts[i] = CharSelectScenePart(0, this->get_char_col(i), row);
        }
    }

    void ScoreSubmitScene::begin() {
        for (int i = 0; i < this->USERNAME_LENGTH; i++) {
            this->char_select_parts[i].begin();
        }
    }

    Scene* ScoreSubmitScene::tick() {
        this->char_select_parts[this->selected_char_idx].tick();

        if (Drivers::button_driver_action.is_clicked()) {
            this->selected_char_idx++;
            if (this->selected_char_idx >= this->USERNAME_LENGTH) {
                this->selected_char_idx = 0;
            }
        }

        Drivers::display_driver.clear_row(this->row + 1);
        Drivers::display_driver.print_at(this->get_char_col(this->selected_char_idx), this->row + 1, "^");

        return nullptr;
    }
    int ScoreSubmitScene::get_char_col(int idx) {
        return ((Drivers::display_driver.size_x - this->USERNAME_LENGTH) / 2) + idx;
    }
}