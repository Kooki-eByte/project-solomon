#include <SDL3/SDL.h>
#include <math.h>

// Plug in deps
#define ARENA_IMPLEMENTATION
#include "deps/arena/arena.h"
#include "deps/glad/glad.h"

#define SDL_MAIN_USE_CALLBACKS 0
// Game Engine
#include "engine/engine.h"
#include "engine/envy/envy_shader.h"
#include "engine/graphics/buffer_handler.h"
#include "engine/graphics/vertex_array_handler.h"

// Global States
#include "global.h"

#define GLSL_VERT_FILE "engine/envy/defaults/default-test.vert"
#define GLSL_FRAG_FILE "engine/envy/defaults/default-test.frag"

static bool initGLLoader(void) {
  
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    fprintf(stderr, "Error: Failed to load sdl with GL? lol\n");
    return false;
  }

  return true;
}

int main(void) {
  // Initializing global settings/state for game window
  struct Global_Settings gs = {
    .width = 1280,
    .height = 720,
    .title = "Project Solomon",
    .is_game_running = true
  }; 
  // Game game = {0};

  f32 triangles[] = {
    //          COORDINATES                     |       COLORS(RGB)        //
    -0.5f,  -0.5f * (f32)(sqrt(3)) / 3,    0.0f,      0.0f, 1.0f, 0.0f,  // lower left vertex
    0.5f,   -0.5f * (f32)(sqrt(3)) / 3,    0.0f,      0.0f, 0.0f, 1.0f,  // lower right vertex 
    0.0f,   0.5f * (f32)(sqrt(3)) * 2 / 3, 0.0f,      1.0f, 0.0f, 0.0f,  // upper vertex 
    -0.5f / 2, 0.5f * (f32)(sqrt(3)) / 6,  0.0f,      0.5f, 0.5f, 0.0f,  // middle left 
    0.5f / 2, 0.5f  * (f32)(sqrt(3)) / 6,  0.0f,      0.5f, 0.0f, 0.5f,  // middle right
    0.0f, -0.5f * (f32)(sqrt(3)) / 3,      0.0f,      0.5f, 0.5f, 0.5f   // middle down
  };
  u32 tri_indices[] = {
    0, 5, 3,
    5, 1, 4,
    3, 4, 2
  };

// ------- Initial set up for SDL usage
  // Initialize SDL subsystems
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Error Initalization for video failed: %s\n", SDL_GetError());
    return 1;
  }

  // Request a GL 3.3 Core profile
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3); 
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // Window init
  SDL_Window *window = SDL_CreateWindow(gs.title, gs.width, gs.height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  if (!window) {
    fprintf(stderr, "Error Initalization for window failed: %s\n", SDL_GetError());
    return 1; 
  }

  // SDL context for openGL
  SDL_GLContext ctx = SDL_GL_CreateContext(window);
  if (!ctx) {
    fprintf(stderr, "Error Initalization for GL context failed: %s\n", SDL_GetError());
    return 1;  
  }

  // Calls static file to load SDL's function pointers with OpenGL functions? Maybe?
  if (!initGLLoader()) return 1;

  // Initial viewport set up
  glViewport(0, 0, gs.width, gs.height);
// --------- End Initial setup for SDL
  
  Envy_Shader e_shader = {0};
  if (!envy_CreateShadersFromFiles(&e_shader, GLSL_VERT_FILE, GLSL_FRAG_FILE)) {
    fprintf(stderr, "Failed to create shader program\n");
    return 1;
  }

  // Initialize vao, vbo, and ebo structs
  VAO vao1 = {0};
  VBO vbo1 = {
    .vertices = triangles,
    .size = sizeof(triangles)
  };
  EBO ebo1 = {
    .indices = tri_indices,
    .size = sizeof(tri_indices)
  };

  // Create Vertex objects and bind them
  genVAO(&vao1);
  bindVAO(&vao1);

  // Create and bind vertex/element objects
  bindVBO(&vbo1);
  bindEBO(&ebo1);

  //Link VBO to VAO
  // ENSURE VBO IS BINDED FIRST BEFORE LINKING
  // Coordinates Vertices (X,Y,Z)
  linkAttrib(0, 3, GL_FLOAT, 6 * sizeof(f32), (void *)0);
  // Color Vertices (RGB)
  linkAttrib(1, 3, GL_FLOAT, 6 * sizeof(f32), (void *)(3 * sizeof(f32)));

  unbindVAO();
  unbindVBO();
  unbindEBO();

  glEnable(GL_DEPTH_TEST);
  
  while (gs.is_game_running) {
    SDL_GL_SwapWindow(window);
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    envy_UseShader(&e_shader);
    bindVAO(&vao1);
    
    glDrawElements(GL_TRIANGLES, sizeof(tri_indices) / sizeof(b32), GL_UNSIGNED_INT, 0);

    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
      if (ev.type == SDL_EVENT_QUIT) gs.is_game_running = false;
      if (ev.type == SDL_EVENT_KEY_DOWN && ev.key.key == SDLK_ESCAPE) gs.is_game_running = false;
      
      // Window resize
      if (ev.type == SDL_EVENT_WINDOW_RESIZED || ev.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) {
        gs.width = ev.window.data1, gs.height = ev.window.data2;
        // Min width and height exceeded reset value to min width and height
        if (gs.width < 320) gs.width = 320;
        if (gs.height < 240) gs.height = 240;
        glViewport(0, 0, gs.width, gs.height);
      }
    }
  }

  // solomonEngineInit(&game, &gs);

  // killEngine(&game);
  deleteVAO(&vao1);
  deleteBuffers(&vbo1, &ebo1);
  envy_DestroyShader(&e_shader);

  SDL_GL_DestroyContext(ctx);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
