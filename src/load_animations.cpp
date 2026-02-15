void loadAnimations(GameState *gameState) {
    // gameState->playerAnimations.idle = ;
}

void loadImages(GameState *gameState) {
    gameState->imageFiles.mapImage = platform_loadImage("../assets/images/map.png", &globalLongTermArena);
}