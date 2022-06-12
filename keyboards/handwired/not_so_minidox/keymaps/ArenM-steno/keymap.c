#include "keymap_steno.h"
#include QMK_KEYBOARD_H

typedef struct {
  uint8_t state;
} tap_state_t;

enum custom_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _R2,
    _VIM,
    _FUNCTION,
    _ADJUST,
    _STENO,
};

enum custom_keycodes {
  VIM_E = SAFE_RANGE,
  VIM_B,
  VIM_EXT,
  PLOVER,
  EXIT_PLV,
};

typedef enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD,
  DOUBLE_TAP,
  TRIPLE_TAP,
  OVER_TAP,
} tap_state_e;

enum tapdances {
  TD_V_VIM,
  TD_S_CAPS,
};

#define KC_RST  RESET

#define KC_CAD  LCTL(LALT(KC_DEL))
#define KC_RSP  LT(_RAISE, KC_SPC)
#define MY_G    LT(_FUNCTION, KC_G)
#define MY_LCTL LCTL_T(KC_ESC)

// Thumb Keys
// #define MY_LSP  LT(_LOWER, KC_SPC)
#define MY_LSP MO(_LOWER)
// TODO: This sends a semi colon for some reason
/* #define MY_TRR LT(_R2, KC_COLN) // Right thumb cluster right button */
#define MY_TRR KC_COLN // Right thumb cluster right button

// Vim Emulation Mode
// #define MY_V    TD(TD_V_VIM)
#define MY_SCLN LT(_VIM, KC_SCLN)
#define MY_V    LT(_VIM, KC_V)

// Configure mod-taps so that S=mod, D=alt, F=ctrl, J=ctrl, K=alt, L=mod, ;=vim
#define MY_S    LGUI_T(KC_S)
#define MY_D    LALT_T(KC_D)
#define MY_F    LCTL_T(KC_F)
#define MY_J    RCTL_T(KC_J)
#define MY_K    RALT_T(KC_K)
#define MY_L    RGUI_T(KC_L)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    KC_TAB,    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,             KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,KC_BSPC,
    MY_LCTL,   KC_A,   MY_S,   MY_D,   MY_F,   MY_G,             KC_H,   MY_J,   MY_K,   MY_L,MY_SCLN,KC_QUOT,
     PLOVER,   KC_Z,   KC_X,   KC_C,   MY_V,   KC_B,             KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH, LT(_R2, KC_ENT),
                              KC_LGUI, MY_LSP,KC_LSFT,      KC_RSFT, KC_RSP,MY_TRR
   ),

// NOTE: KC_MENU is used as a nonsense key to triggering a hotkey
  [_LOWER] = LAYOUT(
     KC_GRV,KC_EXLM,  KC_AT,KC_HASH, KC_DLR,KC_PERC,          KC_CIRC,KC_AMPR,KC_LPRN,KC_RPRN,KC_ASTR, KC_DEL,
    _______,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,          KC_PIPE,KC_PLUS,KC_LCBR,KC_RCBR, KC_EQL,KC_BSLS,
    _______,KC_MENU,_______,_______,TO(_VIM), KC_LT,          KC_GT,KC_MINS,KC_LBRC,KC_RBRC,KC_UNDS, KC_DEL,
                              _______,_______,_______,      _______,MO(_ADJUST),_______
  ),

  [_RAISE] = LAYOUT(
     KC_TILD,_______,   KC_7,   KC_8,   KC_9,_______,          KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN, KC_DEL,
     _______,_______,   KC_4,   KC_5,   KC_6,_______,          _______,_______,_______,_______,_______,_______,
 MO(_ADJUST),_______,   KC_1,   KC_2,   KC_3,_______,          _______,_______,_______,_______,_______,_______,
                              KC_ENT, KC_DOT,   KC_0,      _______,_______,_______
   ),

  [_R2] = LAYOUT(
     XXXXXXX,XXXXXXX,   KC_7,   KC_8,   KC_9,XXXXXXX,          XXXXXXX,   KC_7,   KC_8,   KC_9,XXXXXXX,XXXXXXX,
     XXXXXXX,XXXXXXX,   KC_4,   KC_5,   KC_6,XXXXXXX,          XXXXXXX,   KC_4,   KC_5,   KC_6,XXXXXXX,XXXXXXX,
     XXXXXXX,XXXXXXX,   KC_1,   KC_2,   KC_3,XXXXXXX,          XXXXXXX,   KC_1,   KC_2,   KC_3,XXXXXXX,XXXXXXX,
                              KC_0,    KC_DOT, KC_ENT,       KC_0  , KC_DOT, KC_ENT
   ),

  [_VIM] = LAYOUT(
    XXXXXXX,XXXXXXX,XXXXXXX,  VIM_E,XXXXXXX,XXXXXXX,          XXXXXXX,XXXXXXX, KC_INS,XXXXXXX,KC_PGUP,KC_HOME,
    VIM_EXT,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,          KC_LEFT,KC_DOWN,  KC_UP,KC_RGHT,KC_PGDN,KC_END,
    XXXXXXX,XXXXXXX, KC_DEL,XXXXXXX,XXXXXXX,  VIM_B,          XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
                              KC_LGUI, KC_SPC,KC_LSFT,      KC_RSFT, KC_SPC,_______
   ),

  [_ADJUST] = LAYOUT(
    _______,_______,_______,_______, KC_RST,_______,          _______,_______,_______,_______,KC_PSCR, KC_CAD,
    _______,_______, PLOVER,_______,_______,_______,          _______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,          KC_NLCK,_______,_______,_______,_______,_______,
                              _______,_______,_______,      _______,_______,_______
  ),

  [_FUNCTION] = LAYOUT(
     KC_F12,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,            KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11,
    _______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,          KC_MPRV,KC_VOLD,KC_VOLU,KC_MNXT,XXXXXXX,XXXXXXX,
    _______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,          XXXXXXX,KC_MUTE,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
                              _______,_______,_______,      _______,KC_MPLY,_______
  ),

  [_STENO] = LAYOUT(
    XXXXXXX, STN_N1, STN_N2, STN_N3, STN_N4, STN_N5,           STN_N6, STN_N7, STN_N8, STN_N9,XXXXXXX,XXXXXXX,
    XXXXXXX, STN_S1, STN_TL, STN_PL, STN_HL, STN_ST1,         STN_ST3, STN_FR, STN_PR, STN_LR, STN_TR, STN_DR,
   EXIT_PLV, STN_S2, STN_KL, STN_WL, STN_RL, STN_ST2,         STN_ST4, STN_RR, STN_BR, STN_GR, STN_SR, STN_ZR,
                                 STN_A, STN_O, XXXXXXX,      XXXXXXX,   STN_E,  STN_U
   ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case VIM_B:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL(SS_TAP(X_LEFT)));
        // SEND_STRING("bb");
      }
      return false;
      break;
    case VIM_E:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL(SS_TAP(X_RIGHT)));
        // SEND_STRING("ee");
      }
      return false;
      break;
    case VIM_EXT:
      if (record->event.pressed) {
        layer_off(_VIM);
      }
      return false;
      break;
    case PLOVER:
      if (!record->event.pressed) {
        layer_on(_STENO);
      }
      return false;
      break;
    case EXIT_PLV:
      if (record->event.pressed) {
        layer_off(_STENO);
      }
      return false;
      break;
  }
  return true;
}

/*
uint8_t get_dance(qk_tap_dance_state_t *state) {
  switch (state->count) {
    case 1:
      if (!state->pressed)
        return SINGLE_TAP;
      else
        return SINGLE_HOLD;
    case 2:
      return DOUBLE_TAP;
    case 3:
      return TRIPLE_TAP;
  }
  return OVER_TAP;
}

static uint8_t tap_state = 0;

void ql_finish(qk_tap_dance_state_t *state, void *user_data) {
  tap_state = get_dance(state);
  switch (tap_state) {
    case SINGLE_TAP:
      tap_code(KC_V);
      break;
    case SINGLE_HOLD:
      layer_on(_VIM);
      break;
      return;
    case DOUBLE_TAP:
      tap_code(KC_V);
      tap_code(KC_V);
      break;
    case TRIPLE_TAP:
      if (layer_state_is(_VIM)) {
        layer_off(_VIM);
      } else {
        layer_on(_VIM);
      }
      break;
      return;
  }
  // for (int i = 0; i < state->count; i++) {
  //   tap_code(KC_V);
  // }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (tap_state == SINGLE_HOLD) {
    layer_off(_VIM);
  }
  tap_state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  // Tap once for Escape, twice for Caps Lock
  // [TD_V_VIM] = ACTION_TAP_DANCE_DOUBLE(KC_B, TO(_VIM)),
  [TD_V_VIM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finish, ql_reset),
  [TD_S_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_B, KC_P),
};
*/

void matrix_init_user() {
    steno_set_mode(STENO_MODE_GEMINI);
}

// vim: colorcolumn=12,20,28,36,44,53,62,70,78,86,94,102
