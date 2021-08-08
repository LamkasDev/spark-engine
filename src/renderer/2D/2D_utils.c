SparkRendererObject sparkCreateRendererObject2D(SparkRenderer* renderer, SparkGameObject* gameObject, SparkComponent* component) {
    int ww = renderer->ww;
    int wh = renderer->wh;

    SparkComponentData* shapeData = hashmap_get(component->data, &(SparkComponentData){ .key = "shape" });
    int* shape = shapeData->data;
    SparkComponentData* sizeData = hashmap_get(component->data, &(SparkComponentData){ .key = "size" });
    SparkVector2* size = sizeData->data;

    SparkRendererObject rendererObject;
    SparkVector2* points = vector_create();
    switch(*shape) {
        case RENDERER_SHAPE_QUAD:
        case RENDERER_SHAPE_EMPTY_QUAD: {
            /* Point (Top Left) */
            SparkVector2 p1 = { .x = -1.0f + ((gameObject->pos.x / ww) * 2.0f), .y = 1.0f - ((gameObject->pos.y / wh) * 2.0f) };
            vector_add(&points, p1);
            /* Point (Top Right) */
            SparkVector2 p2 = { .x = -1.0f + ((gameObject->pos.x / ww) * 2.0f) + ((size->x / ww) * 2.0f), .y = 1.0f - ((gameObject->pos.y / wh) * 2.0f) };
            vector_add(&points, p2);
            /* Point (Bottom Right) */
            SparkVector2 p3 = { .x = -1.0f + ((gameObject->pos.x / ww) * 2.0f) + ((size->x / ww) * 2.0f), .y = 1.0f - ((gameObject->pos.y / wh) * 2.0f) - ((size->y / wh) * 2.0f) };
            vector_add(&points, p3);
            /* Point (Bottom Left) */
            SparkVector2 p4 = { .x = -1.0f + ((gameObject->pos.x / ww) * 2.0f), .y = 1.0f - ((gameObject->pos.y / wh) * 2.0f) - ((size->y / wh) * 2.0f) };
            vector_add(&points, p4);
            break;
        }

        case RENDERER_SHAPE_CIRCLE:
        case RENDERER_SHAPE_EMPTY_CIRCLE: {
            GLfloat twicePi = 2.0f * GLM_PI;
            
            /* Point (Center) */
            GLfloat xRad = (((size->y / ww) * 2.0f) / 2.0f);
            GLfloat yRad = (((size->y / wh) * 2.0f) / 2.0f);
            GLfloat x = -1.0f + ((gameObject->pos.x / ww) * 2.0f) + xRad;
            GLfloat y = 1.0f - ((gameObject->pos.y / wh) * 2.0f) - yRad;
            if(*shape == RENDERER_SHAPE_CIRCLE) {
                SparkVector2 p1 = { .x = x, .y = y };
                vector_add(&points, p1);
            }

            for(int k = 0; k < RENDERER_CIRCLE_TRIANGLE_AMMOUNT; k++) {
                /* Point */
                SparkVector2 p2 = { .x = x + (xRad * cos(k *  twicePi / RENDERER_CIRCLE_TRIANGLE_AMMOUNT)), .y = y + (yRad * sin(k * twicePi / RENDERER_CIRCLE_TRIANGLE_AMMOUNT)) };
                vector_add(&points, p2);
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

        switch(component->type) {
            case COMPONENT_TYPE_2D_RENDERER: {
                SparkComponentData* colorData = hashmap_get(component->data, &(SparkComponentData){ .key = "color" });
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
            vector_add(&indices, 0);
            vector_add(&indices, 1);
            vector_add(&indices, 2);
            vector_add(&indices, 0);
            vector_add(&indices, 3);
            vector_add(&indices, 2);

            rendererObject.drawType = GL_TRIANGLES;
            break;
        }

        case RENDERER_SHAPE_EMPTY_QUAD: {
            vector_add(&indices, 0);
            vector_add(&indices, 1);
            vector_add(&indices, 2);
            vector_add(&indices, 3);
            vector_add(&indices, 0);

            rendererObject.drawType = GL_LINE_LOOP;
            break;
        }

        case RENDERER_SHAPE_CIRCLE: {
            for(int k = 0; k < RENDERER_CIRCLE_TRIANGLE_AMMOUNT - 1; k++) {
                vector_add(&indices, 0);
                vector_add(&indices, k + 1);
                vector_add(&indices, k + 2);
            }
            vector_add(&indices, 0);
            vector_add(&indices, RENDERER_CIRCLE_TRIANGLE_AMMOUNT);
            vector_add(&indices, 1);

            rendererObject.drawType = GL_TRIANGLES;
            break;
        }

        case RENDERER_SHAPE_EMPTY_CIRCLE: {
            for(int k = 0; k < RENDERER_CIRCLE_TRIANGLE_AMMOUNT; k++) {
                vector_add(&indices, k);
            }

            rendererObject.drawType = GL_LINE_LOOP;
            break;
        }
    }

    rendererObject.vertices = vertices;
    rendererObject.indices = indices;
    switch(component->type) {
        case COMPONENT_TYPE_2D_RENDERER: {
            rendererObject.type = RENDERER_OBJECT_TYPE_2D_COLOR;
            break;
        }

        case COMPONENT_TYPE_2D_TEXTURE_RENDERER: {
            SparkComponentData* textureData = hashmap_get(component->data, &(SparkComponentData){ .key = "texture" });
            SparkTexture* texture = textureData->data;

            rendererObject.type = RENDERER_OBJECT_TYPE_2D_TEXTURE;
            rendererObject.texture = texture;
            break;
        }
    }
    
    return rendererObject;
}