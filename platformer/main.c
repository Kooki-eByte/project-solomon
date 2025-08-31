// #include <SDL3/SDL.h>
#include <math.h>

// Plug in deps
#define ARENA_IMPLEMENTATION
#include "../deps/arena/arena.h"
#include "../deps/glad/glad.h"

#define SDL_MAIN_USE_CALLBACKS 0
// Game Engine
#include "../engine/core/engine_core.h"
#include "../engine/graphics/envy/envy_shader.h"
#include "../engine/graphics/buffer_handler.h"
#include "../engine/graphics/vertex_array_handler.h"

// Global States
#include "../global.h"

// Game
#include "state/game.h"


int main(void) {
  // Initializing state for game and engine config data
  GameEngineConfigs gec = {
    .width = 1280,
    .height = 720,
    .game_title = "Project Solomon",
    .enable_vsync = true,
    .enable_imgui = false,
    .target_fps = 60.0f,
    .max_frame_dt = 0.25f,
    .is_engine_running = true
  }; 
  EngineCorePlatform platform = {0};
  GameState *gs = (GameState*)malloc(sizeof(GameState));

  SolomonGameCallbacks cb = {
    .initialize = gameInit,
    .update = gameUpdate,
    .render = gameRender,
    .shutdown = gameShutdown,
    .on_event = gameOnEvent,
    .game_state = &gs
  };

  // --- Initial set up for SDL usage --- //
  solomonEngineStartup(&gec, &platform);

  return solomonEngineRun(&gec, &cb, &platform);
}
