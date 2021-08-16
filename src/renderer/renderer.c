#include "utils/renderer_object.h"
#include "shaders/shader.h"
#include "2D/2D_utils.h"
#include "3D/3D_utils.h"
#include "../structs/scene.h"
#include "../utils/hashmap_utils.h"
#include "../utils/math.h"
#include "../utils/print.h"

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
    renderer->materials = hashmap_new(sizeof(SparkMaterial), 0, 0, 0, sparkHashmapMaterialHash, sparkHashmapMaterialCompare, NULL);
    renderer->window = window;
}

SparkShader sparkCompileShader(SparkRenderer* renderer, char* name, char* vertexPath, char* fragmentPath) {
    int size;
    const unsigned char* colorVertexShaderSource = sparkReadFile(vertexPath, true, &size);
    const unsigned char* colorFragmentShaderSource = sparkReadFile(fragmentPath, true, &size);

    SparkShader shader = sparkCreateShader(name, colorVertexShaderSource, colorFragmentShaderSource);
    hashmap_set(renderer->shaders, &shader);
    return shader;
}

void sparkOnWindowResize(GLFWwindow* window, int ww, int wh) {
    glViewport(0, 0, ww, wh);
}

void sparkCreateRendererObjects(SparkRenderer* renderer) {
    sparkDeleteRendererObjects(renderer);

    int numOfGameObjects = vector_size(renderer->scene->gameObjects);
    for(int i = 0; i < numOfGameObjects; i++) {
        SparkGameObject* gameObject = &renderer->scene->gameObjects[i];
        sparkCreateRendererObject(renderer, gameObject);    
    }
}

void sparkCreateRendererObject(SparkRenderer* renderer, SparkGameObject* gameObject) {
    int numOfComponents = vector_size(gameObject->components);
    for(int j = 0; j < numOfComponents; j++) {
        SparkComponent* component = &gameObject->components[j];

        switch(component->type) {
            case COMPONENT_TYPE_2D_RENDERER:
            case COMPONENT_TYPE_2D_TEXTURE_RENDERER: {
                SparkRendererObject rendererObject = sparkCreateRendererObject2D(renderer, gameObject, component);
                sparkInitializeRendererObject(&rendererObject);
                sparkUpdateRendererObject(renderer, &rendererObject);
                
                vector_add(&renderer->rendererObjects, rendererObject);
                break;
            }

            case COMPONENT_TYPE_3D_RENDERER:
            case COMPONENT_TYPE_3D_TEXTURE_RENDERER: {
                SparkRendererObject rendererObject = sparkCreateRendererObject3D(renderer, gameObject, component);
                sparkInitializeRendererObject(&rendererObject);
                sparkUpdateRendererObject(renderer, &rendererObject);

                vector_add(&renderer->rendererObjects, rendererObject);
                break;
            }
        }
    }
}

void sparkUpdateRendererObjects(SparkRenderer* renderer) {
    for(int i = 0; i < vector_size(renderer->rendererObjects); i++) {
        SparkRendererObject* rendererObject = &renderer->rendererObjects[i];
        sparkUpdateRendererObject(renderer, rendererObject);
    }
}

void sparkUpdateRendererObject(SparkRenderer* renderer, SparkRendererObject* rendererObject) {
    sparkBindRendererObject(rendererObject);
    switch(rendererObject->component->type) {
        case COMPONENT_TYPE_2D_RENDERER:
        case COMPONENT_TYPE_2D_TEXTURE_RENDERER: {
            sparkUpdateRendererObject2D(renderer, rendererObject);
            break;
        }

        case COMPONENT_TYPE_3D_RENDERER:
        case COMPONENT_TYPE_3D_TEXTURE_RENDERER: {
            sparkUpdateRendererObject3D(renderer, rendererObject);
            break;
        }
    }
    sparkBufferDataInRendererObject(rendererObject);
    sparkUnbindRendererObject();
}

void sparkDeleteRendererObjects(SparkRenderer* renderer) {
    for(int i = 0; i < vector_size(renderer->rendererObjects); i++) {
        SparkRendererObject* rendererObject = &renderer->rendererObjects[i];
        sparkDeleteRendererObject(rendererObject);
    }
    vector_free(renderer->rendererObjects);
    renderer->rendererObjects = vector_create();
}

void sparkRender(SparkRenderer* renderer) {
    /* [temporary] Create model matrices */
    SparkMat4 model, view, proj;
    glm_mat4_identity_array(&model, 1);
    glm_mat4_identity_array(&view, 1);
    glm_mat4_identity_array(&proj, 1);

    vec3 locVec = { 0.35f, -0.35f, -2.0f };
    vec3 rotVec = { 1.0f, 1.0f, 1.0f };
    glm_translate(view, locVec);
    glm_perspective(glm_rad(90.0f), (float)renderer->ww / (float)renderer->wh, 0.1f, 100.0f, proj);

    /* FPS limiter */
    float targetFPS = 60.00f;
    float targetDeltaTime = targetFPS < 0.0f ? 0.0f : 1.00f / targetFPS;
    clock_t clock_0 = clock();

    float bounceValue = 0.0f;
    float bounceX = 3.0f;
    float bounceY = 3.0f;

    /* Main render loop */
    while(!glfwWindowShouldClose(renderer->window)) {
        float deltaTime = ((clock() - clock_0) / 1000.0f);
        if(deltaTime > targetDeltaTime) {
            glfwGetWindowSize(renderer->window, &renderer->ww, &renderer->wh);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            /* stupid bouncing dvd thing */
            SparkComponentData* bounceSizeData = hashmap_get(renderer->scene->gameObjects[0].components[0].data, &(SparkComponentData){ .key = "size" });
            SparkVector2* bounceSize = bounceSizeData->data;
            renderer->scene->gameObjects[0].pos.x += bounceX;
            renderer->scene->gameObjects[0].pos.y += bounceY;
            if(renderer->scene->gameObjects[0].pos.x < 0 || renderer->scene->gameObjects[0].pos.x + bounceSize->x > renderer->ww) {
                bounceX = -bounceX;
                bounceY = rand() % 2 == 0 ? -bounceY : bounceY;
            } else if(renderer->scene->gameObjects[0].pos.y < 0 || renderer->scene->gameObjects[0].pos.y + bounceSize->y > renderer->wh) {
                bounceY = -bounceY;
                bounceX = rand() % 2 == 0 ? -bounceX : bounceX;
            }

            /* Update all renderer objects */
            sparkUpdateRendererObjects(renderer);

            /* Draw all renderer objects */
            /* TODO: move this somewhere else */
            for(int i = 0; i < vector_size(renderer->rendererObjects); i++) {
                SparkRendererObject* rendererObject = &renderer->rendererObjects[i];

                SparkComponentData* materialData = hashmap_get(rendererObject->component->data, &(SparkComponentData){ .key = "material" });
                SparkMaterial* material = materialData->data;
                SparkComponentData* shaderData = hashmap_get(material->data, &(SparkComponentData){ .key = "shader" });
                SparkShader* shader = shaderData->data;

                sparkBindRendererObject(rendererObject);
                sparkActivateShader(shader);
                switch(rendererObject->component->type) {
                    case COMPONENT_TYPE_3D_RENDERER: {
                        GLuint modelLoc0 = glGetUniformLocation(shader->id, "model");
                        glUniformMatrix4fv(modelLoc0, 1, GL_FALSE, model);
                        GLuint viewLoc0 = glGetUniformLocation(shader->id, "view");
                        glUniformMatrix4fv(viewLoc0, 1, GL_FALSE, view);
                        GLuint projLoc0 = glGetUniformLocation(shader->id, "proj");
                        glUniformMatrix4fv(projLoc0, 1, GL_FALSE, proj);
                        break;
                    }

                    case COMPONENT_TYPE_2D_TEXTURE_RENDERER: {
                        SparkComponentData* textureData = hashmap_get(material->data, &(SparkComponentData){ .key = "texture" });
                        SparkTexture* texture = textureData->data;

                        GLuint uniTex1 = glGetUniformLocation(shader->id, "tex0");
                        glUniform1f(uniTex1, 0);

                        glBindTexture(GL_TEXTURE_2D, texture->id);
                        break;
                    }

                    case COMPONENT_TYPE_3D_TEXTURE_RENDERER: {
                        SparkComponentData* textureData = hashmap_get(material->data, &(SparkComponentData){ .key = "texture" });
                        SparkTexture* texture = textureData->data;

                        GLuint modelLoc1 = glGetUniformLocation(shader->id, "model");
                        glUniformMatrix4fv(modelLoc1, 1, GL_FALSE, model);
                        GLuint viewLoc1 = glGetUniformLocation(shader->id, "view");
                        glUniformMatrix4fv(viewLoc1, 1, GL_FALSE, view);
                        GLuint projLoc1 = glGetUniformLocation(shader->id, "proj");
                        glUniformMatrix4fv(projLoc1, 1, GL_FALSE, proj);

                        GLuint uniTex1 = glGetUniformLocation(shader->id, "tex0");
                        glUniform1f(uniTex1, 0);

                        glBindTexture(GL_TEXTURE_2D, texture->id);
                        break;
                    }
                }
                sparkDrawRendererObject(rendererObject);

                sparkUnbindRendererObject();
            }

            clock_0 = clock();
            glfwSwapBuffers(renderer->window);
        }

        glfwPollEvents();
    }

    sparkDeleteRendererObjects(renderer);
    hashmap_scan(renderer->shaders, sparkDeleteShaderIter, NULL);
    /* TODO: Delete all textures */
    /* TODO: Delete all materials */

    glfwDestroyWindow(renderer->window);
    glfwTerminate();
}

void sparkLoadScene(SparkRenderer* renderer, SparkScene* scene) {
    renderer->scene = scene;

    sparkCreateRendererObjects(renderer);
}