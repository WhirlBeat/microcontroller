#include "fade.hpp"



namespace Engine {
    TimingModFade::TimingModFade() {}

    const char* TimingModFade::get_name() {
        return "Fade";
    }

    const char* TimingModFade::get_description() {
        return "Invisible to you.";
    }

    const char* TimingModFade::get_shorthand() {
        return "FD";
    }

    const float TimingModFade::get_multiplier() {
        return 1.5F;
    }

    void TimingModFade::init_start() {}
    void TimingModFade::init_attempt() {}

    void TimingModFade::on_next_frame(TimingEngineScenePart* engine) {
        if (engine->state == TimingEngineScenePart::STOPPED) return;

        const int score = engine->calculate_score_raw();
        if (score == engine->max_score) return;

        const float ratio = (float)score / (float)(engine->max_score);
        float visible_percent = 1 - pow(ratio, 1.0F / this->fade_curve);

        const int current_led_idx = engine->get_shown_led_idx();
        CRGB* current = &Drivers::lights_driver.led_array[current_led_idx];

        if (visible_percent < this->black_threshold) {
            *current = CRGB::Black;
        } else {
            uint8_t scale = (uint8_t)(floor(visible_percent * 255.0F));
            current->nscale8(scale);
        }
    }

    TimingModFade timing_mod_fade{};
}