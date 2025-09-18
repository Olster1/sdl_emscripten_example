struct TextureHandle {
    #ifdef SDL_BUILD
    void *handle;
    #endif
};

struct Texture {
    int width;
    int height;

    float4 uv;

    TextureHandle handle;
};

enum RenderItemType {
    RENDER_TEXTURE,
    RENDER_VIEW_MATRIX,
};

struct RenderItem {
    RenderItemType type;
    Texture *texture;
    float16 T;
};

struct Renderer {
    int commandsCount;
    RenderItem renderCommands[64];
};