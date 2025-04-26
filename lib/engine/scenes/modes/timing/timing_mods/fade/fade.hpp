#pragma once

#include "../base/base.hpp"



namespace Engine {
    class TimingModFade : public TimingMod {
    public:
        // Fade curve. 0 = none, (0, 1) = higher->sharper near goal, 1 = linear, (1-inf) = higher->sharper near start
        float fade_curve = 1;
        float black_threshold = 0.3;

        TimingModFade();
        const char* get_name() override;
        const char* get_description() override;
        const char* get_shorthand() override;
        const float get_multiplier() override;

        void init_start() override;
        void init_attempt() override;

        void on_next_frame(TimingEngineScenePart* engine) override;
    };


    extern TimingModFade timing_mod_fade;
}