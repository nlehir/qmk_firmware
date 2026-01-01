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
    // Layer 0
    [0] = LAYOUT(
            MS_BTN1, // top left
            TG(1), // top mid left
            DRAG_SCROLL, // top mid right
            MS_BTN2, // top right
            DRAG_SCROLL, // bottom left
            DPI_CONFIG // bottom right
            ),

    // Layer 1
    [1] = LAYOUT(
            MS_BTN1, // top left
            KC_TRNS, // top mid left
            DRAG_SCROLL, // top mid right
            MACRO_2, // top right
            DRAG_SCROLL, // bottom left
            MACRO_1 // bottom right
            ),
};
