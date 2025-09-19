// Plug in deps
#include "../deps/glad/glad.h"

#define SDL_MAIN_USE_CALLBACKS 0

// Game Engine
#include "engine.h"

// Game
#include "../platformer/state/game.h"

static Arena engine_arena = {0};

// NOTE:(Cristian) Main entrypoint is in engine, Engine will be in control of running the game and controlling it via the game callbacks
int main(void) {
  GameEngineConfigs *engine_config = arena_alloc(&engine_arena, sizeof(GameEngineConfigs)); 
  engine_config->width = 1280;
  engine_config->game_title = "Project Solomon";
  engine_config->height = 720;
  engine_config->enable_vsync = true;
  engine_config->enable_imgui = false;
  engine_config->target_fps = 60.0f;
  engine_config->max_frame_dt = 0.25f;
  engine_config->is_engine_running = true;

  EngineCorePlatform *engine_platform = arena_alloc(&engine_arena, sizeof(EngineCorePlatform));
  engine_platform->ctx = 0x0;
  engine_platform->imgui_ctx = 0x0;
  engine_platform->window = 0x0;

  GameState *gs = arena_alloc(&engine_arena ,sizeof(GameState));
  gs->is_game_running = false;

  // from game side
  SolomonGameCallbacks cb = {
    .initialize = gameInit,
    .update = gameUpdate,
    .render = gameRender,
    .shutdown = gameShutdown,
    .on_event = gameOnEvent,
    .game_state = &gs
  };

  // --- Initial set up for SDL usage --- //
  solomonEngineStartup(engine_config, engine_platform);

  if (solomonEngineRun(engine_config, &cb, engine_platform)) {
    arena_free(&engine_arena);
  }
  return 0;

}
