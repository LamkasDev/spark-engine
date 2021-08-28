/**
 * Creates SparkShaders based on a JSON string.
 * 
 * @param app a pointer to an app
 * @param json source of the shaders
 * 
 */
void sparkCreateShadersFromJSON(void* _app, const unsigned char* json) {
    SparkApp* app = (SparkApp*)_app;
    cJSON* tree = cJSON_Parse(json);
    if(tree == NULL) {
        printf("Error parsing JSON: %s\n", cJSON_GetErrorPtr());
        return;
    }
    if(strcmp(cJSON_GetObjectItemCaseSensitive(tree, "type")->valuestring, "shaders") != 0) {
        printf("Error: JSON is not a descriptor of shaders\n");
        return;
    }

    cJSON* shadersData = cJSON_GetObjectItemCaseSensitive(tree, "shaders");
    cJSON* shaderData = NULL;
    cJSON_ArrayForEach(shaderData, shadersData) {
        char* shaderUUID = cJSON_GetObjectItemCaseSensitive(shaderData, "uuid")->valuestring;
        char* name = cJSON_GetObjectItemCaseSensitive(shaderData, "name")->valuestring;
        char* vertexPath = cJSON_GetObjectItemCaseSensitive(shaderData, "vertexPath")->valuestring;
        char* fragmentPath = cJSON_GetObjectItemCaseSensitive(shaderData, "fragmentPath")->valuestring;

        SparkShader shader = sparkCompileShader(&app->renderer, name, sparkCombinePaths(app->assetsPath, sparkCreatePathFromString(vertexPath)), sparkCombinePaths(app->assetsPath, sparkCreatePathFromString(fragmentPath)));
        hashmap_set(app->renderer.shaders, &shader);
    }

    /* TODO: delete the JSON tree, after implementing a system where char* pointers are transfered somewhere else */
    /* - can't use SparkStore for this, because hashmap functions don't know about SparkStore at all */
    //cJSON_Delete(tree);
}

/**
 * Creates SparkFonts based on a JSON string.
 * 
 * @param app a pointer to an app
 * @param json source of the fonts
 * 
 */
void sparkCreateFontsFromJSON(void* _app, const unsigned char* json) {
    SparkApp* app = (SparkApp*)_app;
    cJSON* tree = cJSON_Parse(json);
    if(tree == NULL) {
        printf("Error parsing JSON: %s\n", cJSON_GetErrorPtr());
        return;
    }
    if(strcmp(cJSON_GetObjectItemCaseSensitive(tree, "type")->valuestring, "fonts") != 0) {
        printf("Error: JSON is not a descriptor of fonts\n");
        return;
    }

    cJSON* fontsData = cJSON_GetObjectItemCaseSensitive(tree, "fonts");
    cJSON* fontData = NULL;
    cJSON_ArrayForEach(fontData, fontsData) {
        char* fontUUID = cJSON_GetObjectItemCaseSensitive(fontData, "uuid")->valuestring;
        char* name = cJSON_GetObjectItemCaseSensitive(fontData, "name")->valuestring;
        char* path = cJSON_GetObjectItemCaseSensitive(fontData, "path")->valuestring;

        SparkFont font = sparkCreateFont("Arial");
        sparkLoadFont(&app->renderer.ft, &font, sparkCombinePaths(app->assetsPath, sparkCreatePathFromString(path)));

        hashmap_set(app->renderer.fonts, &font);
    }

    //cJSON_Delete(tree);
}

/**
 * Creates SparkTextures based on a JSON string.
 * 
 * @param app a pointer to an app
 * @param json source of the fonts
 * 
 */
void sparkCreateTexturesFromJSON(void* _app, const unsigned char* json) {
    SparkApp* app = (SparkApp*)_app;
    cJSON* tree = cJSON_Parse(json);
    if(tree == NULL) {
        printf("Error parsing JSON: %s\n", cJSON_GetErrorPtr());
        return;
    }
    if(strcmp(cJSON_GetObjectItemCaseSensitive(tree, "type")->valuestring, "textures") != 0) {
        printf("Error: JSON is not a descriptor of textures\n");
        return;
    }

    cJSON* texturesData = cJSON_GetObjectItemCaseSensitive(tree, "textures");
    cJSON* textureData = NULL;
    cJSON_ArrayForEach(textureData, texturesData) {
        
    }
    
    //cJSON_Delete(tree);
}

/**
 * Creates SparkMaterials based on a JSON string.
 * 
 * @param app a pointer to an app
 * @param json source of the materials
 * 
 */
void sparkCreateMaterialsFromJSON(void* _app, const unsigned char* json) {
    SparkApp* app = (SparkApp*)_app;
    cJSON* tree = cJSON_Parse(json);
    if(tree == NULL) {
        printf("Error parsing JSON: %s\n", cJSON_GetErrorPtr());
        return;
    }
    if(strcmp(cJSON_GetObjectItemCaseSensitive(tree, "type")->valuestring, "materials") != 0) {
        printf("Error: JSON is not a descriptor of materials\n");
        return;
    }

    cJSON* materialsData = cJSON_GetObjectItemCaseSensitive(tree, "materials");
    cJSON* materialData = NULL;
    cJSON_ArrayForEach(materialData, materialsData) {
        char* materialUUID = cJSON_GetObjectItemCaseSensitive(materialData, "uuid")->valuestring;
        char* name = cJSON_GetObjectItemCaseSensitive(materialData, "name")->valuestring;
        SparkShader* shader = sparkCreateComponentDataValueFromJSON(app, NULL, cJSON_GetObjectItemCaseSensitive(materialData, "shader"));

        SparkMaterial material = sparkCreateMaterial(name, shader);

        cJSON* materialsDataData = cJSON_GetObjectItemCaseSensitive(materialData, "data");
        cJSON* materialDataData = NULL;
        cJSON_ArrayForEach(materialDataData, materialsDataData) {
            SparkComponentData materialDataItem = sparkCreateComponentDataFromJSON(app, materialDataData);
            hashmap_set(material.data, &materialDataItem);
        }

        hashmap_set(app->renderer.materials, &material);
    }
    
    //cJSON_Delete(tree);
}

/**
 * Loads SparkScene based on a JSON string.
 * 
 * @param app a pointer to an app
 * @param scene a pointer to a scene
 * @param json source of the scene
 * 
 */
void sparkLoadSceneFromJSON(void* _app, SparkScene* scene, const unsigned char* json) {
    SparkApp* app = (SparkApp*)_app;
    scene->gameObjects = vector_create();

    cJSON* tree = cJSON_Parse(json);
    if(tree == NULL) {
        printf("Error parsing JSON: %s\n", cJSON_GetErrorPtr());
        return;
    }
    if(strcmp(cJSON_GetObjectItemCaseSensitive(tree, "type")->valuestring, "scene") != 0) {
        printf("Error: JSON is not a scene\n");
        return;
    }

    cJSON* gameObjectsData = cJSON_GetObjectItemCaseSensitive(tree, "gameObjects");
    cJSON* gameObjectData = NULL;
    cJSON_ArrayForEach(gameObjectData, gameObjectsData) {
        char* gameObjectUUID = cJSON_GetObjectItemCaseSensitive(gameObjectData, "uuid")->valuestring;

        SparkGameObject gameObject = sparkCreateGameObject();

        cJSON* pos = cJSON_GetObjectItemCaseSensitive(gameObjectData, "pos");
        float posX = cJSON_GetArrayItem(pos, 0)->valuedouble;
        float posY = cJSON_GetArrayItem(pos, 1)->valuedouble;
        float posZ = cJSON_GetArrayItem(pos, 2)->valuedouble;
        gameObject.pos = (SparkVector3){ .x = posX, .y = posY, .z = posZ };

        cJSON* scale = cJSON_GetObjectItemCaseSensitive(gameObjectData, "scale");
        float scaleX = cJSON_GetArrayItem(scale, 0)->valuedouble;
        float scaleY = cJSON_GetArrayItem(scale, 1)->valuedouble;
        float scaleZ = cJSON_GetArrayItem(scale, 2)->valuedouble;
        gameObject.scale = (SparkVector3){ .x = scaleX, .y = scaleY, .z = scaleZ };

        cJSON* componentsData = cJSON_GetObjectItemCaseSensitive(gameObjectData, "components");
        cJSON* componentData = NULL;
        cJSON_ArrayForEach(componentData, componentsData) {
            char* componentUUID = cJSON_GetObjectItemCaseSensitive(componentData, "uuid")->valuestring;
            int componentType = cJSON_GetObjectItemCaseSensitive(componentData, "type")->valueint;

            SparkComponent* component = sparkCreateComponent(&gameObject, componentType);

            cJSON* componentsDataData = cJSON_GetObjectItemCaseSensitive(componentData, "data");
            cJSON* componentDataData = NULL;
            cJSON_ArrayForEach(componentDataData, componentsDataData) {
                SparkComponentData componentDataItem = sparkCreateComponentDataFromJSON(app, componentDataData);
                hashmap_set(component->data, &componentDataItem);
            }
        }

        vector_add(&scene->gameObjects, gameObject);
    }

    //cJSON_Delete(tree);
}

/**
 * Creates SparkComponentData from cJSON data node.
 * 
 * @param app a pointer to an app
 * @param data cJSON data node
 * 
 */
SparkComponentData sparkCreateComponentDataFromJSON(void* _app, cJSON* data) {
    SparkApp* app = (SparkApp*)_app;
    char* componentDataKey = cJSON_GetObjectItemCaseSensitive(data, "key")->valuestring;
    cJSON* componentDataData = cJSON_GetObjectItemCaseSensitive(data, "data");
    SparkComponentData componentData = {
        .key = componentDataKey,
        .data = sparkCreateComponentDataValueFromJSON(app, componentDataKey, componentDataData)
    };

    return componentData;
}

/**
 * Creates a SparkComponentData value from cJSON data node.
 * 
 * @param app a pointer to an app
 * @param data cJSON data node
 * 
 */
void* sparkCreateComponentDataValueFromJSON(void* _app, char* key, cJSON* data) {
    SparkApp* app = (SparkApp*)_app;
    switch(data->type) {
        case cJSON_Number: {
            return sparkCreateStoreFloat(&app->renderer.store, data->valuedouble);
        }

        case cJSON_False:
        case cJSON_True: {
            return sparkCreateStoreInteger(&app->renderer.store, data->type == cJSON_True);
        }

        case cJSON_String: {
            char* validReferencePrefixes[4] = { "&SparkShader@", "&SparkTexture@", "&SparkMaterial@", "&SparkFont@" };
            for(int i = 0; i < (sizeof(validReferencePrefixes) / sizeof(char*)); i++) {
                if(sparkStringStartsWith(data->valuestring, validReferencePrefixes[i])) {
                    char* valueReferenceName = sparkStringReplace(data->valuestring, validReferencePrefixes[i], "");
                    switch(i) {
                        case 0: {
                            return hashmap_get(app->renderer.shaders, &(SparkShader){ .name = valueReferenceName });
                        }

                        case 1: {
                            return hashmap_get(app->renderer.fonts, &(SparkTexture){ .name = valueReferenceName });
                        }

                        case 2: {
                            return hashmap_get(app->renderer.materials, &(SparkMaterial){ .name = valueReferenceName });
                        }

                        case 3: {
                            return hashmap_get(app->renderer.fonts, &(SparkFont){ .name = valueReferenceName });
                        }
                    }
                }
            }

            return sparkCreateStoreString(&app->renderer.store, data->valuestring);
        }

        case cJSON_Array: {
            char* validArrayedObjects[1] = { "color" };
            for(int i = 0; i < (sizeof(validArrayedObjects) / sizeof(char*)); i++) {
                if(strcmp(validArrayedObjects[i], key) == 0) {
                    switch(i) {
                        case 0: {
                            return sparkCreateStoreColor(&app->renderer.store, (SparkColor){ .r = cJSON_GetArrayItem(data, 0)->valuedouble / 255.0f, .g = cJSON_GetArrayItem(data, 1)->valuedouble / 255.0f, .b = cJSON_GetArrayItem(data, 2)->valuedouble / 255.0f, .a = 1.0f });
                        }
                    }
                }
            }
        }

        default: {
            return NULL;
        }
    }
}