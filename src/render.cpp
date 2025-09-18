float3 global_quadData[4] = {
    make_float3(-0.5f, -0.5f, 0), 
    make_float3(-0.5f, 0.5f, 0), 
    make_float3(0.5f, 0.5f, 0),
    make_float3(0.5f, -0.5f, 0),};

void pushRenderTexture(Renderer *renderer, TransformX T, Texture *texture) {
    RenderItem item = {};
    item.texture = texture;
    item.T = getModelToViewSpace_euler(T);
    item.type = RENDER_TEXTURE;
    if(renderer->commandsCount < arrayCount(renderer->renderCommands)) {
        renderer->renderCommands[renderer->commandsCount++] = item;
    } else {
        assert(false);
    }
}

void pushRenderView(Renderer *renderer, float16 T) {
    
    if(renderer->commandsCount < arrayCount(renderer->renderCommands)) {
        RenderItem item = {};
        item.type = RENDER_VIEW_MATRIX;
        item.T = T;
        renderer->renderCommands[renderer->commandsCount++] = item;
    } else {
        assert(false);
    }
}

