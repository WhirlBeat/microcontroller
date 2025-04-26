#include "music.hpp"

#include "../display/display.hpp"



namespace Drivers {
    MusicDriver::MusicDriver(int volume) : volume(volume) {}

    void MusicDriver::begin() {
        display_driver.clear_all();
        display_driver.print_center(0, "Init DFPlayer...");
        display_driver.render();
        Serial.println("Initializing DFPlayer...");

        this->df_serial.begin(9600, SERIAL_8N1, 16, 17);
        while (!this->df_player.begin(this->df_serial)) {
            Serial.println("Reconnecting...");
            delay(1000);
        }

        this->df_player.stop();
        this->df_player.volume(this->volume);

        display_driver.clear_all();
        display_driver.render();
        Serial.println("Initialized DFPlayer!");
    }

    void MusicDriver::tick() {
        if (this->current_song_id < 0) return;

        if (this->current_song_id != this->previous_song_id) {
            Serial.println(String("Now playing ") + this->current_song_id);
            if (this->current_song_id < 0) {
                this->df_player.stop();
            } else {
                this->df_player.play(this->current_song_id);
            }
            this->previous_song_id = this->current_song_id;
        }


        this->loop_debounce_timer--;
        if (this->loop_debounce_timer < 0) this->loop_debounce_timer = 0;

        if (
            this->should_loop &&
            this->df_player.available() &&
            this->df_player.readType() == DFPlayerPlayFinished &&
            this->loop_debounce_timer == 0
        ) {
            Serial.println(String("Looping ") + this->current_song_id);
            this->df_player.play(this->current_song_id);
            this->loop_debounce_timer = 200;
        }
    }

    void MusicDriver::play(int song_id, bool should_loop) {
        this->current_song_id = song_id;
        this->should_loop = should_loop;
    }

    void MusicDriver::stop() {
        this->current_song_id = -1;
    }

    MusicDriver music_driver{};
}