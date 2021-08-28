/**
 * Creates a new renderer object based on the COMPONENT_TYPE_TEXT_RENDERER component.
 * 
 * @param renderer a pointer to a renderer
 * @param gameObject a pointer to a game object
 * @param component a pointer to a component
 * 
 */
SparkRendererObject sparkCreateRendererObjectText(SparkRenderer* renderer, SparkGameObject* gameObject, SparkComponent* component) {
    SparkRendererObject rendererObject = {
        .gameObject = gameObject,
        .component = component,
        .indices = vector_create(),
        .vertices = vector_create()
    };

    return rendererObject;
}

/**
 * Updates a text renderer object.
 * 
 * @param renderer a pointer to a renderer
 * @param rendererObject a pointer to a renderer object
 * @param i index in a renderer object group
 * 
 */
void sparkUpdateRendererObjectText(SparkRenderer* renderer, SparkRendererObject* rendererObject, int i) {
    int ww = renderer->ww;
    int wh = renderer->wh;

    SparkComponentData* textData = hashmap_get(rendererObject->component->data, &(SparkComponentData){ .key = "text" });
    char* text = renderer->store.strings[(uintptr_t)textData->data];
    SparkComponentData* fontData = hashmap_get(rendererObject->component->data, &(SparkComponentData){ .key = "font" });
    SparkFont* font = fontData->data;
    SparkComponentData* fontSizeData = hashmap_get(rendererObject->component->data, &(SparkComponentData){ .key = "fontSize" });
    int fontSize = renderer->store.floats[(uintptr_t)fontSizeData->data];
    GLfloat fontScale = fontSize / 48.0f;

    SparkCharacter* currentCharacter = hashmap_get(font->characters, &(SparkCharacter){ .c = text[i] });
    GLfloat currentCharacterW = currentCharacter->size.x * fontScale;
    GLfloat currentCharacterH = currentCharacter->size.y * fontScale;

    GLfloat xOffset = 0.0f;
    GLfloat yOffset = 0.0f;
    for(int k = 0; k < i; k++) {
        SparkCharacter* character = hashmap_get(font->characters, &(SparkCharacter){ .c = text[k] });
        xOffset += (character->advance >> 6) * fontScale;
    }

    SparkVector2* points = vector_create();
    GLfloat xPos = ((rendererObject->gameObject->pos.x + (currentCharacter->bearing.x * fontScale) + xOffset) / ww) * 2.0f;
    GLfloat yPos = ((rendererObject->gameObject->pos.y + (rendererObject->gameObject->scale.y - (currentCharacter->bearing.y * fontScale)) + yOffset) / wh) * 2.0f;
    GLfloat xSize = (currentCharacterW / ww) * 2.0f;
    GLfloat ySize = (currentCharacterH / wh) * 2.0f;

    /* Point (Top Left) */
    SparkVector2 p1 = { .x = -1.0f + xPos, .y = 1.0f - yPos };
    vector_add(&points, p1);
    /* Point (Top Right) */
    SparkVector2 p2 = { .x = -1.0f + xPos + xSize, .y = 1.0f - yPos };
    vector_add(&points, p2);
    /* Point (Bottom Right) */
    SparkVector2 p3 = { .x = -1.0f + xPos + xSize, .y = 1.0f - yPos - ySize };
    vector_add(&points, p3);
    /* Point (Bottom Left) */
    SparkVector2 p4 = { .x = -1.0f + xPos, .y = 1.0f - yPos - ySize };
    vector_add(&points, p4);

    GLfloat* vertices = vector_create();
    for(int k = 0; k < vector_size(points); k++) {
        SparkVector2* point = &points[k];
        vector_add(&vertices, point->x);
        vector_add(&vertices, point->y);
        vector_add(&vertices, 0.0f);

        switch(k) {
            case 0: {
                vector_add(&vertices, 0.0f);
                vector_add(&vertices, 0.0f);
                break;
            }

            case 1: {
                vector_add(&vertices, 1.0f);
                vector_add(&vertices, 0.0f);
                break;
            }

            case 2: {
                vector_add(&vertices, 1.0f);
                vector_add(&vertices, 1.0f);
                break;
            }

            case 3: {
                vector_add(&vertices, 0.0f);
                vector_add(&vertices, 1.0f);
                break;
            }
        }
    }

    GLuint* indices = vector_create();
    vector_add(&indices, 0);
    vector_add(&indices, 1);
    vector_add(&indices, 2);
    vector_add(&indices, 0);
    vector_add(&indices, 3);
    vector_add(&indices, 2);

    vector_free(points);
    vector_free(rendererObject->vertices);
    vector_free(rendererObject->indices);

    rendererObject->vertices = vertices;
    rendererObject->indices = indices;
    rendererObject->drawType = GL_TRIANGLES;
}