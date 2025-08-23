// Plug in deps
#define ARENA_IMPLEMENTATION
#include "deps/arena/arena.h"
#include "engine/engine.h"


int main(void) {
  Game game = {0};

  if(solomonEngineInit(&game)) {
    startEngine(game.renderer);
  }

  killEngine(&game);
  return 0;
}
