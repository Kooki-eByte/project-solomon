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


bool solomonEngineRun(GameEngineConfigs *engine_config, const SolomonGameCallbacks *cb, EngineCorePlatform *platform) {
  SDL_GL_SwapWindow(platform->window);
  
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // --- Handle Shader | VAO | VBO | EBO --- //
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

  // --- END of Handling Shader | VAO | VBO | EBO --- //  

  const f32 dt = (engine_config->target_fps > 0.0f) ? (1.0f / engine_config->target_fps) : 0.0f;
  uint64_t prev_time = SDL_GetPerformanceCounter();
  f64 acc = 0.0;

  if (!cb->initialize || !cb->initialize(cb->game_state)) {
    g_log_error("Please create a initialize function");
    return false;
  }

  while (engine_config->is_engine_running) {
    // --- Events ---
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
      if (ev.type == SDL_EVENT_QUIT) engine_config->is_engine_running = false;
      if (ev.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) engine_config->is_engine_running = false;
      if (cb->on_event) cb->on_event(cb->game_state, &ev);
      // Handle window resize, focus, etc...
    }

    envy_UseShader(&e_shader);
    bindVAO(&vao1);

    // --- Timing ---
    uint64_t now = SDL_GetPerformanceCounter();
    uint64_t frame = now - prev_time;
    prev_time = now;

    if (engine_config->max_frame_dt > 0.0f && frame > engine_config->max_frame_dt) {
      frame = engine_config->max_frame_dt;
    }

    // Handle update
    if (dt > 0.0f) {
      acc += frame;
      while (acc >= dt) {
        cb->update(cb->game_state, dt);
        acc -= dt;
      }
      f32 alpha = (f32)(acc / dt);

      // Handle render step
      cb->render(cb->game_state, alpha);
    } else {
      // Variable step path
      cb->update(cb->game_state, (f32)frame);
      cb->render(cb->game_state, 1.0f);
    }
  }

  // TODO: Make a check in the beginning to make sure the game side did its job to 
  // have functions and make sure they are stored in the callback struct.
  cb->shutdown ? cb->shutdown(cb->game_state) : (void)0;

  // Teardown graphics -- might be better after SdL stuff but idk
  deleteVAO(&vao1);
  deleteBuffers(&vbo1, &ebo1);
  envy_DestroyShader(&e_shader);

  // Teardown GL/SDL
  SDL_GL_DestroyContext(platform->ctx);
  SDL_DestroyWindow(platform->window);
  SDL_Quit();
  return true;
}