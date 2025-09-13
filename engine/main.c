// Plug in deps
#define ARENA_IMPLEMENTATION
#include "../deps/arena/arena.h"
#include "../deps/glad/glad.h"

#define SDL_MAIN_USE_CALLBACKS 0

// Game Engine
#include "engine.h"

// Game
#include "../platformer/state/game.h"

// NOTE:(Cristian) Main entrypoint is in engine, Engine will be in control of running the game and controlling it via the game callbacks

int main(void) {
  // TODO:(Cristian) Handle these initializations with Arena
  // Initializing state for game and engine config data
  GameEngineConfigs gec = {.width = 1280,
                           .height = 720,
                           .game_title = "Project Solomon",
                           .enable_vsync = true,
                           .enable_imgui = false,
                           .target_fps = 60.0f,
                           .max_frame_dt = 0.25f,
                           .is_engine_running = true};
  EngineCorePlatform platform = {0};
  GameState *gs = (GameState *)malloc(sizeof(GameState));

  // from game side
  SolomonGameCallbacks cb = {.initialize = gameInit,
                             .update = gameUpdate,
                             .render = gameRender,
                             .shutdown = gameShutdown,
                             .on_event = gameOnEvent,
                             .game_state = &gs};

  // --- Initial set up for SDL usage --- //
  solomonEngineStartup(&gec, &platform);

  return solomonEngineRun(&gec, &cb, &platform);
}
