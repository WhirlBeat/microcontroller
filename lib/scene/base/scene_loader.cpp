#include <pins.hpp>

#include "scene.hpp"


namespace Scene {
    Loader::Loader(Source& source) :
        source(source),
        btn_action(PIN_BTN_ACTION, 500),
        btn_up(PIN_BTN_UP, 500),
        btn_down(PIN_BTN_DOWN, 500) {}

    void Loader::on_tick() {
        btn_action.on_tick();
        if (btn_action.is_clicked) source.on_btn_action_click();
        if (btn_action.is_held_repeated) source.on_btn_action_held_repeat();

        btn_up.on_tick();
        if (btn_up.is_clicked) source.on_btn_up_click();
        if (btn_up.is_held_repeated) source.on_btn_up_held_repeat();

        btn_down.on_tick();
        if (btn_down.is_clicked) source.on_btn_down_click();
        if (btn_down.is_held_repeated) source.on_btn_down_held_repeat();

        const Source& next_source = source.render();
        if (next_source.non_null) {
            this->source = next_source;
        }
    }
}