#pragma once



namespace Engine {
    class Scene {
    public:
        Scene();

        virtual void on_enter();
        virtual Scene* tick();
        virtual void on_exit();
    };
}