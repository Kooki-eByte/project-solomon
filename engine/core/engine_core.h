#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include "../engine.h"

// IMGUI SETUP
// For debugging purposes only
#ifdef ENGINE_DEBUG
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
#endif // ENGINE_DEBUG

#endif // ENGINE_CORE_H