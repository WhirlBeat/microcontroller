#include "score_submit.hpp"



namespace Engine {
    ScoreSubmitScene::ScoreSubmitScene(const char* table_name, int score) :
        Scene::Scene(),
        table_name(table_name),
        score(score)
    {
        for (int i = 0; i < this->USERNAME_LENGTH; i++) {
            this->char_select_parts[i] = CharSelectScenePart(
                0,
                ((Drivers::display_driver.size_x - this->USERNAME_LENGTH) / 2) + i,
                row
            );
        }
    }

    Scene* ScoreSubmitScene::tick() {
        this->char_select_parts[0].tick();

        return nullptr;
    }
}