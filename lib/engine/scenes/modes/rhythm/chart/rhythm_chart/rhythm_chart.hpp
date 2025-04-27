#pragma once

#include "../rhythm_note/rhythm_note.hpp"



namespace Engine {
    class RhythmChart {
    public:
        const char* name;
        const int song_id;
        const int offset;

        static const int MAX_NOTES = 1000;
        RhythmNote notes[MAX_NOTES];
        const int note_count;

        RhythmChart(const char* name, int song_id, int offset, RhythmNote *notes, int note_count);
    };


    extern RhythmChart chart_test;
}