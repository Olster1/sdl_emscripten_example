void initGameState(GameState *gameState) {
    gameState->initialized = true;
}

GameState *allocateGameState() {
    GameState * result = pushStruct(&globalLongTermArena, GameState);
    initGameState(result);
    return result;
    
}