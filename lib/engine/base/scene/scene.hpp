#pragma once



namespace Engine {
    class Scene {
    public:
        bool blank = true;

        Scene();
        explicit Scene(bool blank);

        virtual const Scene& tick();
    };

    const Scene blank_scene = Scene(true);
}