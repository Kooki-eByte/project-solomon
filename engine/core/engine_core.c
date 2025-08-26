#include "engine_core.h"

static bool initGLLoader() {
  return !gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) ? false : true;
}

bool solomonEngineStartup(GameEngineConfigs *engine_config, EngineCorePlatform *platform) {
  // Forward declare window and glctx
  // Can't use platform due to it being invalid to SDL
  // \(T_T)/
  SDL_Window *win;
  SDL_GLContext glctx;
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    g_log_error("Failure to initialize SDL and its subsystems");
    return false;
  }

  // Request a GL 3.3 Core profile
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3); 
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  win = SDL_CreateWindow(engine_config->game_title, engine_config->width, engine_config->height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  if (!win) {
    fprintf(stderr, "Window failed. Here is why: %s\n", SDL_GetError());
    return false;
  }
  platform->window = win;

  glctx = SDL_GL_CreateContext(win);
  if (!glctx) {
    fprintf(stderr, "Context failed. Here is why: %s\n", SDL_GetError());
    return false;
  }
  platform->ctx = glctx;

  if (!initGLLoader()) {
    g_log_error("Failed to retrieve GL loader");
    return false;
  }
  return true;
}

bool solomonWindowStartup(GameEngineConfigs *engine_config, EngineCorePlatform *platform) {
  platform->window = SDL_CreateWindow(engine_config->game_title, engine_config->width, engine_config->height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  return !platform->window ? false : true;
}

bool solomonContextStartup(SDL_Window *w, SDL_GLContext ctx) {
  ctx = SDL_GL_CreateContext(w);
  return !ctx ? false : true;
}