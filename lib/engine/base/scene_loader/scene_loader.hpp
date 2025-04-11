#pragma once

#include "../scene/scene.hpp"



namespace Engine {
    class SceneLoader {
    public:
        Scene& scene;

        explicit SceneLoader(Scene& initial_scene);

        void tick();
    };
}