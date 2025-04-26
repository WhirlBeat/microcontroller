#include "timing_mods.hpp"


namespace Engine {
    TimingMod* timing_mods[TIMING_MOD_COUNT] = {
        &timing_mod_speed,
        &timing_mod_fade
    };


    float get_timing_mod_total_multiplier(TimingMod** mods, int mods_count) {
        float multiplier = 1.0f;
        for (int idx = 0; idx < mods_count; idx++) {
            multiplier *= mods[idx]->get_multiplier();
        }

        return multiplier;
    }
}