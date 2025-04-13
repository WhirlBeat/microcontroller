#pragma once



namespace Tools {
    class TPS {
    public:
        unsigned long previous_millis = 0;
        void tick();
    };
}