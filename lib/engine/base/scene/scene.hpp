#pragma once



namespace Engine {
    class Scene {
    public:
        Scene();

        virtual const char* const get_id();

        virtual void begin();
        virtual void tick();
        virtual void end();
    };


    namespace SceneIds {
        const char* const MAIN_MENU = "main_menu";
    }
}