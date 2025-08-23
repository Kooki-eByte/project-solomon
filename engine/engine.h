#ifndef SOLOMON_ENGINE_H
#define SOLOMON_ENGINE_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>

#define SDL_FLAGS SDL_INIT_VIDEO

#include "../defines.h"

typedef struct Game {
  SDL_Window *window;
  SDL_Renderer *renderer;
} Game;

// Returns true or false if initialization fails
bool solomonEngineInit(Game *g);

void initWindow(Game *g, const char *title, b32 w, b32 h);

void initRenderer(Game *g);

void killEngine(Game *g);

void startEngine(SDL_Renderer *r);

#endif // SOLOMON_ENGINE_H
