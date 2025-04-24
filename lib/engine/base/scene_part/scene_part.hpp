#pragma once



namespace Engine {
    class ScenePart {
    public:
        ScenePart();
        virtual void begin();
        virtual void tick();
    };
}