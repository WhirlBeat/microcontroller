#include "distract.hpp"

#include <colors.hpp>



namespace Engine {
    TimingModDistract::TimingModDistract() {}

    const char* TimingModDistract::get_name() {
        return "Distract";
    }

    const char* TimingModDistract::get_description() {
        return "Eyes can deceive.";
    }

    const char* TimingModDistract::get_shorthand() {
        return "DS";
    }

    const float TimingModDistract::get_multiplier() {
        return 1.0F;
    }

    void TimingModDistract::init_start() {
        this->init();
    }
    void TimingModDistract::init_attempt() {
        this->init();
    }

    void TimingModDistract::init() {
        this->timer = 0;

        this->generate_mask();
    }

    void TimingModDistract::on_next_frame(TimingEngineScenePart* engine) {
        if (engine->state == TimingEngineScenePart::STOPPED) return;


        for (int idx = 0; idx < ComponentParams::LED_COUNT; idx++) {
            if (idx == engine->goal_led_idx) continue;

            CRGB* current = &Drivers::lights_driver.led_array[idx];
            if (*current != CRGB::Black) continue;

            *current = this->mask[idx];
        }

        this->timer++;
        if (this->timer < this->change_every) return;
        this->timer = 0;

        this->generate_mask();
    }

    void TimingModDistract::generate_mask() {
        for (int idx = 0; idx < ComponentParams::LED_COUNT; idx++) {
            this->mask[idx] = CRGB::Black;
        }

        for (int idx = 0; idx < ComponentParams::LED_COUNT; idx++) {
            const float show_roll = (float)(random(0, 256)) / 255.0F;
            if (show_roll > this->density) continue;

            const uint8_t color_roll = random(0, 256);
            this->mask[idx] = ColorFromPalette(
                Gradients::rainbow_palette,
                color_roll
            );
        }
    }

    TimingModDistract timing_mod_distract{};
}