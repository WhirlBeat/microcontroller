#pragma once

#include <base/base.hpp>
#include <scene_parts/scene_parts.hpp>



namespace Engine {
    class TimingModeModSelectScene;

    class TimingModeSetupScene : public Scene {
    public:
        TimingModeSetupScene();

        void tick() override;
    };
}