#pragma once
// // Set the mouse settings to a comfortable speed/accuracy trade-off,
// // assuming a screen refresh rate of 60 Htz or higher
// // The default is 50. This makes the mouse ~3 times faster and more accurate
// #define MOUSEKEY_INTERVAL 16
// // The default is 20. Since we made the mouse about 3 times faster with the previous setting,
// // give it more time to accelerate to max speed to retain precise control over short distances.
// #define MOUSEKEY_TIME_TO_MAX 40
// // The default is 300. Let's try and make this as low as possible while keeping the cursor responsive
// #define MOUSEKEY_DELAY 100
// // It makes sense to use the same delay for the mouseweel
// #define MOUSEKEY_WHEEL_DELAY 100
// // The default is 100
// #define MOUSEKEY_WHEEL_INTERVAL 50
// // The default is 40
// #define MOUSEKEY_WHEEL_TIME_TO_MAX 100

#define MK_KINETIC_SPEED
#define MOUSEKEY_DELAY 5
#define MOUSEKEY_INTERVAL 10
#define MOUSEKEY_MOVE_DELTA 32
#define MOUSEKEY_INITIAL_SPEED 100
#define MOUSEKEY_BASE_SPEED 5000
#define MOUSEKEY_DECELERATED_SPEED 400
#define MOUSEKEY_ACCELERATED_SPEED 3000
#define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 16
#define MOUSEKEY_WHEEL_BASE_MOVEMENTS 32
#define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 48
#define MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS 8

#undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#undef RGB_MATRIX_DEFAULT_MODE
#undef RGB_MATRIX_DEFAULT_HUE
#undef RGB_MATRIX_DEFAULT_SAT
#undef RGB_MATRIX_DEFAULT_VAL
#undef RGB_MATRIX_DEFAULT_SPD
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_HUE_BREATHING
#define RGB_MATRIX_DEFAULT_HUE 0
#define RGB_MATRIX_DEFAULT_SAT 250
#define RGB_MATRIX_DEFAULT_VAL 160
#define RGB_MATRIX_DEFAULT_SPD 64

#define ENABLE_COMPILE_KEYCODE
#define CHARYBDIS_MINIMUM_DEFAULT_DPI 200
#define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 100
#define CHARYBDIS_MINIMUM_SNIPING_DPI 100
#define CHARYBDIS_SNIPING_DPI_CONFIG_STEP 50
#define CHARYBDIS_DRAGSCROLL_REVERSE_Y
#define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#undef CHARYBDIS_AUTO_SNIPING_ON_LAYER

// Pick good defaults for enabling homerow modifiers
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define QUICK_TAP_TERM 0
