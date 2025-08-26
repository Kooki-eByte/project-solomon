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
    .max_frame_dt = 0.25f
  }; 
  EngineCorePlatform platform = {0};
  GameState gs = {0};

  SolomonGameCallbacks cb = {
    .initialize = gameInit,
    .update = gameUpdate,
    .render = gameRender,
    .shutdown = gameShutdown,
    .on_event = gameOnEvent,
    .game_state = &gs
  };

  // f32 triangles[] = {
  //   //          COORDINATES                     |       COLORS(RGB)        //
  //   -0.5f,  -0.5f * (f32)(sqrt(3)) / 3,    0.0f,      0.0f, 1.0f, 0.0f,  // lower left vertex
  //   0.5f,   -0.5f * (f32)(sqrt(3)) / 3,    0.0f,      0.0f, 0.0f, 1.0f,  // lower right vertex 
  //   0.0f,   0.5f * (f32)(sqrt(3)) * 2 / 3, 0.0f,      1.0f, 0.0f, 0.0f,  // upper vertex 
  //   -0.5f / 2, 0.5f * (f32)(sqrt(3)) / 6,  0.0f,      0.5f, 0.5f, 0.0f,  // middle left 
  //   0.5f / 2, 0.5f  * (f32)(sqrt(3)) / 6,  0.0f,      0.5f, 0.0f, 0.5f,  // middle right
  //   0.0f, -0.5f * (f32)(sqrt(3)) / 3,      0.0f,      0.5f, 0.5f, 0.5f   // middle down
  // };
  // u32 tri_indices[] = {
  //   0, 5, 3,
  //   5, 1, 4,
  //   3, 4, 2
  // };

  // --- Initial set up for SDL usage --- //
  solomonEngineStartup(&gec, &platform);
  
  // Envy_Shader e_shader = {0};
  // if (!envy_CreateShadersFromFiles(&e_shader, GLSL_VERT_FILE, GLSL_FRAG_FILE)) {
  //   fprintf(stderr, "Failed to create shader program\n");
  //   return 1;
  // }

  // // Initialize vao, vbo, and ebo structs
  // VAO vao1 = {0};
  // VBO vbo1 = {
  //   .vertices = triangles,
  //   .size = sizeof(triangles)
  // };
  // EBO ebo1 = {
  //   .indices = tri_indices,
  //   .size = sizeof(tri_indices)
  // };

  // // Create Vertex objects and bind them
  // genVAO(&vao1);
  // bindVAO(&vao1);

  // // Create and bind vertex/element objects
  // bindVBO(&vbo1);
  // bindEBO(&ebo1);

  // //Link VBO to VAO
  // // ENSURE VBO IS BINDED FIRST BEFORE LINKING
  // // Coordinates Vertices (X,Y,Z)
  // linkAttrib(0, 3, GL_FLOAT, 6 * sizeof(f32), (void *)0);
  // // Color Vertices (RGB)
  // linkAttrib(1, 3, GL_FLOAT, 6 * sizeof(f32), (void *)(3 * sizeof(f32)));

  // unbindVAO();
  // unbindVBO();
  // unbindEBO();

  // glEnable(GL_DEPTH_TEST);
 
  // Can probably be handled in game section of folder for game loop?
  // TODO: Research where this loop should be and how to craft a proper game loop
  // bool is_game_running = true;
  // while (is_game_running) {
  //   SDL_GL_SwapWindow(platform.window);
    
  //   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
  //   // envy_UseShader(&e_shader);
  //   // bindVAO(&vao1);
    
  //   // glDrawElements(GL_TRIANGLES, sizeof(tri_indices) / sizeof(b32), GL_UNSIGNED_INT, 0);

  //   SDL_Event ev;
  //   while (SDL_PollEvent(&ev)) {
  //     if (ev.type == SDL_EVENT_QUIT) is_game_running = false;
  //     if (ev.type == SDL_EVENT_KEY_DOWN && ev.key.key == SDLK_ESCAPE) is_game_running = false;
      
  //     // Window resize
  //     if (ev.type == SDL_EVENT_WINDOW_RESIZED || ev.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) {
  //       gec.width = ev.window.data1, gec.height = ev.window.data2;
  //       // Min width and height exceeded reset value to min width and height
  //       if (gec.width < 320) gec.width = 320;
  //       if (gec.height < 240) gec.height = 240;
  //       glViewport(0, 0, gec.width, gec.height);
  //     }
  //   }
  // }

  // solomonEngineInit(&game, &gs);

  // killEngine(&game);
  // deleteVAO(&vao1);
  // deleteBuffers(&vbo1, &ebo1);
  // envy_DestroyShader(&e_shader)

  return solomonEngineRun(&gec, &cb, &platform);
}
