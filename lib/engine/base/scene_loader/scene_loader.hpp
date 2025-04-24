#pragma once

#include <stack>

#include "../scene/scene.hpp"



namespace Engine {
    class SceneLoader {
    public:
        static const size_t MAX_SCENES = 20;
        Scene* scene_stack[MAX_SCENES];
        int current_scene_idx = -1;

        Scene blank_scene{};

        SceneLoader();

        void tick();

        Scene* get_current_scene();

        void switch_scene(Scene *scene);
        void go_back();
        void go_back_to_scene(const char* scene_id);
    };


    extern SceneLoader scene_loader;
}