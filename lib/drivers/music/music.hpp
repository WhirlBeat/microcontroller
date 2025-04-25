#pragma once

#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#include <global.hpp>



namespace Drivers {
    class MusicDriver {
    public:
        HardwareSerial df_serial{2};
        DFRobotDFPlayerMini df_player{};

        const int volume;

        int current_song_id = -1;
        bool should_loop = false;

        MusicDriver(int volume = ComponentParams::DF_PLAYER_VOLUME);

        void begin();
        void tick();

        void play(int song_id, bool should_loop = false);
        void stop();
    
    private:
        int previous_song_id = -100;
    };


    extern MusicDriver music_driver;
}