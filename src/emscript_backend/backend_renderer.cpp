void processRenderGroup(SDL_Renderer *sdlRenderer, Renderer *renderer, float2 viewPortSize) {
    float16 currentViewMatrix = float16_identity();
    for(int i = 0; i < renderer->commandsCount; ++i) {
        RenderItem *item = renderer->renderCommands + i;

        if(item->type == RENDER_TEXTURE) {
            SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
            float16 T = float16_multiply(currentViewMatrix, item->T);
            float4 points[4] = {};
            for(int i = 0; i < arrayCount(global_quadData); ++i) {
                float3 p = global_quadData[i];
                points[i] = float16_transform(T, make_float4(p.x, p.y, p.z, 1));
                points[i].x /= points[i].w;
                points[i].y /= points[i].w;
                points[i].z /= points[i].w;

                points[i].x = (0.5f*(points[i].x + 1.0f))*viewPortSize.x;
                points[i].y = (0.5f*(points[i].y + 1.0f))*viewPortSize.y;
            }

            SDL_Rect destRect = {};
            destRect.x = points[0].x;   
            destRect.y = points[0].y;    
            destRect.w = points[3].x - points[0].x;   
            destRect.h = points[1].y - points[0].y;  

            float4 uv = item->texture->uv;
            
            SDL_Rect srcRect = {};
            srcRect.x = uv.x * item->texture->width;
            srcRect.y = uv.y * item->texture->height;   
            srcRect.w = (uv.z - uv.x) * item->texture->width;
            srcRect.w = (uv.w - uv.y) * item->texture->height;

            assert(item->texture->handle.handle);
            SDL_RenderCopy(sdlRenderer, (SDL_Texture *)item->texture->handle.handle, &srcRect, &destRect);
        } else if(item->type == RENDER_VIEW_MATRIX) {
            currentViewMatrix = item->T;
        }

    }
    renderer->commandsCount = 0;
}