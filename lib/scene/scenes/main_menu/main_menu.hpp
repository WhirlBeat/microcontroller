#pragma once

#include <managers.hpp>
#include <Vector.h>
#include "../../scene_parts/scene_parts.hpp"
#include "../../base/base.hpp"


namespace SceneSources {
    class MainMenu : public Scene::Source {
    public:
        LCD::Display& display;
        SceneParts::SelectMenu select_menu;

        MainMenu(LCD::Display& display);

        const Scene::Source& render() override;

        void on_btn_action_click() override;
        void on_btn_select_click() override;

        
    };
}