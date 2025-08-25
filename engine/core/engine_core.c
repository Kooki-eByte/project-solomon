#include "engine_core.h"

static bool initGLLoader(void) {
  return !gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) ? false : true;
}

bool solomonEngineStartup(GameEngineConfigs *engine_config, EngineCorePlatform *platform) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    g_log_error("Failure to initialize SDL and its subsystems");
    return false;
  }

  // Request a GL 3.3 Core profile
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3); 
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  if (!solomonWindowStartup(engine_config, platform->window)) {
    g_log_error("Failure to Create SDL Window");
    return false;
  }

  // FIXME: [ERROR][24/7/2025 -> 18:45:4]--[Failure to Create SDL GL Context on line 29 in file engine/core/engine_core.c]
  // if (!solomonContextStartup(platform->window, platform->ctx)) {
  //   g_log_error("Failure to Create SDL GL Context");
  //   return false;
  // }
  platform->ctx = SDL_GL_CreateContext(platform->window);

  if (!initGLLoader()) {
    g_log_error("Failed to retieve GL functions for glad");
    SDL_GL_DestroyContext(platform->ctx);
    SDL_DestroyWindow(platform->window);
    SDL_Quit();
    return false;
  }

  // Initalize first viewport set up
  glViewport(0, 0, engine_config->width, engine_config->height);
  return true;
}

bool solomonWindowStartup(GameEngineConfigs *engine_config, SDL_Window *w) {
  w = SDL_CreateWindow(engine_config->game_title, engine_config->width, engine_config->height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  return !w ? false : true;
}

bool solomonContextStartup(SDL_Window *w, SDL_GLContext ctx) {
  ctx = SDL_GL_CreateContext(w);
  return !ctx ? false : true;
}