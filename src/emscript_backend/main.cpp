#define SDL_BUILD 1
#ifdef __EMSCRIPTEN__
#include <SDL.h>
#include <SDL_image.h>
#include <emscripten/emscripten.h>
#else 
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif

#include <stdbool.h>

#include "../platform.h"

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

Texture *platform_loadImage(char *fileName, Arena *arena) {
  SDL_Surface* surface = IMG_Load(fileName);
  if (!surface) {
      printf("IMG_Load failed: %s", IMG_GetError());
      assert(false);
      return 0;
  }

  int w = surface->w;
  int h = surface->h;

  // convert to texture
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  SDL_SetTextureScaleMode(texture, SDL_ScaleModeNearest);

  Texture *result = pushStruct(arena, Texture);

  result->width = w;
  result->height = h;
  result->uv = make_float4(0, 0, 1, 1);
  result->handle.handle = texture;

  return result;
}

void platform_deleteTexture(Texture *t) {
  if(t && t->handle.handle) {
    SDL_DestroyTexture((SDL_Texture *)t->handle.handle);
    t->handle.handle = 0;
  }
}

#include "../main.cpp"
#include "./backend_renderer.cpp"

static int w = 800, h = 450;
static float x = 0.f, speed = 120.f; // px/sec
static Uint32 lastTicks = 0;


static void frame(void* arg) {
  GameState *gameState = (GameState *)arg;
  Uint32 now = SDL_GetTicks();
  float dt = (now - lastTicks) / 1000.0f;
  lastTicks = now;

  // Draw
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  updateGame(gameState);
  processRenderGroup(renderer, &gameState->renderer, make_float2(w, h));

  SDL_RenderPresent(renderer);
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

  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

  initMemoryArenas();
  GameState *gameState = allocateGameState();
  gameState->aspectRatioWindow_y_over_x = (float)h / (float)w;

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
      if (e.type == SDL_DROPFILE) {
        char* droppedFile = e.drop.file;
        gameState->dragFileName = droppedFile;

      }
    }
    refreshPerFrameArena();
    frame(gameState);
    SDL_Delay(16);

    if(gameState->dragFileName) {
      SDL_free(gameState->dragFileName);
      gameState->dragFileName = 0;
    }
  }
  SDL_Quit();
#endif
  return 0;
}
