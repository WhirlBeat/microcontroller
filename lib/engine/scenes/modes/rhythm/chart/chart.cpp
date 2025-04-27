#include "chart.hpp"



namespace Engine {
    RhythmChart* charts[CHART_COUNT] = {
        &chart_ifg,
        &chart_test
    };
}