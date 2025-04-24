#include "base.hpp"



namespace Engine {
    TimingSettings::TimingSettings() {}

    TimingMod::TimingMod() {}

    void TimingMod::tick() {}
    TimingSettings TimingMod::modify_settings(TimingSettings settings) {
        return settings;
    }
}