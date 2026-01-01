/* Copyright 2023 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum custom_keycodes {
    MACRO_1 = SAFE_RANGE,
    MACRO_2,
    MACRO_12,
};

enum {
    TD_LAYER,
    TD_ABLETON,
};


// why needed ?
void td_layer_reset(tap_dance_state_t *state, void *user_data) {
    // nothing needed here
}

// why needed ?
void td_ableton_reset(tap_dance_state_t *state, void *user_data) {
    // nothing needed here
}

void td_layer_finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            layer_invert(1);  // single tap toggles layer 1
            break;
        case 2:
            layer_invert(2);  // double tap toggles layer 2
            break;
        case 3:
            layer_invert(3);  // triple tap toggles layer 3
            break;
        default:
            // More than 3 taps: do nothing (or add more layers if you want)
            break;
    }
}

void td_ableton_finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code16(A(G(KC_L)));
            break;
        case 2:
            tap_code16(A(G(KC_B)));
            break;
        default:
            break;
    }
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_layer_finished, td_layer_reset),
    [TD_ABLETON] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_ableton_finished, td_ableton_reset),
};

const uint16_t PROGMEM cmd_tab_combo[] = {MACRO_1, MACRO_2, COMBO_END};

combo_t key_combos[1] = {
    [0] = COMBO(cmd_tab_combo, MACRO_12)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case MACRO_1:
            // Single Button: Option + Command + L
            tap_code16(A(G(KC_L)));
            return false;

        case MACRO_2:
            // Single Button: right click
            tap_code(MS_BTN2);
            return false;

        case MACRO_12:
            // Combo (MACRO_1 + MACRO_2): Command + Tab
            tap_code16(G(KC_TAB));
            return false;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
            MS_BTN1, // top left
            TD(TD_LAYER), // top mid left
            DRAG_SCROLL, // top mid right
            MS_BTN2, // top right
            DRAG_SCROLL, // bottom left
            DPI_CONFIG // bottom right
            ),

    [1] = LAYOUT(
            MS_BTN1, // top left
            TO(0), // top mid left
            TD(TD_ABLETON), // top mid right
            MACRO_2, // top right
            MS_BTN1, // bottom left
            MACRO_1 // bottom right
            ),

    [2] = LAYOUT(
            DRAG_SCROLL, // top left
            TO(0), // top mid left
            KC_B, // top mid right
            MACRO_2, // top right
            DRAG_SCROLL, // bottom left
            MACRO_1 // bottom right
            ),

    [3] = LAYOUT(
            DRAG_SCROLL, // top left
            TO(0), // top mid left
            KC_C, // top mid right
            MACRO_2, // top right
            DRAG_SCROLL, // bottom left
            MACRO_1 // bottom right
            ),
};
