#include <zephyr/device.h>
#include <zmk/input_processor.h>

#define ROTATE 0.087f

static int trackball_rotate_process(struct zmk_input_processor *proc,
                                    struct zmk_input_event *evt) {
    if (evt->type != ZMK_INPUT_EV_REL) {
        return 0;
    }

    float x = evt->rel.x;
    float y = evt->rel.y;

    evt->rel.x = x - (y * ROTATE);
    evt->rel.y = y + (x * ROTATE);

    return 0;
}

ZMK_INPUT_PROCESSOR(trackball_rotate, trackball_rotate_process);
