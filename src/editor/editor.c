void sparkCompileEditorShaders(SparkApp* app) {
    
}

void sparkLoadEditorFonts(SparkApp* app) {

}

void sparkLoadEditorTextures(SparkApp* app) {
    SparkTexture texture_0 = sparkCreateTexture("DVD");
    sparkLoadTexture(&texture_0, sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/textures/dvd.png")));
    hashmap_set(app->renderer.textures, &texture_0);
}

void sparkCreateEditorMaterials(SparkApp* app) {
    int shape = RENDERER_SHAPE_QUAD;
    SparkShader* shader_0 = hashmap_get(app->renderer.shaders, &(SparkShader){ .name = "2DTexture" });
    SparkShader* shader_1 = hashmap_get(app->renderer.shaders, &(SparkShader){ .name = "2DColor" });
    SparkTexture* texture_0 = hashmap_get(app->renderer.textures, &(SparkTexture){ .name = "DVD" });

    SparkMaterial material_0 = sparkCreateMaterial("DVD", shader_0);
    hashmap_set(material_0.data, &(SparkComponentData){ .key = "texture", .data = texture_0 });
    hashmap_set(material_0.data, &(SparkComponentData){ .key = "shape", .data = &shape });
    hashmap_set(app->renderer.materials, &material_0);

    SparkMaterial material_1 = sparkCreateMaterial("Color", shader_1);
    hashmap_set(material_1.data, &(SparkComponentData){ .key = "color", .data = &(SparkColor){ .r=1.0f, .g=1.0f, .b=1.0f, .a=1.0f } });
    hashmap_set(material_1.data, &(SparkComponentData){ .key = "shape", .data = &shape });
    hashmap_set(app->renderer.materials, &material_1);
}

SparkScene sparkCreateEditorScene(SparkApp* app) {
    SparkScene scene = sparkCreateScene("Editor");
    SparkFont* font_0 = hashmap_get(app->renderer.fonts, &(SparkFont){ .name = "Arial" });
    SparkMaterial* material_0 = hashmap_get(app->renderer.materials, &(SparkMaterial){ .name = "DVD" });
    SparkMaterial* material_1 = hashmap_get(app->renderer.materials, &(SparkMaterial){ .name = "Text" });
    SparkMaterial* material_2 = hashmap_get(app->renderer.materials, &(SparkMaterial){ .name = "Color" });

    SparkGameObject gameObject_0 = sparkCreateGameObject();
    SparkComponent* component_0 = sparkCreateComponent(&gameObject_0, COMPONENT_TYPE_2D_TEXTURE_RENDERER);
    gameObject_0.pos = (SparkVector3){ .x = 0.0f, .y = 0.0f, .z = 0.0f };
    gameObject_0.scale = (SparkVector3){ .x = 180.0f, .y = 180.0f, .z = 0.0f };
    hashmap_set(component_0->data, &(SparkComponentData){ .key = "material", .data = material_0 });
    vector_add(&scene.gameObjects, gameObject_0);

    SparkGameObject gameObject_1 = sparkCreateGameObject();
    SparkComponent* component_1 = sparkCreateComponent(&gameObject_1, COMPONENT_TYPE_TEXT_RENDERER);
    gameObject_1.pos = (SparkVector3){ .x = 0.0f, .y = 0.0f, .z = 0.0f };
    gameObject_1.scale = (SparkVector3){ .x = 350.0f, .y = 50.0f, .z = 0.0f };
    hashmap_set(component_1->data, &(SparkComponentData){ .key = "text", .data = "owo" });
    hashmap_set(component_1->data, &(SparkComponentData){ .key = "font", .data = font_0 });
    hashmap_set(component_1->data, &(SparkComponentData){ .key = "material", .data = material_1 });
    vector_add(&scene.gameObjects, gameObject_1);

    SparkGameObject gameObject_2 = sparkCreateGameObject();
    SparkComponent* component_2 = sparkCreateComponent(&gameObject_2, COMPONENT_TYPE_2D_RENDERER);
    gameObject_2.pos = (SparkVector3){ .x = 100.0f, .y = 100.0f, .z = 0.0f };
    gameObject_2.scale = (SparkVector3){ .x = 180.0f, .y = 180.0f, .z = 0.0f };
    hashmap_set(component_2->data, &(SparkComponentData){ .key = "material", .data = material_2 });
    vector_add(&scene.gameObjects, gameObject_2);

    return scene;
}