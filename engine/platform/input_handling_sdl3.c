#ifdef SDL_INPUT_HANDLING

#include "../input/input.h"

void process_input(SolomonGameCallbacks *cb, GameEngineConfigs *ec) {
  SDL_Event ev;

  while (SDL_PollEvent(&ev)) {

#ifdef ENGINE_DEBUG
      cimgui_ImplSDL3_ProcessEvent(&ev);
#endif // ENGINE_DEBUG

      if (ev.type == SDL_EVENT_QUIT)
        ec->is_engine_running = false;
      if (ev.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
        ec->is_engine_running = false;
      if (ev.type == SDL_EVENT_KEY_DOWN && ev.key.key == SDLK_ESCAPE)
        ec->is_engine_running = false;
      if (ev.type == SDL_EVENT_KEY_DOWN && ev.key.key == SDLK_M) {
        ec->enable_imgui = !ec->enable_imgui;
      }

      if (cb->on_event) {
        cb->on_event(cb->game_state, &ev);
      }

      // Window resize
      if (ev.type == SDL_EVENT_WINDOW_RESIZED ||
          ev.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) {
        ec->width = ev.window.data1,
        ec->height = ev.window.data2;
        // Min width and height exceeded reset value to min width and height
        if (ec->width < 320)
          ec->width = 320;
        if (ec->height < 240)
          ec->height = 240;
        glViewport(0, 0, ec->width, ec->height);
      }
    }
}

#endif // SDL_INPUT_HANDLING