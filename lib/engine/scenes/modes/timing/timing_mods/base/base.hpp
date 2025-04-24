#pragma once



namespace Engine {
    class TimingSettings {
    public:
        int ticks_per_loop = 200;
        double curve = 0.15;

        TimingSettings();
    };

    class TimingMod {
    public:
        TimingMod();

        virtual const char* get_name() = 0;
        virtual const char* get_description() = 0;

        virtual void tick();
        virtual TimingSettings modify_settings(TimingSettings settings);
    };
}