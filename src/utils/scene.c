SparkScene sparkCreateScene(char* name) {
    SparkScene scene = {
        .name = name,
        .gameObjects = vector_create()
    };

    return scene;
}