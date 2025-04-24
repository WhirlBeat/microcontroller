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
        return "FF";
    }

    const float TimingModSpeed::get_multiplier() {
        return 1.0F;
    }

    TimingSettings TimingModSpeed::modify_settings(TimingSettings settings) {
        settings.ticks_per_loop /= 2;
        return settings;
    }

    TimingModSpeed timing_mod_speed{};
}