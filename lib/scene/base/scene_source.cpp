#include "scene.hpp"


namespace Scene {
    Source::Source() {}
    Source::Source(bool non_null) : non_null(non_null) {}

    const Source& Source::render() {
        return *this;
    }

    void Source::on_btn_action_click() {}
    void Source::on_btn_action_held_repeat() {}
    void Source::on_btn_select_click() {}
    void Source::on_btn_select_held_repeat() {}

    BlankSource::BlankSource() : Source(true) {}

    const Source& BlankSource::render() {
        return *this;
    }

    const Source blank_source = BlankSource();
}