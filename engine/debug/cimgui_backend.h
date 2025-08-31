#ifndef SOLOMON_CIMGUI_BACKEND_H
#define SOLOMON_CIMGUI_BACKEND_H

#include <SDL3/SDL.h>
#include "../../deps/cimgui/cimgui.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// SDL3 Backend
bool cimgui_ImplSDL3_InitForOpenGL(SDL_Window* window, void* gl_ctx);
void cimgui_ImplSDL3_Shutdown(void);
void cimgui_ImplSDL3_NewFrame(void);
bool cimgui_ImplSDL3_ProcessEvent(const SDL_Event* e);

// OpenGL backend
// Can check out what glsl version you have from this site:
// https://www.khronos.org/opengl/wiki/Core_Language_(GLSL)
bool cimgui_ImplOpenGL3_Init(const char* glsl_version);
void cimgui_ImplOpenGL3_Shutdown(void);
void cimgui_ImplOpenGL3_NewFrame(void);
void cimgui_ImplOpenGL3_RenderDrawData(ImDrawData* data);
#ifdef __cplusplus
}
#endif // __cplusplus
#endif // SOLOMON_CIMGUI_BACKEND_H