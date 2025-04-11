#include "scene.hpp"



namespace Engine {
    Scene::Scene() {}
    Scene::Scene(bool blank) : blank(blank) {}
    const Scene& Scene::tick() {
        return blank_scene;
    }
}