#include <zephyr/device.h>
#include <zmk/input_processor.h>
#include <zmk/split/bluetooth/central.h>

#define SIN_ANGLE 0.087f  // ~sin(5°)

static int trackball_rotate_process(struct zmk_input_processor *proc,
                                    struct zmk_input_event *evt) {
    if (evt->type != ZMK_INPUT_EV_REL) {
        return 0;
    }

    float x = evt->rel.x;
    float y = evt->rel.y;

    // Detect which half we are on
    bool is_right = IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL);

    if (is_left) {
        // LEFT: +5°
        evt->rel.x = x - (y * SIN_ANGLE);
        evt->rel.y = y + (x * SIN_ANGLE);
    } else {
        // RIGHT: -5°
        evt->rel.x = x + (y * SIN_ANGLE);
        evt->rel.y = y - (x * SIN_ANGLE);
    }

    return 0;
}

static struct zmk_input_processor_api trackball_rotate_api = {
    .process = trackball_rotate_process,
};

ZMK_INPUT_PROCESSOR_DEFINE(trackball_rotate, &trackball_rotate_api);
