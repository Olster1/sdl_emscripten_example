struct GameState {
    bool initialized;

    float aspectRatioWindow_y_over_x;
    Renderer renderer;
    char *dragFileName;

    Texture *viewTexture;

    int tileCount;
	MapTile tiles[10000];

    int entityCount;
    Entity entities[256];

    float dt;

    AnimationState animationState;
    DefaultEntityAnimations playerAnimations;
    ImageFiles imageFiles;

    Camera camera;
};