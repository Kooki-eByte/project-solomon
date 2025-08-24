#ifndef SOLOMON_ENGINE_H
#define SOLOMON_ENGINE_H


// #include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>

#define SDL_FLAGS SDL_INIT_VIDEO

#include "../defines.h"
#include "../global.h"
#include "logging/greed.h"

typedef struct Game {
  SDL_Window *window;
  SDL_GLContext *ctx;
  bool is_vsync;
} Game;

// Window Handling
// void initWindow(Game *g, struct Global_Settings *gs);

// void initContext(Game *g, struct Global_Settings *gs);

// void windowPump(f32 *dt, Game *g, struct Global_Settings *gs);

// void solomonEngineInit(Game *g, struct Global_Settings *gs);

// void swapWindowBuffer(Game *g);

// void killEngine(Game *g);

#endif // SOLOMON_ENGINE_H
