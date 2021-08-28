/**
 * Creates shaders needed by the editor.
 * 
 * @param app a pointer to an app
 * 
 */
void sparkCreateEditorShaders(SparkApp* app) {
    int size;
    const unsigned char* shadersRaw = sparkReadFile(sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/editor/spark_objects/editor_shaders.sobj")), false, &size);
    sparkCreateShadersFromJSON(&app->renderer, shadersRaw);
}

/**
 * Creates fonts needed by the editor.
 * 
 * @param app a pointer to an app
 * 
 */
void sparkCreateEditorFonts(SparkApp* app) {
    int size;
    const unsigned char* fontsRaw = sparkReadFile(sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/editor/spark_objects/editor_fonts.sobj")), false, &size);
    sparkCreateFontsFromJSON(&app->renderer, fontsRaw);
}

/**
 * Creates textures needed by the editor.
 * 
 * @param app a pointer to an app
 * 
 */
void sparkCreateEditorTextures(SparkApp* app) {
    int size;
    const unsigned char* texturesRaw = sparkReadFile(sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/editor/spark_objects/editor_textures.sobj")), false, &size);
    sparkCreateTexturesFromJSON(&app->renderer, texturesRaw);
}

/**
 * Creates materials needed by the editor.
 * 
 * @param app a pointer to an app
 * 
 */
void sparkCreateEditorMaterials(SparkApp* app) {
    int size;
    const unsigned char* materialsRaw = sparkReadFile(sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/editor/spark_objects/editor_materials.sobj")), false, &size);
    sparkCreateMaterialsFromJSON(&app->renderer, materialsRaw);
}

/**
 * Creates the editor scene.
 * 
 * @param app a pointer to an app
 * 
 */
SparkScene sparkCreateEditorScene(SparkApp* app) {
    SparkScene scene = sparkCreateScene("Editor");
    sparkLoadSceneFromFile(&app->renderer, &scene, sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/editor/spark_objects/editor_scene.sobj")));

    return scene;
}