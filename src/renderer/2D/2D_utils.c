SparkRendererObject sparkCreateRendererObject2D(SparkRenderer* renderer, SparkGameObject* gameObject, SparkComponent* component) {
    SparkRendererObject rendererObject = {
        .gameObject = gameObject,
        .component = component,
        .indices = vector_create(),
        .vertices = vector_create()
    };

    return rendererObject;
}

void sparkUpdateRendererObject2D(SparkRenderer* renderer, SparkRendererObject* rendererObject) {
    int ww = renderer->ww;
    int wh = renderer->wh;

    SparkComponentData* materialData = hashmap_get(rendererObject->component->data, &(SparkComponentData){ .key = "material" });
    SparkMaterial* material = materialData->data;
    SparkComponentData* shapeData = hashmap_get(material->data, &(SparkComponentData){ .key = "shape" });
    int* shape = shapeData->data;

    SparkVector2* points = vector_create();
    switch(*shape) {
        case RENDERER_SHAPE_QUAD:
        case RENDERER_SHAPE_EMPTY_QUAD: {
            GLfloat xPos = (rendererObject->gameObject->pos.x / ww) * 2.0f;
            GLfloat yPos = (rendererObject->gameObject->pos.y / wh) * 2.0f;
            GLfloat xSize = (rendererObject->gameObject->scale.x / ww) * 2.0f;
            GLfloat ySize = (rendererObject->gameObject->scale.y / wh) * 2.0f;

            SparkComponentData* borderData = hashmap_get(rendererObject->component->data, &(SparkComponentData){ .key = "border" });
            if(borderData == NULL) {
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
            } else {
                GLfloat twicePi = 2.0f * GLM_PI;

                float* border = borderData->data;
                GLfloat xBorderRad = xSize * (*border);
                GLfloat yBorderRad = ySize * (*border);
                GLfloat x = 0.0f;
                GLfloat y = 0.0f;
                GLfloat xSize0 = rendererObject->gameObject->scale.x / ww;
                GLfloat ySize0 = rendererObject->gameObject->scale.y / wh;

                /* Point (Center) */
                SparkVector2 p0 = { .x = -1.0f + xPos + xSize0, .y = 1.0f - yPos - ySize0 };
                vector_add(&points, p0);
                
                /* Point (Bottom Center) */
                SparkVector2 p1 = { .x = -1.0f + xPos + xSize0, .y = 1.0f - yPos - ySize };
                vector_add(&points, p1);
                /* Border (Bottom Right) */
                x = -1.0f + xPos + xSize - xBorderRad;
                y = 1.0f - yPos - ySize + yBorderRad;
                for(int k = RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_0 * 3; k < RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1; k++) {
                    SparkVector2 p = { .x = x + (xBorderRad * cos(k * twicePi / RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1)), .y = y + (yBorderRad * sin(k * twicePi / RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1)) };
                    vector_add(&points, p);
                }
                SparkVector2 p1B = { .x = x + xBorderRad, .y = y };
                vector_add(&points, p1B);
                /* Point (Right Center) */
                SparkVector2 p2 = { .x = -1.0f + xPos + xSize, .y = 1.0f - yPos - ySize0 };
                vector_add(&points, p2);
                /* Border (Top Right) */
                x = -1.0f + xPos + xSize - xBorderRad;
                y = 1.0f - yPos - yBorderRad;
                for(int k = 0; k < RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_0; k++) {
                    SparkVector2 p = { .x = x + (xBorderRad * cos(k * twicePi / RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1)), .y = y + (yBorderRad * sin(k * twicePi / RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1)) };
                    vector_add(&points, p);
                }
                SparkVector2 p2B = { .x = x, .y = y + yBorderRad };
                vector_add(&points, p2B);
                /* Point (Top Center) */
                SparkVector2 p3 = { .x = -1.0f + xPos + xSize0, .y = 1.0f - yPos };
                vector_add(&points, p3);
                /* Border (Top Left) */
                x = -1.0f + xPos + xBorderRad;
                y = 1.0f - yPos - yBorderRad;
                for(int k = RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_0 * 1; k < RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_0 * 2; k++) {
                    SparkVector2 p = { .x = x + (xBorderRad * cos(k * twicePi / RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1)), .y = y + (yBorderRad * sin(k * twicePi / RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1)) };
                    vector_add(&points, p);
                }
                SparkVector2 p3B = { .x = x - xBorderRad, .y = y };
                vector_add(&points, p3B);
                /* Point (Left Center) */
                SparkVector2 p4 = { .x = -1.0f + xPos, .y = 1.0f - yPos - ySize0 };
                vector_add(&points, p4);
                /* Border (Bottom Left) */
                x = -1.0f + xPos + xBorderRad;
                y = 1.0f - yPos - ySize + yBorderRad;
                for(int k = RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_0 * 2; k < RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_0 * 3; k++) {
                    SparkVector2 p = { .x = x + (xBorderRad * cos(k * twicePi / RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1)), .y = y + (yBorderRad * sin(k * twicePi / RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1)) };
                    vector_add(&points, p);
                }
                SparkVector2 p4B = { .x = x, .y = y - yBorderRad };
                vector_add(&points, p4B);
            }
            break;
        }
    }

    GLfloat* vertices = vector_create();
    for(int k = 0; k < vector_size(points); k++) {
        SparkVector2* point = &points[k];
        vector_add(&vertices, point->x);
        vector_add(&vertices, point->y);
        vector_add(&vertices, 0.0f);

        switch(rendererObject->component->type) {
            case COMPONENT_TYPE_2D_RENDERER: {
                SparkComponentData* colorData = hashmap_get(material->data, &(SparkComponentData){ .key = "color" });
                SparkColor* color = colorData->data;
            
                /* Add colors */
                vector_add(&vertices, color->r);
                vector_add(&vertices, color->g);
                vector_add(&vertices, color->b);
                break;
            }

            case COMPONENT_TYPE_2D_TEXTURE_RENDERER: {
                /* Add texture coordinates */
                switch(k) {
                    case 0: {
                        vector_add(&vertices, 0.0f);
                        vector_add(&vertices, 1.0f);
                        break;
                    }

                    case 1: {
                        vector_add(&vertices, 1.0f);
                        vector_add(&vertices, 1.0f);
                        break;
                    }

                    case 2: {
                        vector_add(&vertices, 1.0f);
                        vector_add(&vertices, 0.0f);
                        break;
                    }

                    case 3: {
                        vector_add(&vertices, 0.0f);
                        vector_add(&vertices, 0.0f);
                        break;
                    }
                }
            }
        }
    }

    GLuint* indices = vector_create();
    switch(*shape) {
        case RENDERER_SHAPE_QUAD: {
            SparkComponentData* borderData = hashmap_get(rendererObject->component->data, &(SparkComponentData){ .key = "border" });
            if(borderData == NULL) {
                vector_add(&indices, 0);
                vector_add(&indices, 1);
                vector_add(&indices, 2);
                vector_add(&indices, 0);
                vector_add(&indices, 3);
                vector_add(&indices, 2);
            } else {
               for(int k = 0; k < RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1 + 7; k++) {
                    vector_add(&indices, 0);
                    vector_add(&indices, k + 1);
                    vector_add(&indices, k + 2);
                }
                vector_add(&indices, 0);
                vector_add(&indices, RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1 + 8);
                vector_add(&indices, 1);
            }

            rendererObject->drawType = GL_TRIANGLES;
            break;
        }

        case RENDERER_SHAPE_EMPTY_QUAD: {
            vector_add(&indices, 0);
            vector_add(&indices, 1);
            vector_add(&indices, 2);
            vector_add(&indices, 3);
            vector_add(&indices, 0);

            rendererObject->drawType = GL_LINE_LOOP;
            break;
        }
    }

    vector_free(points);
    vector_free(rendererObject->vertices);
    vector_free(rendererObject->indices);

    rendererObject->vertices = vertices;
    rendererObject->indices = indices;
}