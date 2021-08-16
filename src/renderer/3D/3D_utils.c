SparkRendererObject sparkCreateRendererObject3D(SparkRenderer* renderer, SparkGameObject* gameObject, SparkComponent* component) {
    SparkRendererObject rendererObject = {
        .gameObject = gameObject,
        .component = component,
        .indices = vector_create(),
        .vertices = vector_create()
    };

    return rendererObject;
}

void sparkUpdateRendererObject3D(SparkRenderer* renderer, SparkRendererObject* rendererObject) {
    int ww = renderer->ww;
    int wh = renderer->wh;
}