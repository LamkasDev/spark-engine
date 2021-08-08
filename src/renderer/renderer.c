#include "utils/renderer_object.h"
#include "shaders/shader.h"
#include "../utils/hashmap_utils.h"
#include "../utils/scene.h"
#include "../utils/math.h"

void sparkSetupWindow(SparkRenderer* renderer) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Spark - Preview", NULL, NULL);
    if(window == NULL) {
        printf("Failed to create GLFW window!");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, sparkOnWindowResize);
    gladLoadGL();

    glfwGetWindowSize(window, &renderer->ww, &renderer->wh);
    glViewport(0, 0, renderer->ww, renderer->wh);

    renderer->rendererObjects = vector_create();
    renderer->shaders = hashmap_new(sizeof(SparkShader), 0, 0, 0, sparkHasmapShaderHash, sparkHashmapShaderCompare, NULL);
    renderer->textures = hashmap_new(sizeof(SparkTexture), 0, 0, 0, sparkHashmapTextureHash, sparkHashmapTextureCompare, NULL);
    renderer->window = window;
}

void sparkCompileShaders(SparkRenderer* renderer) {
    int size;
    const unsigned char* colorVertexShaderSource0 = sparkReadFile("D:\\Coding\\spark-engine\\build_src\\shaders\\2D_color_vertex.shader", true, &size);
    const unsigned char* colorFragmentShaderSource0 = sparkReadFile("D:\\Coding\\spark-engine\\build_src\\shaders\\2D_color_fragment.shader", true, &size);

    SparkShader colorShader0;
    sparkInitializeShader(&colorShader0, "2DColor", colorVertexShaderSource0, colorFragmentShaderSource0);
    hashmap_set(renderer->shaders, &colorShader0);

    const unsigned char* textureVertexShaderSource0 = sparkReadFile("D:\\Coding\\spark-engine\\build_src\\shaders\\2D_tex_vertex.shader", true, &size);
    const unsigned char* textureFragmentShaderSource0 = sparkReadFile("D:\\Coding\\spark-engine\\build_src\\shaders\\2D_tex_fragment.shader", true, &size);

    SparkShader textureShader0;
    sparkInitializeShader(&textureShader0, "2DTexture", textureVertexShaderSource0, textureFragmentShaderSource0);
    hashmap_set(renderer->shaders, &textureShader0);

    const unsigned char* colorVertexShaderSource1 = sparkReadFile("D:\\Coding\\spark-engine\\build_src\\shaders\\3D_color_vertex.shader", true, &size);
    const unsigned char* colorFragmentShaderSource1 = sparkReadFile("D:\\Coding\\spark-engine\\build_src\\shaders\\3D_color_fragment.shader", true, &size);

    SparkShader colorShader1;
    sparkInitializeShader(&colorShader1, "3DColor", colorVertexShaderSource1, colorFragmentShaderSource1);
    hashmap_set(renderer->shaders, &colorShader1);

    const unsigned char* textureVertexShaderSource1 = sparkReadFile("D:\\Coding\\spark-engine\\build_src\\shaders\\3D_tex_vertex.shader", true, &size);
    const unsigned char* textureFragmentShaderSource1 = sparkReadFile("D:\\Coding\\spark-engine\\build_src\\shaders\\3D_tex_fragment.shader", true, &size);

    SparkShader textureShader1;
    sparkInitializeShader(&textureShader1, "3DTexture", textureVertexShaderSource1, textureFragmentShaderSource1);
    hashmap_set(renderer->shaders, &textureShader1);
}

void sparkOnWindowResize(GLFWwindow* window, int ww, int wh) {
    glViewport(0, 0, ww, wh);
}

void sparkCreateRendererObjects(SparkRenderer* renderer) {
    glfwGetWindowSize(renderer->window, &renderer->ww, &renderer->wh);
    int ww = renderer->ww;
    int wh = renderer->wh;

    /* Create renderer objects and their vertices */
    renderer->rendererObjects = vector_create();
    int numOfGameObjects = vector_size(renderer->scene->gameObjects);
    for(int i = 0; i < numOfGameObjects; i++) {
        SparkGameObject* gameObject = &renderer->scene->gameObjects[i];

        int numOfComponents = vector_size(gameObject->components);
        for(int j = 0; j < numOfComponents; j++) {
            SparkComponent* component = &gameObject->components[j];

            switch(component->type) {
                case COMPONENT_TYPE_RENDERER:
                case COMPONENT_TYPE_TEXTURE_RENDERER: {
                    SparkVector2* points = vector_create();

                    SparkComponentData* shapeData = hashmap_get(component->data, &(SparkComponentData){ .key = "shape" });
                    int* shape = shapeData->data;
                    SparkComponentData* sizeData = hashmap_get(component->data, &(SparkComponentData){ .key = "size" });
                    SparkVector2* size = sizeData->data;

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
                            case COMPONENT_TYPE_RENDERER: {
                                SparkComponentData* colorData = hashmap_get(component->data, &(SparkComponentData){ .key = "color" });
                                SparkColor* color = colorData->data;
                            
                                /* Add colors */
                                vector_add(&vertices, color->r);
                                vector_add(&vertices, color->g);
                                vector_add(&vertices, color->b);
                                break;
                            }

                            case COMPONENT_TYPE_TEXTURE_RENDERER: {
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

                    SparkRendererObject rendererObject;
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
                        case COMPONENT_TYPE_RENDERER: {
                            rendererObject.type = RENDERER_OBJECT_TYPE_COLOR;
                            break;
                        }

                        case COMPONENT_TYPE_TEXTURE_RENDERER: {
                            SparkComponentData* textureData = hashmap_get(component->data, &(SparkComponentData){ .key = "texture" });
                            SparkTexture* texture = textureData->data;

                            rendererObject.type = RENDERER_OBJECT_TYPE_TEXTURE;
                            rendererObject.texture = texture;
                            break;
                        }
                    }
                    
                    vector_add(&renderer->rendererObjects, rendererObject);
                    break;
                }
            }
        }
    }

    /* Generate buffers for each rendered object, buffer their data and set their vertex attributes */
    for(int i = 0; i < vector_size(renderer->rendererObjects); i++) {
        SparkRendererObject* rendererObject = &renderer->rendererObjects[i];
        sparkGenerateBuffersInRendererObject(rendererObject);
        sparkBindRendererObject(rendererObject);
        sparkBufferDataInRendererObject(rendererObject);

        switch(rendererObject->type) {
            case RENDERER_OBJECT_TYPE_COLOR: {
                sparkLinkAttributesInRendererObject(rendererObject, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
                sparkLinkAttributesInRendererObject(rendererObject, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
                break;
            }

            case RENDERER_OBJECT_TYPE_TEXTURE: {
                sparkLinkAttributesInRendererObject(rendererObject, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
                sparkLinkAttributesInRendererObject(rendererObject, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
                break;
            }
        }

        sparkUnbindRendererObject();
    }
}

void sparkRender(SparkRenderer* renderer) {
    /* temporary */
    SparkShader* colorShader0 = hashmap_get(renderer->shaders, &(SparkShader){ .name = "2DColor" });
    SparkShader* textureShader0 = hashmap_get(renderer->shaders, &(SparkShader){ .name = "2DTexture" });
    SparkShader* colorShader1 = hashmap_get(renderer->shaders, &(SparkShader){ .name = "3DColor" });
    SparkShader* textureShader1 = hashmap_get(renderer->shaders, &(SparkShader){ .name = "3DTexture" });

    /* h */
    SparkMat4 model, view, proj;
    glm_mat4_identity_array(&model, 1);
    glm_mat4_identity_array(&view, 1);
    glm_mat4_identity_array(&proj, 1);

    vec3 locVec = { 0.35f, -0.35f, -2.0f };
    vec3 rotVec = { 1.0f, 1.0f, 1.0f };
    glm_translate(view, locVec);
    glm_perspective(glm_rad(90.0f), (float)renderer->ww / (float)renderer->wh, 0.1f, 100.0f, proj);

    float rot = 0.0f;
    float targetFPS = 60.00f;
    float targetDeltaTime = 1.00f / targetFPS;
    clock_t clock_0 = clock();

    while(!glfwWindowShouldClose(renderer->window)) {
        float deltaTime = ((clock() - clock_0) / 1000.0f);
        if(deltaTime > targetDeltaTime) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            /* TODO: Delete all renderer objects and their buffers (or not create new renderer objects and buffers everytime) */

            /* Create renderer objects */
            sparkCreateRendererObjects(renderer);

            /* speeeen */
            glm_rotate(model, glm_rad(rot), rotVec);

            /* Draw all renderer objects */
            for(int i = 0; i < vector_size(renderer->rendererObjects); i++) {
                SparkRendererObject* rendererObject = &renderer->rendererObjects[i];

                sparkBindRendererObject(rendererObject);
                /* TODO: Assign a shader to the renderer object */
                switch(rendererObject->type) {
                    case RENDERER_OBJECT_TYPE_COLOR: {
                        GLuint modelLoc0 = glGetUniformLocation(colorShader1->id, "model");
                        glUniformMatrix4fv(modelLoc0, 1, GL_FALSE, model);
                        GLuint viewLoc0 = glGetUniformLocation(colorShader1->id, "view");
                        glUniformMatrix4fv(viewLoc0, 1, GL_FALSE, view);
                        GLuint projLoc0 = glGetUniformLocation(colorShader1->id, "proj");
                        glUniformMatrix4fv(projLoc0, 1, GL_FALSE, proj);

                        sparkActivateShader(colorShader1);
                        break;
                    }

                    case RENDERER_OBJECT_TYPE_TEXTURE: {
                        GLuint modelLoc1 = glGetUniformLocation(textureShader1->id, "model");
                        glUniformMatrix4fv(modelLoc1, 1, GL_FALSE, model);
                        GLuint viewLoc1 = glGetUniformLocation(textureShader1->id, "view");
                        glUniformMatrix4fv(viewLoc1, 1, GL_FALSE, view);
                        GLuint projLoc1 = glGetUniformLocation(textureShader1->id, "proj");
                        glUniformMatrix4fv(projLoc1, 1, GL_FALSE, proj);

                        GLuint uniTex1 = glGetUniformLocation(textureShader1->id, "tex0");
                        glUniform1f(uniTex1, 0);

                        sparkActivateShader(textureShader1);
                        glBindTexture(GL_TEXTURE_2D, rendererObject->texture->id);
                        break;
                    }
                }
                sparkDrawRendererObject(rendererObject);
            
                sparkUnbindRendererObject();
            }

            clock_0 = clock();
            rot += 0.10f;
            glfwSwapBuffers(renderer->window);
        }

        glfwPollEvents();
    }

    for(int i = 0; i < vector_size(renderer->rendererObjects); i++) {
        SparkRendererObject* rendererObject = &renderer->rendererObjects[i];
        sparkDeleteRendererObject(rendererObject);
    }
    hashmap_scan(renderer->shaders, sparkDeleteShaderIter, NULL);
    /* TODO: Delete all textures */

    glfwDestroyWindow(renderer->window);
    glfwTerminate();
}

void sparkLoadScene(SparkRenderer* renderer, SparkScene* scene) {
    renderer->scene = scene;
}