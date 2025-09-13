#ifndef SOLOMON_DEBUG_H
#define SOLOMON_DEBUG_H

// IMGUI SETUP
// For debugging purposes only
#ifdef ENGINE_DEBUG

#include "cimgui_backend.h"

#define GLSL_VERSION "#version 330"

// NOTE:(Cristian) This is only used for SDL3 and openGL implementation for now!

ImGuiContext* solomonEngineImguiInit(SDL_Window *window, SDL_GLContext sdl_ctx) {
  // Create Dear ImGui context
  ImGuiContext *ctx = igCreateContext(NULL);
  igSetCurrentContext(ctx);
  if (ctx == NULL) {
    fprintf(stderr, "Error: Creating context for Cimgui failed!\n");
    return ctx; 
  }

  // Setup IO / Config flags (optional)
  ImGuiIO *io = igGetIO_ContextPtr(ctx);
  io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  // Init Backends
  cimgui_ImplSDL3_InitForOpenGL(window, sdl_ctx);
  cimgui_ImplOpenGL3_Init(GLSL_VERSION);

  return ctx;
}

void solomonEngineImguiShutdown(ImGuiContext *ctx) {
  cimgui_ImplOpenGL3_Shutdown();
  cimgui_ImplSDL3_Shutdown();
  igDestroyContext(ctx);
}
#endif // ENGINE_DEBUG

#endif // end SOLOMON_DEBUG_H
