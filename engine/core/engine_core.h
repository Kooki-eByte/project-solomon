#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include "../engine.h"

// TODO: This is to initialize everything needed for the core engine to run. 
// Will be called by game main.c

typedef struct EngineCorePlatform {
  SDL_Window *window;
  // TODO: Check if * needs to be removed
  SDL_GLContext ctx;
} EngineCorePlatform;

// SDL Initialize Subsystems | Request GL 3.3 Core Profile |
bool solomonEngineStartup(GameEngineConfigs *engine_config, EngineCorePlatform *platform);

// TODO: Can be static functions most likely
bool solomonWindowStartup(GameEngineConfigs *engine_config, SDL_Window *w);

bool solomonContextStartup(SDL_Window *w, SDL_GLContext ctx);

#endif