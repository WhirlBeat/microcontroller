#include "speed.hpp"



namespace Engine {
    Engine::TimingModSpeed::TimingModSpeed() {}

    const char* Engine::TimingModSpeed::get_name() {
        return "Speed";
    }

    const char* Engine::TimingModSpeed::get_description() {
        return "Faster, faster!";
    }

    const char* TimingModSpeed::get_shorthand() {
        return "SP";
    }

    const float TimingModSpeed::get_multiplier() {
        return 1.0F;
    }

    void TimingModSpeed::init_start() {}
    void TimingModSpeed::init_attempt() {}

    TimingSettings TimingModSpeed::modify_settings(TimingSettings settings) {
        settings.ticks_per_loop = (int)((float)(settings.ticks_per_loop) / 1.75F);
        return settings;
    }

    TimingModSpeed timing_mod_speed{};
}