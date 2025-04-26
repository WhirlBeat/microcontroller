#pragma once

#include "../base/base.hpp"



namespace Engine {
    class TimingModSpeed : public TimingMod {
    public:
        TimingModSpeed();
        const char* get_name() override;
        const char* get_description() override;
        const char* get_shorthand() override;
        const float get_multiplier() override;

        void init_start() override;
        void init_attempt() override;

        TimingSettings modify_settings(TimingSettings settings) override;
    };


    extern TimingModSpeed timing_mod_speed;
}