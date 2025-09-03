#include "./transform.cpp"
#include "./camera.cpp"
#include "./game_state.h"
#include "./game_state.cpp"
void updateGame(GameState *gameState) {
    assert(gameState->initialized);

    updateCamera(&gameState->camera, make_float3(0, 0, 0));
        

}