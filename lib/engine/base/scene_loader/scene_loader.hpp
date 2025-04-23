#pragma once

#include "../scene/scene.hpp"



namespace Engine {
    class SceneLoader {
    public:
        Scene *current_scene;
        bool first_begin_called = false;

        explicit SceneLoader(Scene *initial_scene);

        void tick();
    };
}