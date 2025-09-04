#include "inputhandler.h"
#include "../logging/greed.h"

// NOTE:(Cristian) Handling state for keyboard/mouse
typedef struct keyboard_state {
  bool keys[KEYS_MAX_KEYS];
} keyboard_state;

typedef struct mouse_state {
  i16 x;
  i16 y;
  u8 buttons[BUTTON_MAX_BUTTONS];
} mouse_state;

typedef struct input_state {
  keyboard_state keyboard_curr;
  keyboard_state keyboard_prev;
  mouse_state mouse_curr;
  mouse_state mouse_prev;
} input_state;

// Internal input state
static bool initialized = false;
static input_state = {0};