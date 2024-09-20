#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 10

// default but used in macros
#undef TAPPING_TERM
#define TAPPING_TERM 150

#undef QUICK_TAP_TERM
#define QUICK_TAP_TERM 0

#define PERMISSIVE_HOLD

#define DUMMY_MOD_NEUTRALIZER_KEYCODE KC_RIGHT_CTRL

// Auto Shift
#define NO_AUTO_SHIFT_ALPHA
#define AUTO_SHIFT_TIMEOUT
#define AUTO_SHIFT_NO_SETUP

/* Charybdis-specific features. */

#ifdef POINTING_DEVICE_ENABLE
// Automatically enable the pointer layer when moving the trackball.  See also:
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS`
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD`
// #define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#endif // POINTING_DEVICE_ENABLE
