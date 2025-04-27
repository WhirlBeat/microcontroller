#pragma once

#include <global.hpp>



namespace Drivers {
    class ButtonDriver {
    public:
        int pitch;

        ButtonDriver(int pin, int pitch);

        bool read_value();

        void tick();

        bool check_hold() const;
        bool check_click() const;
        bool check_repeat_clicks(int repeat_rate = 100, int before_delay = 500) const;

        bool is_hold() const;
        bool is_click() const;
        bool is_repeat_click(int repeat_rate = 100, int before_delay = 500) const;

        void play_tone() const;

    private:
        int pin;

        bool held_state = false;
        bool clicked_state = false;
        int ticks_since_press = 0;

        void on_held();
        void on_release();


        static void set_pin_mode(int pin);
    };


    extern ButtonDriver button_driver_left;
    extern ButtonDriver button_driver_action;
    extern ButtonDriver button_driver_right;
}