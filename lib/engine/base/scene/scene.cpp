#include "scene.hpp"



namespace Engine {
    Scene::Scene() {}

    void Scene::on_enter() {}

    Scene* Scene::tick() {
        return nullptr;
    }

    void Scene::on_exit() {}
}