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
    hashmap_set(material_0.data, &(SparkComponentData){ .key = "shape", .data = sparkCreateStoreInteger(&app->renderer.store, RENDERER_SHAPE_QUAD) });
    hashmap_set(app->renderer.materials, &material_0);

    SparkMaterial material_1 = sparkCreateMaterial("Color_1", shader_1);
    hashmap_set(material_1.data, &(SparkComponentData){ .key = "color", .data = sparkCreateStoreColor(&app->renderer.store, sparkCreateColorFromHex(0x2b2b2b, 1.0f)) });
    hashmap_set(material_1.data, &(SparkComponentData){ .key = "shape", .data = sparkCreateStoreInteger(&app->renderer.store, RENDERER_SHAPE_QUAD) });
    hashmap_set(app->renderer.materials, &material_1);

    SparkMaterial material_2 = sparkCreateMaterial("Color_2", shader_1);
    hashmap_set(material_2.data, &(SparkComponentData){ .key = "color", .data = sparkCreateStoreColor(&app->renderer.store, sparkCreateColorFromHex(0x383838, 1.0f)) });
    hashmap_set(material_2.data, &(SparkComponentData){ .key = "shape", .data = sparkCreateStoreInteger(&app->renderer.store, RENDERER_SHAPE_QUAD) });
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
    SparkFont* font_0 = hashmap_get(app->renderer.fonts, &(SparkFont){ .name = "Arial" });
    SparkMaterial* material_0 = hashmap_get(app->renderer.materials, &(SparkMaterial){ .name = "Text" });
    SparkMaterial* material_1 = hashmap_get(app->renderer.materials, &(SparkMaterial){ .name = "Color_1" });
    SparkMaterial* material_2 = hashmap_get(app->renderer.materials, &(SparkMaterial){ .name = "Color_2" });

    SparkGameObject gameObjectBG = sparkCreateGameObject();
    SparkComponent* componentBG = sparkCreateComponent(&gameObjectBG, COMPONENT_TYPE_2D_RENDERER);
    gameObjectBG.pos = (SparkVector3){ .x = 0.0f, .y = 0.0f, .z = 0.0f };
    gameObjectBG.scale = (SparkVector3){ .x = -1, .y = -1, .z = 0.0f };
    hashmap_set(componentBG->data, &(SparkComponentData){ .key = "material", .data = material_2 });
    vector_add(&scene.gameObjects, gameObjectBG);

    SparkGameObject gameObjectPanel0 = sparkCreateGameObject();
    SparkComponent* componentPanel0 = sparkCreateComponent(&gameObjectPanel0, COMPONENT_TYPE_2D_RENDERER);
    gameObjectPanel0.pos = (SparkVector3){ .x = 0.0f, .y = 0.0f, .z = 0.0f };
    gameObjectPanel0.scale = (SparkVector3){ .x = 180.0f, .y = -1, .z = 0.0f };
    hashmap_set(componentPanel0->data, &(SparkComponentData){ .key = "material", .data = material_1 });
    vector_add(&scene.gameObjects, gameObjectPanel0);

    SparkGameObject gameObjectPanel0Title = sparkCreateGameObject();
    SparkComponent* componentPanel0Title = sparkCreateComponent(&gameObjectPanel0Title, COMPONENT_TYPE_TEXT_RENDERER);
    gameObjectPanel0Title.pos = (SparkVector3){ .x = 10.0f, .y = 10.0f, .z = 0.0f };
    gameObjectPanel0Title.scale = (SparkVector3){ .x = 160.0f, .y = 30.0f, .z = 0.0f };
    hashmap_set(componentPanel0Title->data, &(SparkComponentData){ .key = "text", .data = sparkCreateStoreString(&app->renderer.store, "Spark") });
    hashmap_set(componentPanel0Title->data, &(SparkComponentData){ .key = "font", .data = font_0 });
    hashmap_set(componentPanel0Title->data, &(SparkComponentData){ .key = "fontSize", .data = sparkCreateStoreInteger(&app->renderer.store, 24) });
    hashmap_set(componentPanel0Title->data, &(SparkComponentData){ .key = "material", .data = material_0 });
    vector_add(&scene.gameObjects, gameObjectPanel0Title);

    return scene;
}