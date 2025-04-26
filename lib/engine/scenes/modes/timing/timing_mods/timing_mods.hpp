#pragma once

#include "base/base.hpp"
#include "speed/speed.hpp"
#include "fade/fade.hpp"
#include "distract/distract.hpp"


namespace Engine {
    const int TIMING_MOD_COUNT = 3;
    extern TimingMod* timing_mods[TIMING_MOD_COUNT];
    float get_timing_mod_total_multiplier(TimingMod** mods, int mods_count);
}