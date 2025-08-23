#include "engine.h"

bool solomonEngineInit(Game *g) {
  if (!SDL_Init(SDL_FLAGS)) {
    // TODO: Change to greed logger later
    fprintf(stderr, "Error initializing SDL3: %s\n", SDL_GetError());
    return false;
  }

  initWindow(g, "Test Title here", 1280, 720);
  initRenderer(g);

  return true;
}

void initWindow(Game *g, const char *title, b32 w, b32 h) {
  g->window = SDL_CreateWindow(title, w, h, 0);
  if (!g->window) {
    // TODO: Change to greed logger later
    fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
  }
}

void initRenderer(Game *g) {
  g->renderer = SDL_CreateRenderer(g->window, NULL);
  if (!g->renderer) {
    // TODO: Change to greed logger later
    fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
  }
}

void killEngine(Game *g) {
  if (g->renderer) {
    SDL_DestroyRenderer(g->renderer);
    g->renderer = NULL;
  }

  if (g->window) {
    SDL_DestroyWindow(g->window);
    g->window = NULL;
  }

  SDL_Quit();
}

void startEngine(SDL_Renderer *r) {
  SDL_RenderClear(r);

  SDL_RenderPresent(r);

  SDL_Delay(5000);
}