#pragma once

#include "../scene/scene.hpp"



namespace Engine {
    class SceneLoader {
    public:
        Scene *current_scene;

        explicit SceneLoader(Scene *initial_scene);

        void tick();
    };
}