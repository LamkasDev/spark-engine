/**
 * Creates a new scene.
 * 
 * @param name name of the scene
 * 
 */
SparkScene sparkCreateScene(char* name) {
    char* uuid = sparkGenerateUUID();
    SparkScene scene = {
        .uuid = *uuid,
        .name = name,
        .gameObjects = vector_create()
    };

    return scene;
}

/**
 * Loads a scene from a file.
 * 
 * @param _renderer a pointer to a renderer
 * @param scene a pointer to a scene
 * @param path path to the scene file
 * 
 */
void sparkLoadSceneFromFile(void* _renderer, SparkScene* scene, char* path) {
    SparkRenderer* renderer = (SparkRenderer*)_renderer;

    int size;
    const unsigned char* sceneRaw = sparkReadFile(path, false, &size);
    sparkLoadSceneFromJSON(renderer, scene, sceneRaw);
}