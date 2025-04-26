#include "base.hpp"



namespace Engine {
    TimingMod::TimingMod() {}

    void TimingMod::on_next_frame(TimingEngineScenePart *engine) {}

    void TimingMod::tick() {}
    TimingSettings TimingMod::modify_settings(TimingSettings settings) {
        return settings;
    }
}