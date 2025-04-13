#include <colors.hpp>

#include "select_menu.hpp"



// Slice the strip into a certain amount of slices. This function calculates the left border of a slice.
int get_left_border(int led_count, int slices, int slice_idx) {
    int minimum_leds_per_slice = floor(led_count / slices);
    int extra_leds = led_count % slices;
    return slice_idx < extra_leds
        ? slice_idx * (minimum_leds_per_slice + 1)
        : slice_idx * minimum_leds_per_slice + extra_leds;
}


namespace Engine {
    SelectMenuScenePart::SelectMenuScenePart(const char *const choices[], const size_t choices_count, int row) :
        ScenePart(),
        row(row),
        choices(choices), choices_count(choices_count),
        arrows(row)
    {}

    void SelectMenuScenePart::tick() {
        this->arrows.tick();

        if (Drivers::button_driver_left.is_clicked()) {
            select_idx--;
            if (select_idx < 0) select_idx = choices_count - 1;
        }

        if (Drivers::button_driver_right.is_clicked()) {
            select_idx++;
            if (select_idx >= (int)choices_count) select_idx = 0;
        }

        if (select_idx != previous_select_idx) {
            arrows.clear_without_arrows();
            Drivers::display_driver.print_center(0, choices[select_idx]);
            previous_select_idx = select_idx;
        }

        this->render_lights();
    }


    const char * SelectMenuScenePart::get_selected_str()
    {
        return choices[select_idx];
    }
    int SelectMenuScenePart::get_selected_idx() {
        return select_idx;
    }


    void SelectMenuScenePart::render_lights() {
        Drivers::lights_driver.clear_led_array();
        int lower_bound = get_left_border(Drivers::lights_driver.lights_count, choices_count, select_idx);
        int upper_bound_exc = get_left_border(Drivers::lights_driver.lights_count, choices_count, select_idx + 1);


        if (!(
            Drivers::button_driver_right.is_held() ||
            Drivers::button_driver_left.is_held() ||
            Drivers::button_driver_action.is_held()
        )) {
            for (int i = lower_bound; i < upper_bound_exc; i++) {
                Drivers::lights_driver.led_array[i] = ColorFromPalette(
                    Gradients::rainbow_palette,
                    floor(((float)this->select_idx / (float)this->choices_count) * 255)
                );
            }
        }

        Drivers::lights_driver.show();
    }
}