#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include QMK_KEYBOARD_CONFIG_H

#define TAPPING_TERM 155
#define IGNORE_MOD_TAP_INTERRUPT
/*#define HOLD_ON_OTHER_KEY_PRESS*/
// #define RETRO_TAPPING
// TODO: it may make sense to enable TAPPING_FORCE_HOLD for some keys,
// but I rely heavily on being able to repeat some keys, such as j, and k
// so it would onlo work for some keys, see https://docs.qmk.fm/#/tap_hold?id=tapping-force-hold
// #define TAPPING_FORCE_HOLD
// #define PERMISSIVE_HOLD

#endif
