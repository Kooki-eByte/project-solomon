#ifndef SOLOMON_ENGINE_H
#define SOLOMON_ENGINE_H

#include "../deps/glad/glad.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_timer.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define SDL_FLAGS SDL_INIT_VIDEO

#include "../defines.h"
#include "../global.h"

#ifdef ENGINE_DEBUG
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "debug/cimgui_backend.h"
#endif // ENGINE_DEBUG

#include "logging/greed.h"
#include "graphics/envy/envy_shader.h"
#include "graphics/buffer_handler.h"
#include "graphics/texture_handler.h"
#include "graphics/vertex_array_handler.h"

// Setting default size of a region in an arena
#define ARENA_REGION_DEFAULT_CAPACITY (KIB * 5)
#include "memory/arena/arena.h"



#define GLSL_VERT_FILE "engine/graphics/envy/defaults/default-test.vert"
#define GLSL_FRAG_FILE "engine/graphics/envy/defaults/default-test.frag"

// TODO: This is for later but will be useful when moving to game code
typedef struct SolomonGameCallbacks {  
  // Function pointer to game initialize function
  bool (*initialize)(void *game_state);

  // Function Pointer to game update function
  void (*update)(void *game_state, f32 delta_time);

  // Function pointer to game render function
  // TODO: Remove bool toggle later, was made for debug purposes
  void (*render)(void *game_state, f32 delta_time, bool toggle);

  void (*shutdown)(void *game_state);

  // Function pointer to handle event callback, allowing game to consume SDL_Event
  void (*on_event)(void *game_state, const void *sdl_event);

  // Game-Specific game state. Created and managed by the game side!
  void *game_state;
} SolomonGameCallbacks;

typedef struct GameEngineConfigs {
  u32 width, height;
  const char *game_title;
  bool enable_vsync;
  bool enable_imgui;

  // Fixed-step target => 60.0f; Set <=0 for varibale step
  f32 target_fps;
  // caps/clamps; Handles hitches
  f32 max_frame_dt;

  bool is_engine_running;
} GameEngineConfigs;

typedef struct EngineCorePlatform {
  SDL_Window *window;
  // TODO: Check if * needs to be removed
  SDL_GLContext ctx;
  #ifdef ENGINE_DEBUG
  ImGuiContext *imgui_ctx;
  #endif // ENGINE_DEBUG
} EngineCorePlatform;

// SDL Initialize Subsystems | Request GL 3.3 Core Profile |
bool solomonEngineStartup(GameEngineConfigs *engine_config, EngineCorePlatform *platform);

// Handles Engine running with gameloop
bool solomonEngineRun(GameEngineConfigs *engine_config, const SolomonGameCallbacks *cb, EngineCorePlatform *platform);
#endif // SOLOMON_ENGINE_H
