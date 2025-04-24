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
        Drivers::lights_driver.show();
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

        this->prepare_next_scene();

        this->get_current_scene()->begin();
    }

    void SceneLoader::go_back() {
        if (this->current_scene_idx < 0) return;
        this->current_scene_idx--;
        this->prepare_next_scene();
    }

    void SceneLoader::go_back_to_scene(const char* const scene_id) {
        this->prepare_next_scene();

        for (int i = this->current_scene_idx; i >= 0; i--) {
            if (strcmp(this->scene_stack[i]->get_id(), scene_id) == 0) {
                this->current_scene_idx = i;
                return;
            }
        }
    }

    void SceneLoader::prepare_next_scene() {
        Drivers::display_driver.clear_all();
        Drivers::lights_driver.clear_led_array();
    }

    SceneLoader scene_loader{};
}