/**
 * Creates a new renderer object based on the COMPONENT_TYPE_3D_RENDERER component.
 * 
 * @param renderer a pointer to a renderer
 * @param gameObject a pointer to a game object
 * @param component a pointer to a component
 * 
 */
SparkRendererObject sparkCreateRendererObject3D(SparkRenderer* renderer, SparkGameObject* gameObject, SparkComponent* component) {
    SparkRendererObject rendererObject = {
        .gameObject = gameObject,
        .component = component,
        .indices = vector_create(),
        .vertices = vector_create()
    };

    return rendererObject;
}

/**
 * Updates a 3D renderer object.
 * 
 * @param renderer a pointer to a renderer
 * @param rendererObject a pointer to a renderer object
 * 
 */
void sparkUpdateRendererObject3D(SparkRenderer* renderer, SparkRendererObject* rendererObject) {
    int ww = renderer->ww;
    int wh = renderer->wh;
}