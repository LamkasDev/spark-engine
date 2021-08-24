/**
 * Creates a new game object.
 */
SparkGameObject sparkCreateGameObject() {
    SparkGameObject gameObject = {
        .pos = { 0, 0, 0 },
        .scale = { 1, 1, 1 },
        .components = vector_create()
    };

    return gameObject;
}