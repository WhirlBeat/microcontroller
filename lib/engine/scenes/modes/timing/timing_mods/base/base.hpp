#pragma once

#include <scenes/modes/timing/timing_engine/timing_engine.hpp>



namespace Engine {
    class TimingMod {
    public:
        TimingMod();

        virtual const char* get_name() = 0;
        virtual const char* get_description() = 0;
        virtual const char* get_shorthand() = 0;
        virtual const float get_multiplier() = 0;

        virtual void init_start() = 0;
        virtual void init_attempt() = 0;

        virtual void on_next_frame(TimingEngineScenePart *engine);

        virtual void tick();
        virtual TimingSettings modify_settings(TimingSettings settings);
    };
}