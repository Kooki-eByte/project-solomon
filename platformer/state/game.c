#include "game.h"

bool gameInit(void *game_state) {
  GameState *gs = (GameState*)game_state;
  if (game_state == NULL) {
    fprintf(stderr, "Game State needs to be initialized with {0}\n");
    return false;
  }

  gs->is_game_running = true;
  return true;
}

void gameUpdate(void *game_state, f32 delta_time) {
  (void)game_state;
  (void)delta_time;
  // advance sim: input -> ECS -> physics -> scripts
}

// TODO: Remove toggle param later
void gameRender(void *game_state, f32 delta_time, bool toggle) {
  (void)game_state;
  (void)delta_time;

  if (toggle) {
    glDrawElements(GL_TRIANGLES, (sizeof(u32) * 9) / sizeof(b32), GL_UNSIGNED_INT, 0);
  }
}

void gameShutdown(void *game_state) {
  (void)game_state;
  // Free allocations and assets for game.
}

void gameOnEvent(void *game_state, const void *sdl_event) {
  (void)game_state;
  
  printf("We have reached the gameOnEvent function in platformer side");

  const SDL_Event *ev = (const SDL_Event*)sdl_event;
  switch (ev->type) {
    case SDL_EVENT_KEY_DOWN:
      if (ev->key.key == SDLK_W) {
        printf("W");
        // TODO: do something here
      }
      if (ev->key.key == SDLK_A) {
        printf("A");
        // TODO: do something here
      }
      if (ev->key.key == SDLK_S) {
        printf("S");
        // TODO: do something here
      }
      if (ev->key.key == SDLK_D) {
        printf("D");
        // TODO: do something here
      }
      break;
      // Handle more event inputs here for game logic
    default:
      break;
  }
}