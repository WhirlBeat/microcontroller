#pragma once

#include "../base/base.hpp"



namespace Engine {
    class TimingModDistract : public TimingMod {
    public:
        float density = 0.4;
        int change_every = 176;

        CRGB mask[ComponentParams::LED_COUNT];

        int timer = 0;

        TimingModDistract();
        const char* get_name() override;
        const char* get_description() override;
        const char* get_shorthand() override;
        const float get_multiplier() override;

        void init_start() override;
        void init_attempt() override;

        void init();

        void on_next_frame(TimingEngineScenePart* engine) override;

    private:
        void generate_mask();
    };


    extern TimingModDistract timing_mod_distract;
}