void initGameState(GameState *gameState) {
    gameState->initialized = true;
    loadAnimations(gameState);
    makePlayer(gameState);

}

GameState *allocateGameState() {
    GameState * result = pushStruct(&globalLongTermArena, GameState);
    initGameState(result);
    return result;
    
}