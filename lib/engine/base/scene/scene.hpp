#pragma once



namespace Engine {
    class Scene {
    public:
        Scene();

        virtual Scene* tick();
    };
}