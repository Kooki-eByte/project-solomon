#ifndef SOLOMON_ENGINE_H
#define SOLOMON_ENGINE_H

#include "../deps/glad/glad.h"

#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SDL_FLAGS SDL_INIT_VIDEO


#include "../defines.h"
#include "../global.h"

#include "logging/greed.h"

// TODO: This is for later but will be useful when moving to game code
typedef struct SolomonGameCallbacks {  
  // Function pointer to game initialize function
  bool (*initialize)(struct SolomonGameCallbacks *game_inst);

  // Function Pointer to game update function
  bool (*update)(struct SolomonGameCallbacks *game_inst, f32 delta_time);

  // Function pointer to game render function
  bool (*render)(struct SolomonGameCallbacks *game_inst, f32 delta_time);

  // Function pointer to handle resize
  void (*on_resize)(struct SolomonGameCallbacks *game_inst, u32 width, u32 height);

  // Game-Specific game state. Created and managed by the game side!
  void *state;
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
} GameEngineConfigs;

#endif // SOLOMON_ENGINE_H
