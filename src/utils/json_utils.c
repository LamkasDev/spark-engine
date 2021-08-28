/**
 * Loads a scene from a JSON string.
 * 
 * @param renderer a pointer to a renderer
 * @param scene a pointer to a scene
 * @param json source of the scene
 * 
 */
void sparkLoadSceneFromJSON(SparkRenderer* renderer, SparkScene* scene, const unsigned char* json) {
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
        SparkGameObject gameObject = sparkCreateGameObject();

        char* gameObjectUUID = cJSON_GetObjectItemCaseSensitive(gameObjectData, "uuid")->valuestring;

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
                char* componentDataKey = cJSON_GetObjectItemCaseSensitive(componentDataData, "key")->valuestring;
                cJSON *componentDataValue = cJSON_GetObjectItemCaseSensitive(componentDataData, "value");

                switch(componentDataValue->type) {
                    case cJSON_Number: {
                        float value = componentDataValue->valuedouble;
                        hashmap_set(component->data, &(SparkComponentData){ .key = componentDataKey, .data = sparkCreateStoreFloat(&renderer->store, value) });
                        break;
                    }

                    case cJSON_String: {
                        bool isReference = false;
                        char* validReferencePrefixes[4] = { "&SparkShader@", "&SparkTexture@", "&SparkMaterial@", "&SparkFont@" };
                        for(int i = 0; i < (sizeof(validReferencePrefixes) / sizeof(char*)); i++) {
                            if(sparkStringStartsWith(componentDataValue->valuestring, validReferencePrefixes[i])) {
                                char* valueReferenceName = sparkStringReplace(componentDataValue->valuestring, validReferencePrefixes[i], "");
                                switch(i) {
                                    case 0: {
                                        SparkShader* valueReference = hashmap_get(renderer->shaders, &(SparkShader){ .name = valueReferenceName });
                                        hashmap_set(component->data, &(SparkComponentData){ .key = componentDataKey, .data = valueReference });
                                        break;
                                    }

                                    case 1: {
                                        SparkTexture* valueReference = hashmap_get(renderer->fonts, &(SparkTexture){ .name = valueReferenceName });
                                        hashmap_set(component->data, &(SparkComponentData){ .key = componentDataKey, .data = valueReference });
                                        break;
                                    }

                                    case 2: {
                                        SparkMaterial* valueReference = hashmap_get(renderer->materials, &(SparkMaterial){ .name = valueReferenceName });
                                        hashmap_set(component->data, &(SparkComponentData){ .key = componentDataKey, .data = valueReference });
                                        break;
                                    }

                                    case 3: {
                                        SparkFont* valueReference = hashmap_get(renderer->fonts, &(SparkFont){ .name = valueReferenceName });
                                        hashmap_set(component->data, &(SparkComponentData){ .key = componentDataKey, .data = valueReference });
                                        break;
                                    }
                                }

                                isReference = true;
                            }
                        }

                        if(!isReference) {
                            hashmap_set(component->data, &(SparkComponentData){ .key = componentDataKey, .data = sparkCreateStoreString(&renderer->store, componentDataValue->valuestring) });
                        }
                        break;
                    }
                }
            }
        }

        vector_add(&scene->gameObjects, gameObject);
    }

    /* TODO: delete the JSON tree, after implementing a system where char* pointers are transfered somewhere else */
    /* - can't use SparkStore for this, because hashmap functions don't know about SparkStore at all */
    //cJSON_Delete(tree);
}