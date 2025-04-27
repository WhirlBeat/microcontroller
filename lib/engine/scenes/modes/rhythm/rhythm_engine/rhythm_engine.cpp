#include <colors.hpp>

#include "rhythm_engine.hpp"




namespace Engine {
    RhythmEngineScenePart::RhythmEngineScenePart() : ScenePart() {}

    void RhythmEngineScenePart::init(RhythmChart *chart) {
        this->state = STARTING;
        this->start_time = 0;
        this->offset = chart->offset;

        this->song_id = chart->song_id;

        for (int idx = 0; idx < RhythmChart::MAX_NOTES; idx++) {
            this->notes[idx] = &chart->notes[idx];
        }
        this->note_count = chart->note_count;

        this->visible_notes_start_idx = 0;
        this->visible_notes_end_idx = 0;
    }

    void RhythmEngineScenePart::tick() {
        if (this->state == STARTING) {
            Drivers::music_driver.play(this->song_id);
            this->start_time = millis();
            this->state = PLAYING;
            return;
        }


        int time_pos_raw = millis() - this->start_time;
        int time_pos = time_pos_raw - this->get_total_offset();

        int visible_pos_start = time_pos - this->timing_window_ms;
        int visible_pos_end = time_pos + this->visible_before_hit_ms;

        while (true) {
            int next_visible_note_end_idx = this->visible_notes_end_idx + 1;
            if (next_visible_note_end_idx >= this->note_count) break;

            if (this->notes[next_visible_note_end_idx]->start_ms < visible_pos_end) {
                this->visible_notes_end_idx++;
                continue;
            } else {
                break;
            }
        }

        while (true) {
            int next_visible_note_start_idx = this->visible_notes_start_idx + 1;
            if (next_visible_note_start_idx >= this->note_count) break;

            if (this->notes[next_visible_note_start_idx]->start_ms < visible_pos_start) {
                this->visible_notes_start_idx++;
                continue;
            } else {
                break;
            }
        }


        Drivers::lights_driver.clear_led_array();

        for (int idx = this->visible_notes_start_idx; idx <= this->visible_notes_end_idx; idx++) {
            RhythmNote* current_note = this->notes[idx];
            if (current_note->start_ms < visible_pos_start || current_note->start_ms > visible_pos_end) {
                continue;
            }

            float progress = 1 - ((float)(current_note->start_ms - time_pos) / (float)this->visible_before_hit_ms);
            int light_idx = floor(progress * (float)(this->goal_led_idx));
            if (light_idx >= Drivers::lights_driver.lights_count) continue;

            Drivers::lights_driver.led_array[light_idx] = CRGB::Green;
        }

        Drivers::lights_driver.led_array[this->goal_led_idx] = CRGB::White;
    }


    int RhythmEngineScenePart::get_total_offset() {
        return this->offset + ComponentParams::RHYTHM_OFFSET;
    }
}  // namespace Engine
