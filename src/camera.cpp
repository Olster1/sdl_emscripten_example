struct Camera {
    TransformX T;
};

float16 makeWorldToCameraT(Camera *camera) {
    float16 T = getModelToViewSpaceWithoutScale(camera->T);
    return T;
}

void updateCamera(Camera *camera, float3 targetP) {
    camera->T.pos = lerp_float3(camera->T.pos, targetP, 0.4f);
}