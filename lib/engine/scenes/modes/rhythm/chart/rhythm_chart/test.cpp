#include <drivers.hpp>

#include "rhythm_chart.hpp"



namespace Engine {
    RhythmNote chart_test_notes[] = {
        RhythmNote(0),
        RhythmNote(429),
        RhythmNote(857),
        // RhythmNote(1286),
        RhythmNote(1714),
        RhythmNote(2143),
        RhythmNote(2571),
        RhythmNote(3000),
        RhythmNote(3429),
        RhythmNote(3857),
        RhythmNote(4286),
        // RhythmNote(4714),
        RhythmNote(5143),
        RhythmNote(5571),
        RhythmNote(6000),
        RhythmNote(6429),
        RhythmNote(6857),
        RhythmNote(7286),
        RhythmNote(7714),
        // RhythmNote(8143),
        RhythmNote(8571),
        RhythmNote(9000),
        RhythmNote(9429),
        RhythmNote(9857),
        RhythmNote(10286),
        RhythmNote(10714),
        RhythmNote(11143),
        //RhythmNote(11571),
        RhythmNote(12000),
        RhythmNote(12429),
        RhythmNote(12857),
        RhythmNote(13286)
    };

    RhythmChart chart_test{
        "Test",
        SongIDs::SETUP,
        73,
        chart_test_notes, 28
    };
}