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