#ifndef GAME_H
#define GAME_H

#include "../../defines.h"
#include "../../deps/glad/glad.h"
#include "SDL3/SDL_events.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct GameState {
  bool is_game_running;
  // Store player data, scene graph, inventory, rng seeds, etc
} GameState;

// Functions we will use to feed to the function pointers from the engine code
bool gameInit(void *game_state);

void gameUpdate(void *game_state, f32 delta_time);

void gameRender(void *game_state, f32 delta_time);

void gameShutdown(void *game_state);

void gameOnEvent(void *game_state, const void *sdl_event);

#endif