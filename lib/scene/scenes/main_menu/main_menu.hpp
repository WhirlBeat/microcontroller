#pragma once

#include <managers.hpp>
#include "../../scene_parts/scene_parts.hpp"
#include "../../base/base.hpp"


namespace SceneSources {
    class MainMenu : public Scene::Source {
    public:
        int choices_length = 3;
        const char* choices[3] = {
            "choice 1",
            "choice 2aa",
            "choice 3"
        };
        int select_idx = 0;
        int previous_select_idx = -1000;

        LCD::Display& display;
        SceneParts::Arrows arrows;

        MainMenu(LCD::Display& display);

        const Scene::Source& render() override;

        void on_btn_action_click() override;
        void on_btn_up_click() override;
        void on_btn_down_click() override;
    };
}