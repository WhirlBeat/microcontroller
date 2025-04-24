#include <drivers.hpp>

#include "scene_loader.hpp"



namespace Engine {
    SceneLoader::SceneLoader() {}

    void SceneLoader::tick() {
        Drivers::button_driver_left.tick();
        Drivers::button_driver_action.tick();
        Drivers::button_driver_right.tick();

        this->get_current_scene()->tick();

        Drivers::display_driver.render();
    }

    Scene *SceneLoader::get_current_scene() {
        if (this->current_scene_idx < 0) {
            return &this->blank_scene;
        }

        return this->scene_stack[this->current_scene_idx];
    }

    void SceneLoader::switch_scene(Scene *scene) {
        this->get_current_scene()->end();

        this->current_scene_idx++;
        this->scene_stack[this->current_scene_idx] = scene;

        this->get_current_scene()->begin();
    }

    void SceneLoader::go_back() {
        if (this->current_scene_idx < 0) return;
        this->current_scene_idx--;
    }

    void SceneLoader::go_back_to_scene(const char* const scene_id) {
        for (int i = this->current_scene_idx; i >= 0; i--) {
            if (strcmp(this->scene_stack[i]->get_id(), scene_id) == 0) {
                this->current_scene_idx = i;
                return;
            }
        }
    }


    SceneLoader scene_loader{};
}