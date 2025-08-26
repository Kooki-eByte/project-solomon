#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include "../engine.h"

// TODO: This is to initialize everything needed for the core engine to run.
// Hold the game loop and game loop calls the game callback functions 
// Will be called by game main.c

typedef struct EngineCorePlatform {
  SDL_Window *window;
  // TODO: Check if * needs to be removed
  SDL_GLContext ctx;
} EngineCorePlatform;

// SDL Initialize Subsystems | Request GL 3.3 Core Profile |
bool solomonEngineStartup(GameEngineConfigs *engine_config, EngineCorePlatform *platform);

// Handles Engine running with gameloop
bool solomonEngineRun(GameEngineConfigs *engine_config, const SolomonGameCallbacks *cb, EngineCorePlatform *platform);

#endif