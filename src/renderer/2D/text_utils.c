SparkRendererObject sparkCreateRendererObjectText(SparkRenderer* renderer, SparkGameObject* gameObject, SparkComponent* component) {
    SparkRendererObject rendererObject = {
        .gameObject = gameObject,
        .component = component,
        .indices = vector_create(),
        .vertices = vector_create()
    };

    return rendererObject;
}

void sparkUpdateRendererObjectText(SparkRenderer* renderer, SparkRendererObject* rendererObject, int i) {
    int ww = renderer->ww;
    int wh = renderer->wh;

    SparkComponentData* textData = hashmap_get(rendererObject->component->data, &(SparkComponentData){ .key = "text" });
    char* text = textData->data;
    SparkComponentData* fontData = hashmap_get(rendererObject->component->data, &(SparkComponentData){ .key = "font" });
    SparkFont* font = fontData->data;
    SparkCharacter* currentCharacter = hashmap_get(font->characters, &(SparkCharacter){ .c = text[i] });

    GLfloat xOffset = 0.0f;
    GLfloat yOffset = 0.0f;
    for(int k = 0; k < i; k++) {
        SparkCharacter* character = hashmap_get(font->characters, &(SparkCharacter){ .c = text[k] });
        xOffset += character->advance >> 6;
    }

    SparkVector2* points = vector_create();
    GLfloat xPos = ((rendererObject->gameObject->pos.x + currentCharacter->bearing.x + xOffset) / ww) * 2.0f;
    GLfloat yPos = ((rendererObject->gameObject->pos.y - currentCharacter->bearing.y - yOffset) / wh) * 2.0f;
    GLfloat xSize = (currentCharacter->size.x / ww) * 2.0f;
    GLfloat ySize = (currentCharacter->size.y / wh) * 2.0f;

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