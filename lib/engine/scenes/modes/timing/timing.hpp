#pragma once

#include <base/base.hpp>
#include <scene_parts/scene_parts.hpp>



namespace Engine {
    class TimingModePlayScene : public Scene {
    public:
        TimingScenePart current_timing_sp{};
        int total_score = 0;

        TimingModePlayScene();

        Scene* tick() override;
    };
}