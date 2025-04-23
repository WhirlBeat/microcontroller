#pragma once



namespace Engine {
    class Scene {
    public:
        Scene();

        virtual void begin();
        virtual Scene* tick();
        virtual void end();
    };
}