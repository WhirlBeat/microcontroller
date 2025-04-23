#include <drivers.hpp>

#include "scene_loader.hpp"



namespace Engine {
    SceneLoader::SceneLoader(Scene *initial_scene) :
        current_scene(initial_scene)
    {
        this->current_scene->on_enter();
    }

    void SceneLoader::tick() {
        Drivers::button_driver_left.tick();
        Drivers::button_driver_action.tick();
        Drivers::button_driver_right.tick();

        Scene *next_scene = this->current_scene->tick();

        Drivers::display_driver.render();

        if (next_scene) {
            this->current_scene->on_exit();

            this->current_scene = next_scene;
            this->current_scene->on_enter();
        }
    }
}