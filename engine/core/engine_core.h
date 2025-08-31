#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include "../engine.h"

#ifdef ENGINE_CORE_DEBUG
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "../debug/cimgui_backend.h"
#endif // ENGINE_CORE_DEBUG

typedef struct EngineCorePlatform {
  SDL_Window *window;
  // TODO: Check if * needs to be removed
  SDL_GLContext ctx;
  #ifdef ENGINE_CORE_DEBUG
  ImGuiContext *imgui_ctx;
  #endif // ENGINE_DEBUG
} EngineCorePlatform;

// SDL Initialize Subsystems | Request GL 3.3 Core Profile |
bool solomonEngineStartup(GameEngineConfigs *engine_config, EngineCorePlatform *platform);

// Handles Engine running with gameloop
bool solomonEngineRun(GameEngineConfigs *engine_config, const SolomonGameCallbacks *cb, EngineCorePlatform *platform);

// IMGUI SETUP
// For debugging purposes only
#ifdef ENGINE_CORE_DEBUG
#define GLSL_VERSION "#version 330"


bool solomonEngineImguiInit(EngineCorePlatform *platform) {
  // Create Dear ImGui context
  ImGuiContext *ctx = igCreateContext(NULL);
  igSetCurrentContext(ctx);
  if (ctx == NULL) {
    fprintf(stderr, "Error: Creating context for Cimgui failed!\n"); 
    return false;
  }

  platform->imgui_ctx = ctx;

  // Setup IO / Config flags (optional)
  ImGuiIO *io = igGetIO_ContextPtr(ctx);
  io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  // Init Backends
  cimgui_ImplSDL3_InitForOpenGL(platform->window, platform->ctx);
  cimgui_ImplOpenGL3_Init(GLSL_VERSION);

  return true;
}

void solomonEngineImguiShutdown(EngineCorePlatform *p) {
  cimgui_ImplOpenGL3_Shutdown();
  cimgui_ImplSDL3_Shutdown();
  igDestroyContext(p->imgui_ctx);
}
#endif // ENGINE_CORE_DEBUG

#endif // ENGINE_CORE_H