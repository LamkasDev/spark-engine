SparkRendererObject sparkCreateRendererObject2D(SparkRenderer* renderer, SparkGameObject* gameObject, SparkComponent* component) {
    int ww = renderer->ww;
    int wh = renderer->wh;

    SparkComponentData* materialData = hashmap_get(component->data, &(SparkComponentData){ .key = "material" });
    SparkMaterial* material = materialData->data;
    SparkComponentData* shapeData = hashmap_get(material->data, &(SparkComponentData){ .key = "shape" });
    int* shape = shapeData->data;

    SparkComponentData* sizeData = hashmap_get(component->data, &(SparkComponentData){ .key = "size" });
    SparkVector2* size = sizeData->data;

    SparkRendererObject rendererObject;
    SparkVector2* points = vector_create();
    switch(*shape) {
        case RENDERER_SHAPE_QUAD:
        case RENDERER_SHAPE_EMPTY_QUAD: {
            SparkComponentData* borderData = hashmap_get(component->data, &(SparkComponentData){ .key = "border" });
            if(borderData == NULL) {
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
            } else {
                GLfloat twicePi = 2.0f * GLM_PI;

                float* border = borderData->data;
                GLfloat borderRad = (((size->y / ww) * 2.0f) / 2.0f) * (*border);
                GLfloat x = 0.0f;
                GLfloat y = 0.0f;

                /* Point (Center) */
                SparkVector2 p0 = { .x = -1.0f + ((gameObject->pos.x / ww) * 2.0f) + (size->x / ww), .y = 1.0f - ((gameObject->pos.y / wh) * 2.0f) - (size->y / wh) };
                vector_add(&points, p0);
                
                /* Point (Bottom Center) */
                SparkVector2 p1 = { .x = -1.0f + ((gameObject->pos.x / ww) * 2.0f) + (size->x / ww), .y = 1.0f - ((gameObject->pos.y / wh) * 2.0f) - ((size->y / wh) * 2.0f) };
                vector_add(&points, p1);
                /* Border (Bottom Right) */
                x = -1.0f + ((gameObject->pos.x / ww) * 2.0f) + ((size->x / ww) * 2.0f) - borderRad;
                y = 1.0f - ((gameObject->pos.y / wh) * 2.0f) - ((size->y / wh) * 2.0f) + borderRad;
                for(int k = RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_0 * 3; k < RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1; k++) {
                    SparkVector2 p = { .x = x + (borderRad * cos(k * twicePi / RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1)), .y = y + (borderRad * sin(k * twicePi / RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1)) };
                    vector_add(&points, p);
                }
                SparkVector2 p1B = { .x = x + borderRad, .y = y };
                vector_add(&points, p1B);
                /* Point (Right Center) */
                SparkVector2 p2 = { .x = -1.0f + ((gameObject->pos.x / ww) * 2.0f) + ((size->x / ww) * 2.0f), .y = 1.0f - ((gameObject->pos.y / wh) * 2.0f) - (size->y / wh) };
                vector_add(&points, p2);
                /* Border (Top Right) */
                x = -1.0f + ((gameObject->pos.x / ww) * 2.0f) + ((size->x / ww) * 2.0f) - borderRad;
                y = 1.0f - ((gameObject->pos.y / wh) * 2.0f) - borderRad;
                for(int k = 0; k < RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_0; k++) {
                    SparkVector2 p = { .x = x + (borderRad * cos(k * twicePi / RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1)), .y = y + (borderRad * sin(k * twicePi / RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1)) };
                    vector_add(&points, p);
                }
                SparkVector2 p2B = { .x = x, .y = y + borderRad };
                vector_add(&points, p2B);
                /* Point (Top Center) */
                SparkVector2 p3 = { .x = -1.0f + ((gameObject->pos.x / ww) * 2.0f) + (size->x / ww), .y = 1.0f - ((gameObject->pos.y / wh) * 2.0f) };
                vector_add(&points, p3);
                /* Border (Top Left) */
                x = -1.0f + ((gameObject->pos.x / ww) * 2.0f) + borderRad;
                y = 1.0f - ((gameObject->pos.y / wh) * 2.0f) - borderRad;
                for(int k = RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_0 * 1; k < RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_0 * 2; k++) {
                    SparkVector2 p = { .x = x + (borderRad * cos(k * twicePi / RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1)), .y = y + (borderRad * sin(k * twicePi / RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1)) };
                    vector_add(&points, p);
                }
                SparkVector2 p3B = { .x = x - borderRad, .y = y };
                vector_add(&points, p3B);
                /* Point (Left Center) */
                SparkVector2 p4 = { .x = -1.0f + ((gameObject->pos.x / ww) * 2.0f), .y = 1.0f - ((gameObject->pos.y / wh) * 2.0f) - (size->y / wh) };
                vector_add(&points, p4);
                /* Border (Bottom Left) */
                x = -1.0f + ((gameObject->pos.x / ww) * 2.0f) + borderRad;
                y = 1.0f - ((gameObject->pos.y / wh) * 2.0f) - ((size->y / wh) * 2.0f) + borderRad;
                for(int k = RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_0 * 2; k < RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_0 * 3; k++) {
                    SparkVector2 p = { .x = x + (borderRad * cos(k * twicePi / RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1)), .y = y + (borderRad * sin(k * twicePi / RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1)) };
                    vector_add(&points, p);
                }
                SparkVector2 p4B = { .x = x, .y = y - borderRad };
                vector_add(&points, p4B);

                //sparkPrintPoints(points);
            }
            break;
        }

        case RENDERER_SHAPE_CIRCLE:
        case RENDERER_SHAPE_EMPTY_CIRCLE: {
            GLfloat twicePi = 2.0f * GLM_PI;

            GLfloat xRad = (((size->y / ww) * 2.0f) / 2.0f);
            GLfloat yRad = (((size->y / wh) * 2.0f) / 2.0f);
            GLfloat x = -1.0f + ((gameObject->pos.x / ww) * 2.0f) + xRad;
            GLfloat y = 1.0f - ((gameObject->pos.y / wh) * 2.0f) - yRad;
            
            /* Point (Center) */
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
            SparkComponentData* borderData = hashmap_get(component->data, &(SparkComponentData){ .key = "border" });
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
    rendererObject.material = material;

    switch(component->type) {
        case COMPONENT_TYPE_2D_RENDERER: {
            rendererObject.type = RENDERER_OBJECT_TYPE_2D_COLOR;
            break;
        }

        case COMPONENT_TYPE_2D_TEXTURE_RENDERER: {
            rendererObject.type = RENDERER_OBJECT_TYPE_2D_TEXTURE;
            break;
        }
    }
    
    return rendererObject;
}