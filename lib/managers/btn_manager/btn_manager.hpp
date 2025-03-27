#pragma once

namespace BtnManager {
    class Button {
    public:
        int pin;
        int repeat_delay_ms;

        bool is_pressed = false;
        bool is_clicked = false;
        bool is_held_repeated = false;
        
        int ticks_since_press = 0;


        Button(int pin, int repeat_delay_ms = 100);
        
        void on_tick();

        void on_held();
        void on_release();
    };
}