/*
 *
 * Copyright (c) 2023 The ZMK Contributors
 * SPDX-License-Identifier: MIT
 *
 */

#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/battery.h>
#include <zmk/display.h>
#include "status.h"
#include <zmk/events/usb_conn_state_changed.h>
#include <zmk/event_manager.h>
#include <zmk/events/battery_state_changed.h>
#include <zmk/events/ble_active_profile_changed.h>
#include <zmk/events/endpoint_changed.h>
#include <zmk/events/wpm_state_changed.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/usb.h>
#include <zmk/ble.h>
#include <zmk/endpoints.h>
#include <zmk/keymap.h>
#include <zmk/wpm.h>

LV_IMG_DECLARE(mai_0);
LV_IMG_DECLARE(mai_1);
LV_IMG_DECLARE(mai_2);
LV_IMG_DECLARE(mai_3);
LV_IMG_DECLARE(mai_4);
LV_IMG_DECLARE(mai_5);
LV_IMG_DECLARE(mai_6);
LV_IMG_DECLARE(mai_7);
LV_IMG_DECLARE(mai_8);
LV_IMG_DECLARE(mai_9);
LV_IMG_DECLARE(mai_10);
LV_IMG_DECLARE(mai_11);
LV_IMG_DECLARE(mai_12);
LV_IMG_DECLARE(mai_13);
LV_IMG_DECLARE(mai_14);
LV_IMG_DECLARE(mai_15);
LV_IMG_DECLARE(mai_16);
LV_IMG_DECLARE(mai_17);
LV_IMG_DECLARE(mai_18);
LV_IMG_DECLARE(mai_19);
LV_IMG_DECLARE(mai_20);
LV_IMG_DECLARE(mai_21);
LV_IMG_DECLARE(mai_22);
LV_IMG_DECLARE(mai_23);
LV_IMG_DECLARE(mai_24);
LV_IMG_DECLARE(mai_25);
LV_IMG_DECLARE(mai_26);
LV_IMG_DECLARE(mai_27);
LV_IMG_DECLARE(mai_28);
LV_IMG_DECLARE(mai_29);
LV_IMG_DECLARE(mai_30);
LV_IMG_DECLARE(mai_31);
LV_IMG_DECLARE(mai_32);
LV_IMG_DECLARE(mai_33);
LV_IMG_DECLARE(mai_34);
LV_IMG_DECLARE(mai_35);
LV_IMG_DECLARE(mai_36);
LV_IMG_DECLARE(mai_37);
LV_IMG_DECLARE(mai_38);
LV_IMG_DECLARE(mai_39);
LV_IMG_DECLARE(mai_40);
LV_IMG_DECLARE(mai_41);
LV_IMG_DECLARE(mai_42);
LV_IMG_DECLARE(mai_43);
LV_IMG_DECLARE(mai_44);
LV_IMG_DECLARE(mai_45);
LV_IMG_DECLARE(mai_46);
LV_IMG_DECLARE(mai_47);
LV_IMG_DECLARE(mai_48);
LV_IMG_DECLARE(mai_49);
LV_IMG_DECLARE(mai_50);
LV_IMG_DECLARE(mai_51);
LV_IMG_DECLARE(mai_52);
LV_IMG_DECLARE(mai_53);

const lv_img_dsc_t *anim_imgs[] = {
    &mai_0,
    &mai_1,
    &mai_2,
    &mai_3,
    &mai_4,
    &mai_5,
    &mai_6,
    &mai_7,
    &mai_8,
    &mai_9,
    &mai_10,
    &mai_11,
    &mai_12,
    &mai_13,
    &mai_14,
    &mai_15,
    &mai_16,
    &mai_17,
    &mai_18,
    &mai_19,
    &mai_20,
    &mai_21,
    &mai_22,
    &mai_23,
    &mai_24,
    &mai_25,
    &mai_26,
    &mai_27,
    &mai_28,
    &mai_29,
    &mai_30,
    &mai_31,
    &mai_32,
    &mai_33,
    &mai_34,
    &mai_35,
    &mai_36,
    &mai_37,
    &mai_38,
    &mai_39,
    &mai_40,
    &mai_41,
    &mai_42,
    &mai_43,
    &mai_44,
    &mai_45,
    &mai_46,
    &mai_47,
    &mai_48,
    &mai_49,
    &mai_50,
    &mai_51,
    &mai_52,
    &mai_53,
};


static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

struct output_status_state {
    struct zmk_endpoint_instance selected_endpoint;
    int active_profile_index;
    bool active_profile_connected;
    bool active_profile_bonded;
};

struct layer_status_state {
    uint8_t index;
    const char *label;
};

struct wpm_status_state {
    uint8_t wpm;
};

static void draw_top(lv_obj_t *widget, lv_color_t cbuf[], const struct status_state *state) {
    lv_obj_t *canvas = lv_obj_get_child(widget, 0);

    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &lv_font_montserrat_16, LV_TEXT_ALIGN_RIGHT);
    lv_draw_label_dsc_t label_dsc_wpm;
    init_label_dsc(&label_dsc_wpm, LVGL_FOREGROUND, &lv_font_unscii_8, LV_TEXT_ALIGN_RIGHT);
    lv_draw_rect_dsc_t rect_black_dsc;
    init_rect_dsc(&rect_black_dsc, LVGL_BACKGROUND);
    lv_draw_rect_dsc_t rect_white_dsc;
    init_rect_dsc(&rect_white_dsc, LVGL_FOREGROUND);
    lv_draw_line_dsc_t line_dsc;
    init_line_dsc(&line_dsc, LVGL_FOREGROUND, 1);

    // Fill background
    lv_canvas_draw_rect(canvas, 0, 0, CANVAS_SIZE, CANVAS_SIZE, &rect_black_dsc);

    // Draw battery
    draw_battery(canvas, state);

    // Draw output status
    char output_text[10] = {};

    switch (state->selected_endpoint.transport) {
    case ZMK_TRANSPORT_USB:
        strcat(output_text, LV_SYMBOL_USB);
        break;
    case ZMK_TRANSPORT_BLE:
        if (state->active_profile_bonded) {
            if (state->active_profile_connected) {
                strcat(output_text, LV_SYMBOL_WIFI);
            } else {
                strcat(output_text, LV_SYMBOL_CLOSE);
            }
        } else {
            strcat(output_text, LV_SYMBOL_SETTINGS);
        }
        break;
    }

    lv_canvas_draw_text(canvas, 0, 0, CANVAS_SIZE, &label_dsc, output_text);

    // Rotate canvas
    rotate_canvas(canvas, cbuf);
}

static void set_battery_status(struct zmk_widget_status *widget,
                               struct battery_status_state state) {
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
    widget->state.charging = state.usb_present;
#endif /* IS_ENABLED(CONFIG_USB_DEVICE_STACK) */

    widget->state.battery = state.level;

    draw_top(widget->obj, widget->cbuf, &widget->state);
}

static void battery_status_update_cb(struct battery_status_state state) {
    struct zmk_widget_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) { set_battery_status(widget, state); }
}

static struct battery_status_state battery_status_get_state(const zmk_event_t *eh) {
    const struct zmk_battery_state_changed *ev = as_zmk_battery_state_changed(eh);

    return (struct battery_status_state) {
        .level = (ev != NULL) ? ev->state_of_charge : zmk_battery_state_of_charge(),
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
        .usb_present = zmk_usb_is_powered(),
#endif /* IS_ENABLED(CONFIG_USB_DEVICE_STACK) */
    };
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_battery_status, struct battery_status_state,
                            battery_status_update_cb, battery_status_get_state)

ZMK_SUBSCRIPTION(widget_battery_status, zmk_battery_state_changed);
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
ZMK_SUBSCRIPTION(widget_battery_status, zmk_usb_conn_state_changed);
#endif /* IS_ENABLED(CONFIG_USB_DEVICE_STACK) */

static void set_output_status(struct zmk_widget_status *widget,
                              const struct output_status_state *state) {
    widget->state.selected_endpoint = state->selected_endpoint;
    widget->state.active_profile_index = state->active_profile_index;
    widget->state.active_profile_connected = state->active_profile_connected;
    widget->state.active_profile_bonded = state->active_profile_bonded;

    draw_top(widget->obj, widget->cbuf, &widget->state);
}

static void output_status_update_cb(struct output_status_state state) {
    struct zmk_widget_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) { set_output_status(widget, &state); }
}

static struct output_status_state output_status_get_state(const zmk_event_t *_eh) {
    return (struct output_status_state){
        .selected_endpoint = zmk_endpoints_selected(),
        .active_profile_index = zmk_ble_active_profile_index(),
        .active_profile_connected = zmk_ble_active_profile_is_connected(),
        .active_profile_bonded = !zmk_ble_active_profile_is_open(),
    };
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_output_status, struct output_status_state,
                            output_status_update_cb, output_status_get_state)
ZMK_SUBSCRIPTION(widget_output_status, zmk_endpoint_changed);

#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
ZMK_SUBSCRIPTION(widget_output_status, zmk_usb_conn_state_changed);
#endif
#if defined(CONFIG_ZMK_BLE)
ZMK_SUBSCRIPTION(widget_output_status, zmk_ble_active_profile_changed);
#endif

int zmk_widget_status_init(struct zmk_widget_status *widget, lv_obj_t *parent) {
    widget->obj = lv_obj_create(parent);
    lv_obj_set_size(widget->obj, 160, 68);
    lv_obj_t *top = lv_canvas_create(widget->obj);
    lv_obj_align(top, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_canvas_set_buffer(top, widget->cbuf, CANVAS_SIZE, CANVAS_SIZE, LV_IMG_CF_TRUE_COLOR);

    lv_obj_t * art = lv_animimg_create(widget->obj);            //<--
    lv_obj_center(art);                                         //<--
    lv_animimg_set_src(art, (const void **) anim_imgs, 53);     //<--
    lv_animimg_set_duration(art, 10000);                         //<--
    lv_animimg_set_repeat_count(art, LV_ANIM_REPEAT_INFINITE);  //<--
    lv_animimg_start(art);                                      //<--
    lv_obj_align(art, LV_ALIGN_TOP_LEFT, 0, 0);

    sys_slist_append(&widgets, &widget->node);
    widget_battery_status_init();
    widget_output_status_init();

    return 0;
}

lv_obj_t *zmk_widget_status_obj(struct zmk_widget_status *widget) { return widget->obj; }
