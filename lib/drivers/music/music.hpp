#pragma once

#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#include <global.hpp>



enum SongIDs {
    MAIN_MENU = 1,
    SETUP = 2,
    SETUP_REMIX = 3,
    HIGHSCORE = 4,
    LEADERBOARD = 5,
    TIMING_PLAY = 6
};


namespace Drivers {
    class MusicDriver {
    public:
        HardwareSerial df_serial{2};
        DFRobotDFPlayerMini df_player{};

        const int volume;

        int current_song_id = -1;
        bool should_loop = false;
        int loop_debounce_timer = 0;

        MusicDriver(int volume = ComponentParams::DF_PLAYER_VOLUME);

        void begin();
        void tick();

        void set_debounce_timer(int debounce = 1000);

        void play(int song_id, bool should_loop = false);
        void stop();

    private:
        int previous_song_id = -100;
    };


    extern MusicDriver music_driver;
}