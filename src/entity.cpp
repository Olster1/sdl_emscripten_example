u64 global_entity_id = 1;

void initBaseEntity(Entity *e) {
    easyMemory_zeroSize(e, sizeof(Entity));

    e->id = global_entity_id++;
    e->T.pos.z = RENDER_PLANE_Z;
}

void makePlayer(GameState *gameState) {
    if(gameState->entityCount < arrayCount(gameState->entities)) {
        Entity *e = gameState->entities + gameState->entityCount++;
        initBaseEntity(e);
        e->flags |= ENTITY_FLAG_MOVE_PLAYER;
        e->defaultAnimations = &gameState->playerAnimations;
    }
}

void updateEntity(GameState *gameState, Entity *e, float dt) {
    if(e->flags & ENTITY_FLAG_MOVE_PLAYER) {
        // updatePlayerInput(gameState, e, dt);
    }
}

void renderEntity(GameState *gameState, Entity *e, float dt) {
     Texture *t = 0;

    if(easyAnimation_isControllerValid(&e->animationController)) {
        t = easyAnimation_updateAnimation_getTexture(&e->animationController, &gameState->animationState.animationItemFreeListPtr, dt);
    } 

    if(t) {
        pushRenderTexture(&gameState->renderer, e->T, t);
    }
}

void updateEntities(GameState *gameState, float dt) {
    for(int i = 0; i < gameState->entityCount; ++i) {
        Entity *e = gameState->entities + i;

        updateEntity(gameState, e, dt);
        renderEntity(gameState, e, dt);
    }
}