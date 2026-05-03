#include <zephyr/device.h>
#include <zmk/input_processor.h>
#include <zmk/split/bluetooth/central.h>

#define ROTATE 0.087f  // ~5 degrees

static int trackball_rotate_process(struct zmk_input_processor *proc,
                                    struct zmk_input_event *evt) {
    if (evt->type != ZMK_INPUT_EV_REL) {
        return 0;
    }

    float x = evt->rel.x;
    float y = evt->rel.y;

    bool is_central = IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL);

    float dir = is_central ? -1.0f : 1.0f;

    float new_x = x - (y * ROTATE * dir);
    float new_y = y + (x * ROTATE * dir);

    evt->rel.x = new_x;
    evt->rel.y = new_y;

    return 0;
}

static struct zmk_input_processor_api trackball_rotate_api = {
    .process = trackball_rotate_process,
};

ZMK_INPUT_PROCESSOR_DEFINE(trackball_rotate, &trackball_rotate_api);
