#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 10

// default but used in macros
#undef TAPPING_TERM
#define TAPPING_TERM 150
#define PERMISSIVE_HOLD

// Make rolling trigger wrong input less
#define BILATERAL_COMBINATIONS

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define QUICK_TAP_TERM 0

#define RETRO_TAPPING

// Auto Shift
#define NO_AUTO_SHIFT_ALPHA
#define AUTO_SHIFT_TIMEOUT TAPPING_TERM
#define AUTO_SHIFT_NO_SETUP

#undef CHARYBDIS_AUTO_SNIPING_ON_LAYER

/* Charybdis-specific features. */

#ifdef POINTING_DEVICE_ENABLE
// Automatically enable the pointer layer when moving the trackball.  See also:
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS`
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD`
// #define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#endif // POINTING_DEVICE_ENABLE
