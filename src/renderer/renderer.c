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
    renderer->shaders = hashmap_new(sizeof(SparkShader), 0, 0, 0, sparkHasmapShaderHash, sparkHashmapShaderCompare, NULL)
    renderer->textures = hashmap_new(sizeof(SparkTexture), 0, 0, 0, sparkHasmapTextureHash, sparkHashmapTextureCompare, NULL)
    renderer->window = window;
}

void sparkCompileShaders(SparkRenderer* renderer) {
    int size;
    const unsigned char* colorVertexShaderSource = sparkReadFile("D:\\Coding\\spark-engine\\build_src\\shaders\\color_vertex.shader", true, &size);
    const unsigned char* colorFragmentShaderSource = sparkReadFile("D:\\Coding\\spark-engine\\build_src\\shaders\\color_fragment.shader", true, &size);

    SparkShader colorShader;
    sparkInitializeShader(&colorShader, "Color", colorVertexShaderSource, colorFragmentShaderSource);
    vector_add(&renderer->shaders, colorShader);

    const unsigned char* textureVertexShaderSource = sparkReadFile("D:\\Coding\\spark-engine\\build_src\\shaders\\tex_vertex.shader", true, &size);
    const unsigned char* textureFragmentShaderSource = sparkReadFile("D:\\Coding\\spark-engine\\build_src\\shaders\\tex_fragment.shader", true, &size);

    SparkShader textureShader;
    sparkInitializeShader(&textureShader, "Texture", textureVertexShaderSource, textureFragmentShaderSource);
    vector_add(&renderer->shaders, textureShader);
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
                    if(component->type == COMPONENT_TYPE_RENDERER) {
                        rendererObject.type = RENDERER_OBJECT_TYPE_COLOR;
                    } else if(component->type == COMPONENT_TYPE_TEXTURE_RENDERER) {
                        SparkComponentData* textureData = hashmap_get(component->data, &(SparkComponentData){ .key = "texture" });
                        SparkTexture* texture = textureData->data;

                        rendererObject.type = RENDERER_OBJECT_TYPE_TEXTURE;
                        rendererObject.texture = texture;
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

    /* Specify background color */
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void sparkRender(SparkRenderer* renderer) {
    GLuint uniTex = glGetUniformLocation(renderer->shaders[1].id, "tex0");
    glUniform1f(uniTex, 0);

    float targetFPS = 60.0f;
    clock_t clock_0 = clock();
    while(!glfwWindowShouldClose(renderer->window)) {
        if(targetFPS < 0 || (clock() - clock_0) / CLOCKS_PER_SEC > 1 / targetFPS) {
            glClear(GL_COLOR_BUFFER_BIT);
            /* TODO: Delete all renderer objects and their buffers (or not create new renderer objects and buffers everytime) */

            /* Create renderer objects */
            sparkCreateRendererObjects(renderer);

            /* h */
            SparkMat4 model = GLM_MAT4_IDENTITY_INIT, view = GLM_MAT4_IDENTITY_INIT, proj = GLM_MAT4_IDENTITY_INIT;
            vec3 locVec = { 0.0f, -0.5f, -2.0f };
            vec3 rotVec = { 0.0f, 1.0f, 0.0f };

            glm_rotate(model, glm_rad(45.0f), rotVec);
            glm_translate(view, locVec);
            glm_perspective(glm_rad(45.0f), (float)(renderer->ww / renderer->wh), 0.1f, 100.0f, proj);

            GLuint modelLoc = glGetUniformLocation(renderer->shaders[0].id, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);
            GLuint viewLoc = glGetUniformLocation(renderer->shaders[0].id, "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view);
            GLuint projLoc = glGetUniformLocation(renderer->shaders[0].id, "proj");
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, proj);

            /* Draw all renderer objects */
            for(int i = 0; i < vector_size(renderer->rendererObjects); i++) {
                SparkRendererObject* rendererObject = &renderer->rendererObjects[i];

                sparkBindRendererObject(rendererObject);
                /* TODO: Assign a shader to the renderer object */
                if(rendererObject->type == RENDERER_OBJECT_TYPE_COLOR) {
                    sparkActivateShader(&renderer->shaders[0]);
                } else {
                    sparkActivateShader(&renderer->shaders[1]);
                    glBindTexture(GL_TEXTURE_2D, rendererObject->texture->id);
                }
                sparkDrawRendererObject(rendererObject);
            
                sparkUnbindRendererObject();
            }

            clock_0 = clock();
            glfwSwapBuffers(renderer->window);
        }

        glfwPollEvents();
    }

    for(int i = 0; i < vector_size(renderer->rendererObjects); i++) {
        SparkRendererObject* rendererObject = &renderer->rendererObjects[i];
        sparkDeleteRendererObject(rendererObject);
    }
    for(int i = 0; i < vector_size(renderer->shaders); i++) {
        SparkShader* shader = &renderer->shaders[i];
        sparkDeleteShader(shader);
    }
    /* TODO: Delete all textures */

    glfwDestroyWindow(renderer->window);
    glfwTerminate();
}

void sparkLoadScene(SparkRenderer* renderer, SparkScene* scene) {
    renderer->scene = scene;
}