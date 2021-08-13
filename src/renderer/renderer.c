#include "utils/renderer_object.h"
#include "shaders/shader.h"
#include "2D/2D_utils.h"
#include "3D/3D_utils.h"
#include "../structs/scene.h"
#include "../utils/hashmap_utils.h"
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
    renderer->materials = hashmap_new(sizeof(SparkMaterial), 0, 0, 0, sparkHashmapMaterialHash, sparkHashmapMaterialCompare, NULL);
    renderer->window = window;
}

void sparkCompileShaders(SparkRenderer* renderer) {
    int size;
    const unsigned char* colorVertexShaderSource0 = sparkReadFile("D:\\Coding\\spark-engine\\build_src\\shaders\\2D_color_vertex.shader", true, &size);
    const unsigned char* colorFragmentShaderSource0 = sparkReadFile("D:\\Coding\\spark-engine\\build_src\\shaders\\2D_color_fragment.shader", true, &size);

    SparkShader colorShader0 = sparkCreateShader("2DColor", colorVertexShaderSource0, colorFragmentShaderSource0);
    hashmap_set(renderer->shaders, &colorShader0);

    const unsigned char* textureVertexShaderSource0 = sparkReadFile("D:\\Coding\\spark-engine\\build_src\\shaders\\2D_tex_vertex.shader", true, &size);
    const unsigned char* textureFragmentShaderSource0 = sparkReadFile("D:\\Coding\\spark-engine\\build_src\\shaders\\2D_tex_fragment.shader", true, &size);

    SparkShader textureShader0 = sparkCreateShader("2DTexture", textureVertexShaderSource0, textureFragmentShaderSource0);
    hashmap_set(renderer->shaders, &textureShader0);

    const unsigned char* colorVertexShaderSource1 = sparkReadFile("D:\\Coding\\spark-engine\\build_src\\shaders\\3D_color_vertex.shader", true, &size);
    const unsigned char* colorFragmentShaderSource1 = sparkReadFile("D:\\Coding\\spark-engine\\build_src\\shaders\\3D_color_fragment.shader", true, &size);

    SparkShader colorShader1 = sparkCreateShader("3DColor", colorVertexShaderSource1, colorFragmentShaderSource1);
    hashmap_set(renderer->shaders, &colorShader1);

    const unsigned char* textureVertexShaderSource1 = sparkReadFile("D:\\Coding\\spark-engine\\build_src\\shaders\\3D_tex_vertex.shader", true, &size);
    const unsigned char* textureFragmentShaderSource1 = sparkReadFile("D:\\Coding\\spark-engine\\build_src\\shaders\\3D_tex_fragment.shader", true, &size);

    SparkShader textureShader1 = sparkCreateShader("3DTexture", textureVertexShaderSource1, textureFragmentShaderSource1);
    hashmap_set(renderer->shaders, &textureShader1);
}

void sparkOnWindowResize(GLFWwindow* window, int ww, int wh) {
    glViewport(0, 0, ww, wh);
}

void sparkCreateRendererObjects(SparkRenderer* renderer) {
    glfwGetWindowSize(renderer->window, &renderer->ww, &renderer->wh);

    /* Create renderer objects */
    renderer->rendererObjects = vector_create();
    int numOfGameObjects = vector_size(renderer->scene->gameObjects);
    for(int i = 0; i < numOfGameObjects; i++) {
        SparkGameObject* gameObject = &renderer->scene->gameObjects[i];

        int numOfComponents = vector_size(gameObject->components);
        for(int j = 0; j < numOfComponents; j++) {
            SparkComponent* component = &gameObject->components[j];

            switch(component->type) {
                case COMPONENT_TYPE_2D_RENDERER:
                case COMPONENT_TYPE_2D_TEXTURE_RENDERER: {
                    SparkRendererObject rendererObject = sparkCreateRendererObject2D(renderer, gameObject, component);
                    vector_add(&renderer->rendererObjects, rendererObject);
                }

                case COMPONENT_TYPE_3D_RENDERER:
                case COMPONENT_TYPE_3D_TEXTURE_RENDERER: {
                    SparkRendererObject rendererObject = sparkCreateRendererObject3D(renderer, gameObject, component);
                    //vector_add(&renderer->rendererObjects, rendererObject);
                }
            }
        }
    }

    /* Generate buffers for each rendered object, buffer their data and set their vertex attributes */
    /* TODO: move this somewhere else */
    for(int i = 0; i < vector_size(renderer->rendererObjects); i++) {
        SparkRendererObject* rendererObject = &renderer->rendererObjects[i];
        sparkGenerateBuffersInRendererObject(rendererObject);
        sparkBindRendererObject(rendererObject);
        sparkBufferDataInRendererObject(rendererObject);

        switch(rendererObject->type) {
            case RENDERER_OBJECT_TYPE_2D_COLOR:
            case RENDERER_OBJECT_TYPE_3D_COLOR: {
                sparkLinkAttributesInRendererObject(rendererObject, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
                sparkLinkAttributesInRendererObject(rendererObject, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
                break;
            }

            case RENDERER_OBJECT_TYPE_2D_TEXTURE:
            case RENDERER_OBJECT_TYPE_3D_TEXTURE: {
                sparkLinkAttributesInRendererObject(rendererObject, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
                sparkLinkAttributesInRendererObject(rendererObject, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
                break;
            }
        }

        sparkUnbindRendererObject();
    }
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

    /* Create renderer objects */
    sparkCreateRendererObjects(renderer);

    /* Main render loop */
    while(!glfwWindowShouldClose(renderer->window)) {
        float deltaTime = ((clock() - clock_0) / 1000.0f);
        if(deltaTime > targetDeltaTime) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            /* speeeen */
            glm_rotate(model, glm_rad(5.0f), rotVec);

            /* Draw all renderer objects */
            for(int i = 0; i < vector_size(renderer->rendererObjects); i++) {
                SparkRendererObject* rendererObject = &renderer->rendererObjects[i];

                SparkComponentData* shaderData = hashmap_get(rendererObject->material->data, &(SparkComponentData){ .key = "shader" });
                SparkShader* shader = shaderData->data;

                sparkBindRendererObject(rendererObject);
                sparkActivateShader(shader);
                switch(rendererObject->type) {
                    case RENDERER_OBJECT_TYPE_3D_COLOR: {
                        GLuint modelLoc0 = glGetUniformLocation(shader->id, "model");
                        glUniformMatrix4fv(modelLoc0, 1, GL_FALSE, model);
                        GLuint viewLoc0 = glGetUniformLocation(shader->id, "view");
                        glUniformMatrix4fv(viewLoc0, 1, GL_FALSE, view);
                        GLuint projLoc0 = glGetUniformLocation(shader->id, "proj");
                        glUniformMatrix4fv(projLoc0, 1, GL_FALSE, proj);
                        break;
                    }

                    case RENDERER_OBJECT_TYPE_2D_TEXTURE: {
                        SparkComponentData* textureData = hashmap_get(rendererObject->material->data, &(SparkComponentData){ .key = "texture" });
                        SparkTexture* texture = textureData->data;

                        GLuint uniTex1 = glGetUniformLocation(shader->id, "tex0");
                        glUniform1f(uniTex1, 0);

                        glBindTexture(GL_TEXTURE_2D, texture->id);
                        break;
                    }

                    case RENDERER_OBJECT_TYPE_3D_TEXTURE: {
                        SparkComponentData* textureData = hashmap_get(rendererObject->material->data, &(SparkComponentData){ .key = "texture" });
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

    /* TODO: this is the place where renderer objects will be created */
}