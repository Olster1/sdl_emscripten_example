#include <SDL.h>
#include <stdbool.h>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include "../platform.h"
#include "../main.cpp"


static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static int w = 800, h = 450;
static float x = 0.f, speed = 120.f; // px/sec
static Uint32 lastTicks = 0;

static void frame(void* arg) {
  GameState *gameState = (GameState *)arg;
  Uint32 now = SDL_GetTicks();
  float dt = (now - lastTicks) / 1000.0f;
  lastTicks = now;

  // Move rect
  x += speed * dt;
  if (x < 0) { x = 0; speed = -speed; }
  if (x > w - 100) { x = w - 100; speed = -speed; }

  // Draw
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  SDL_Rect r = { (int)x, h/2 - 25, 100, 50 };
  SDL_SetRenderDrawColor(renderer, 220, 255, 120, 255);
  SDL_RenderFillRect(renderer, &r);

  SDL_RenderPresent(renderer);

  updateGame(gameState);
}

int main(int argc, char** argv) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
    SDL_Log("SDL_Init failed: %s", SDL_GetError());
    return 1;
  }

  window = SDL_CreateWindow("SDL + Emscripten (ESM)",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    w, h, SDL_WINDOW_SHOWN);
  if (!window) {
    SDL_Log("CreateWindow failed: %s", SDL_GetError());
    return 1;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    SDL_Log("CreateRenderer failed: %s", SDL_GetError());
    return 1;
  }

  initMemoryArenas();
  GameState *gameState = allocateGameState();

  lastTicks = SDL_GetTicks();

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop_arg(frame, gameState, 0, 1);
#else
  // Desktop fallback (optional)
  bool running = true;
  while (running) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) running = false;
    }
    refreshPerFrameArena();
    frame(gameState);
    SDL_Delay(16);
  }
  SDL_Quit();
#endif
  return 0;
}
