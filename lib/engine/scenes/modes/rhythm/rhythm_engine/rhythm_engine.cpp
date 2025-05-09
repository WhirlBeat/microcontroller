#include <colors.hpp>

#include "rhythm_engine.hpp"




namespace Engine {
    RhythmEngineScenePart::RhythmEngineScenePart() : ScenePart() {}

    void RhythmEngineScenePart::init(RhythmChart *chart) {
        this->state = STARTING;
        this->init_start_time = 0;
        this->offset = chart->offset;

        this->song_id = chart->song_id;

        for (int idx = 0; idx < RhythmChart::MAX_NOTES; idx++) {
            this->notes[idx] = &chart->notes[idx];
        }
        this->note_count = chart->note_count;

        this->visible_notes_start_idx = 0;
        this->visible_notes_end_idx = 0;

        this->target_note_idx = 0;

        this->combo = 0;
        this->score = 0;
        this->unweighted_score = 0;
    }

    void RhythmEngineScenePart::tick() {
        if (this->state == FINISHED) return;
        if (this->state == STARTING) {
            this->init_start_time = millis();
            this->state = PLAYING;
            return;
        }


        int time_pos_raw = millis() - this->init_start_time - this->visible_before_hit_ms;
        if (time_pos_raw > 0) {
            Drivers::music_driver.play(this->song_id);
        }
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
            if (idx < this->target_note_idx) continue;
            if (idx >= this->note_count) continue;


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



        RhythmNote* target_note = this->notes[this->target_note_idx];

        while (true) {
            if (this->target_note_idx >= this->note_count) {
                this->state = FINISHED;
                return;
            };

            if (this->notes[this->target_note_idx]->start_ms < visible_pos_start) {
                this->target_note_idx++;
                this->on_miss();
            }
            else break;
        }


        int perfect_timing_window = floor((float)this->timing_window_ms * (1.0F/3.0F));
        int good_timing_window = floor((float)this->timing_window_ms * (2.0F/3.0F));
        int ok_timing_window = this->timing_window_ms;

        if (Drivers::button_driver_action.is_click()) {
            int difference = abs(target_note->start_ms - time_pos);

            if (difference < perfect_timing_window) this->on_perfect();
            else if (difference < good_timing_window) this->on_good();
            else if (difference < ok_timing_window) this->on_ok();
            else this->on_miss();

            this->target_note_idx++;
        }
    }


    int RhythmEngineScenePart::get_total_offset() {
        return this->offset + ComponentParams::RHYTHM_OFFSET;
    }

    void RhythmEngineScenePart::on_perfect() {
        this->add_score(this->perfect_base_score);
        this->combo++;
        this->previous_judgement = "PERFECT";
        Drivers::buzzer_driver.play_tone(this->perfect_pitch, this->pitch_duration_ms);
    }
    void RhythmEngineScenePart::on_good() {
        this->add_score(this->good_base_score);
        this->combo++;
        this->previous_judgement = "GOOD";
        Drivers::buzzer_driver.play_tone(this->good_pitch, this->pitch_duration_ms);
    }
    void RhythmEngineScenePart::on_ok() {
        this->add_score(this->ok_base_score);
        this->combo++;
        this->previous_judgement = "OK";
        Drivers::buzzer_driver.play_tone(this->ok_pitch, this->pitch_duration_ms);
    }
    void RhythmEngineScenePart::on_miss() {
        this->combo = 0;
        this->previous_judgement = "MISS";
        Drivers::buzzer_driver.play_tone(this->miss_pitch, this->pitch_duration_ms);
    }

    void RhythmEngineScenePart::add_score(int base_score) {
        this->score += floor((float)base_score * (1.0F + (((float)this->combo) / 25.0F)));
        this->unweighted_score += base_score;
    }
}
