#include <pins.hpp>

#include "scene.hpp"


namespace Scene {
    Loader::Loader(Source& source) :
        source(source),
        btn_action(PIN_BTN_ACTION, 500),
        btn_select(PIN_BTN_SELECT, 500) {}

    void Loader::on_tick() {
        btn_action.on_tick();
        if (btn_action.is_clicked) source.on_btn_action_click();
        if (btn_action.is_held_repeated) source.on_btn_action_held_repeat();

        btn_select.on_tick();
        if (btn_select.is_clicked) source.on_btn_select_click();
        if (btn_select.is_held_repeated) source.on_btn_select_held_repeat();

        const Source& next_source = source.render();
        if (next_source.non_null) {
            this->source = next_source;
        }
    }
}