#include "./includes.h"

void updateGame(GameState *gameState) {
    assert(gameState->initialized);
    float2 plane = make_float2(100, 100*gameState->aspectRatioWindow_y_over_x);
    float16 viewT = make_ortho_matrix_origin_center(plane.x, plane.y, MATH_3D_NEAR_CLIP_PlANE, MATH_3D_FAR_CLIP_PlANE);

    updateCamera(&gameState->camera, make_float3(0, 0, 0));

    float16 worldToCameraT = makeWorldToCameraT(&gameState->camera);
    pushRenderView(&gameState->renderer, float16_multiply(viewT, worldToCameraT));        
    
    updateEntities(gameState, gameState->dt);
}