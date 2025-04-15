#pragma once

#include <global.hpp>



namespace Drivers {
    class ButtonDriver {
    public:
        ButtonDriver(int pin);

        bool read_value();

        void tick();

        bool is_held() const;
        bool is_clicked() const;
        bool is_click_repeated(int repeat_rate = 100, int before_delay = 1000);

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