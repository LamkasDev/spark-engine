SparkGameObject sparkCreateGameObject() {
    SparkGameObject gameObject = {
        .pos = { 0, 0, 0 },
        .components = vector_create()
    };

    return gameObject;
}