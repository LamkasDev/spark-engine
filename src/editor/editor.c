/**
 * Compiles shaders needed by the editor.
 * 
 * @param app a pointer to an app
 * 
 */
void sparkCompileEditorShaders(SparkApp* app) {
    
}

/**
 * Loads fonts needed by the editor.
 * 
 * @param app a pointer to an app
 * 
 */
void sparkLoadEditorFonts(SparkApp* app) {

}

/**
 * Loads textures needed by the editor.
 * 
 * @param app a pointer to an app
 * 
 */
void sparkLoadEditorTextures(SparkApp* app) {
    SparkTexture texture_0 = sparkCreateTexture("DVD");
    sparkLoadTexture(&texture_0, sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/textures/dvd.png")));
    hashmap_set(app->renderer.textures, &texture_0);
}

/**
 * Creates materials needed by the editor.
 * 
 * @param app a pointer to an app
 * 
 */
void sparkCreateEditorMaterials(SparkApp* app) {
    SparkShader* shader_0 = hashmap_get(app->renderer.shaders, &(SparkShader){ .name = "2DTexture" });
    SparkShader* shader_1 = hashmap_get(app->renderer.shaders, &(SparkShader){ .name = "2DColor" });

    SparkMaterial material_0 = sparkCreateMaterial("Color_0", shader_1);
    hashmap_set(material_0.data, &(SparkComponentData){ .key = "color", .data = sparkCreateStoreColor(&app->renderer.store, sparkCreateColorFromHex(0xffffff, 1.0f)) });
    hashmap_set(material_0.data, &(SparkComponentData){ .key = "shape", .data = sparkCreateStoreFloat(&app->renderer.store, RENDERER_SHAPE_QUAD) });
    hashmap_set(app->renderer.materials, &material_0);

    SparkMaterial material_1 = sparkCreateMaterial("Color_1", shader_1);
    hashmap_set(material_1.data, &(SparkComponentData){ .key = "color", .data = sparkCreateStoreColor(&app->renderer.store, sparkCreateColorFromHex(0x2b2b2b, 1.0f)) });
    hashmap_set(material_1.data, &(SparkComponentData){ .key = "shape", .data = sparkCreateStoreFloat(&app->renderer.store, RENDERER_SHAPE_QUAD) });
    hashmap_set(app->renderer.materials, &material_1);

    SparkMaterial material_2 = sparkCreateMaterial("Color_2", shader_1);
    hashmap_set(material_2.data, &(SparkComponentData){ .key = "color", .data = sparkCreateStoreColor(&app->renderer.store, sparkCreateColorFromHex(0x383838, 1.0f)) });
    hashmap_set(material_2.data, &(SparkComponentData){ .key = "shape", .data = sparkCreateStoreFloat(&app->renderer.store, RENDERER_SHAPE_QUAD) });
    hashmap_set(app->renderer.materials, &material_2);
}

/**
 * Creates the editor scene.
 * 
 * @param app a pointer to an app
 * 
 */
SparkScene sparkCreateEditorScene(SparkApp* app) {
    SparkScene scene = sparkCreateScene("Editor");
    sparkLoadSceneFromFile(&app->renderer, &scene, sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/scenes/editor.scene")));

    return scene;
}