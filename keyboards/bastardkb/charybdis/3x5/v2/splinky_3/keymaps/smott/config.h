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

#define ENABLE_COMPILE_KEYCODE

// Pick good defaults for enabling homerow modifiers
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define QUICK_TAP_TERM 0
