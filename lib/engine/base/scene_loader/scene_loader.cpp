#include <drivers.hpp>

#include "scene_loader.hpp"



namespace Engine {
    SceneLoader::SceneLoader(Scene& initial_scene) :
        scene(initial_scene)
    {}

    void SceneLoader::tick() {
        const Scene& next_scene = this->scene.tick();

        Drivers::button_driver_left.tick();
        Drivers::button_driver_action.tick();
        Drivers::button_driver_right.tick();

        if (!next_scene.blank) {
            this->scene = next_scene;
        }
    }
}