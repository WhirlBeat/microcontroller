#include "rhythm_chart.hpp"



namespace Engine {
    RhythmChart::RhythmChart(
        const char* name,
        int song_id,
        int offset,
        RhythmNote *notes,
        int note_count
    ) :
        name(name),
        song_id(song_id),
        offset(offset),
        note_count(note_count)
    {
        for (int idx = 0; idx < note_count; idx++) {
            this->notes[idx] = notes[idx];
        }
    }
}
