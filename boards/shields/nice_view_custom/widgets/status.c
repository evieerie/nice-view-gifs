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

LV_IMG_DECLARE(sister_0);
LV_IMG_DECLARE(sister_1);
LV_IMG_DECLARE(sister_2);
LV_IMG_DECLARE(sister_3);
LV_IMG_DECLARE(sister_4);
LV_IMG_DECLARE(sister_5);
LV_IMG_DECLARE(sister_6);
LV_IMG_DECLARE(sister_7);
LV_IMG_DECLARE(sister_8);
LV_IMG_DECLARE(sister_9);
LV_IMG_DECLARE(sister_10);
LV_IMG_DECLARE(sister_11);
LV_IMG_DECLARE(sister_12);
LV_IMG_DECLARE(sister_13);
LV_IMG_DECLARE(sister_14);
LV_IMG_DECLARE(sister_15);
LV_IMG_DECLARE(sister_16);
LV_IMG_DECLARE(sister_17);
LV_IMG_DECLARE(sister_18);
LV_IMG_DECLARE(sister_19);
LV_IMG_DECLARE(sister_20);
LV_IMG_DECLARE(sister_21);
LV_IMG_DECLARE(sister_22);
LV_IMG_DECLARE(sister_23);
LV_IMG_DECLARE(sister_24);
LV_IMG_DECLARE(sister_25);
LV_IMG_DECLARE(sister_26);
LV_IMG_DECLARE(sister_27);
LV_IMG_DECLARE(sister_28);
LV_IMG_DECLARE(sister_29);
LV_IMG_DECLARE(sister_30);
LV_IMG_DECLARE(sister_31);
LV_IMG_DECLARE(sister_32);
LV_IMG_DECLARE(sister_33);
LV_IMG_DECLARE(sister_34);
LV_IMG_DECLARE(sister_35);
LV_IMG_DECLARE(sister_36);
LV_IMG_DECLARE(sister_37);
LV_IMG_DECLARE(sister_38);
LV_IMG_DECLARE(sister_39);
LV_IMG_DECLARE(sister_40);
LV_IMG_DECLARE(sister_41);
LV_IMG_DECLARE(sister_42);
LV_IMG_DECLARE(sister_43);
LV_IMG_DECLARE(sister_44);
LV_IMG_DECLARE(sister_45);
LV_IMG_DECLARE(sister_46);
LV_IMG_DECLARE(sister_47);
LV_IMG_DECLARE(sister_48);
LV_IMG_DECLARE(sister_49);
LV_IMG_DECLARE(sister_50);
LV_IMG_DECLARE(sister_51);
LV_IMG_DECLARE(sister_52);
LV_IMG_DECLARE(sister_53);
LV_IMG_DECLARE(sister_54);
LV_IMG_DECLARE(sister_55);
LV_IMG_DECLARE(sister_56);
LV_IMG_DECLARE(sister_57);
LV_IMG_DECLARE(sister_58);
LV_IMG_DECLARE(sister_59);
LV_IMG_DECLARE(sister_60);
LV_IMG_DECLARE(sister_61);
LV_IMG_DECLARE(sister_62);
LV_IMG_DECLARE(sister_63);
LV_IMG_DECLARE(sister_64);
LV_IMG_DECLARE(sister_65);
LV_IMG_DECLARE(sister_66);
LV_IMG_DECLARE(sister_67);
LV_IMG_DECLARE(sister_68);
LV_IMG_DECLARE(sister_69);
LV_IMG_DECLARE(sister_70);
LV_IMG_DECLARE(sister_71);
LV_IMG_DECLARE(sister_72);
LV_IMG_DECLARE(sister_73);
LV_IMG_DECLARE(sister_74);
LV_IMG_DECLARE(sister_75);
LV_IMG_DECLARE(sister_76);
LV_IMG_DECLARE(sister_77);
LV_IMG_DECLARE(sister_78);
LV_IMG_DECLARE(sister_79);
LV_IMG_DECLARE(sister_80);
LV_IMG_DECLARE(sister_81);
LV_IMG_DECLARE(sister_82);
LV_IMG_DECLARE(sister_83);
LV_IMG_DECLARE(sister_84);
LV_IMG_DECLARE(sister_85);
LV_IMG_DECLARE(sister_86);
LV_IMG_DECLARE(sister_87);
LV_IMG_DECLARE(sister_88);
LV_IMG_DECLARE(sister_89);
LV_IMG_DECLARE(sister_90);
LV_IMG_DECLARE(sister_91);
LV_IMG_DECLARE(sister_92);
LV_IMG_DECLARE(sister_93);
LV_IMG_DECLARE(sister_94);
LV_IMG_DECLARE(sister_95);
LV_IMG_DECLARE(sister_96);
LV_IMG_DECLARE(sister_97);
LV_IMG_DECLARE(sister_98);
LV_IMG_DECLARE(sister_99);
LV_IMG_DECLARE(sister_100);

const lv_img_dsc_t *anim_imgs[] = {
    &sister_0,
    &sister_1,
    &sister_2,
    &sister_3,
    &sister_4,
    &sister_5,
    &sister_6,
    &sister_7,
    &sister_8,
    &sister_9,
    &sister_10,
    &sister_11,
    &sister_12,
    &sister_13,
    &sister_14,
    &sister_15,
    &sister_16,
    &sister_17,
    &sister_18,
    &sister_19,
    &sister_20,
    &sister_21,
    &sister_22,
    &sister_23,
    &sister_24,
    &sister_25,
    &sister_26,
    &sister_27,
    &sister_28,
    &sister_29,
    &sister_30,
    &sister_31,
    &sister_32,
    &sister_33,
    &sister_34,
    &sister_35,
    &sister_36,
    &sister_37,
    &sister_38,
    &sister_39,
    &sister_40,
    &sister_41,
    &sister_42,
    &sister_43,
    &sister_44,
    &sister_45,
    &sister_46,
    &sister_47,
    &sister_48,
    &sister_49,
    &sister_50,
    &sister_51,
    &sister_52,
    &sister_53,
    &sister_54,
    &sister_55,
    &sister_56,
    &sister_57,
    &sister_58,
    &sister_59,
    &sister_60,
    &sister_61,
    &sister_62,
    &sister_63,
    &sister_64,
    &sister_65,
    &sister_66,
    &sister_67,
    &sister_68,
    &sister_69,
    &sister_70,
    &sister_71,
    &sister_72,
    &sister_73,
    &sister_74,
    &sister_75,
    &sister_76,
    &sister_77,
    &sister_78,
    &sister_79,
    &sister_80,
    &sister_81,
    &sister_82,
    &sister_83,
    &sister_84,
    &sister_85,
    &sister_86,
    &sister_87,
    &sister_88,
    &sister_89,
    &sister_90,
    &sister_91,
    &sister_92,
    &sister_93,
    &sister_94,
    &sister_95,
    &sister_96,
    &sister_97,
    &sister_98,
    &sister_99,
    &sister_100,
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
    lv_animimg_set_src(art, (const void **) anim_imgs, 101);     //<--
    lv_animimg_set_duration(art, 5000);                         //<--
    lv_animimg_set_repeat_count(art, LV_ANIM_REPEAT_INFINITE);  //<--
    lv_animimg_start(art);                                      //<--
    lv_obj_align(art, LV_ALIGN_TOP_LEFT, 0, 0);

    sys_slist_append(&widgets, &widget->node);
    widget_battery_status_init();
    widget_output_status_init();

    return 0;
}

lv_obj_t *zmk_widget_status_obj(struct zmk_widget_status *widget) { return widget->obj; }
