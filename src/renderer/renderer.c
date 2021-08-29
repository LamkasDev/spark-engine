#include "utils/renderer_object_group.h"
#include "shaders/shader.h"
#include "2D/2D_utils.h"
#include "2D/text_utils.h"
#include "3D/3D_utils.h"

/**
 * Setups a renderer.
 * 
 * @param renderer a pointer to a renderer
 * 
 */
void sparkSetupRenderer(SparkRenderer* renderer) {
    renderer->store = sparkCreateStore();
    renderer->rendererObjectGroups = vector_create();
    renderer->shaders = hashmap_new(sizeof(SparkShader), 0, 0, 0, sparkHasmapShaderHash, sparkHashmapShaderCompare, NULL);
    renderer->textures = hashmap_new(sizeof(SparkTexture), 0, 0, 0, sparkHashmapTextureHash, sparkHashmapTextureCompare, NULL);
    renderer->materials = hashmap_new(sizeof(SparkMaterial), 0, 0, 0, sparkHashmapMaterialHash, sparkHashmapMaterialCompare, NULL);
    renderer->fonts = hashmap_new(sizeof(SparkFont), 0, 0, 0, sparkHashmapFontHash, sparkHashmapFontCompare, NULL);

    FT_Init_FreeType(&renderer->ft);
}

/**
 * Setups a GLFW windows and the renderer.
 * 
 * @param renderer a pointer to a renderer
 * 
 */
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

    renderer->window = window;
}

/**
 * Compiles a shader from paths to it's vertex and fragment files.
 * 
 * @param renderer a pointer to a renderer
 * @param name shader name
 * @param vertexPath path to the vertex shader
 * @param fragmentPath path to the fragment shader
 * 
 */
SparkShader sparkCompileShader(SparkRenderer* renderer, char* name, char* vertexPath, char* fragmentPath) {
    int size;
    const unsigned char* colorVertexShaderSource = sparkReadFile(vertexPath, true, &size);
    const unsigned char* colorFragmentShaderSource = sparkReadFile(fragmentPath, true, &size);

    SparkShader shader = sparkCreateShader(name, colorVertexShaderSource, colorFragmentShaderSource);
    hashmap_set(renderer->shaders, &shader);
    return shader;
}

/**
 * Called when the window is resized.
 * 
 * @param window window that was resized
 * @param ww window width
 * @param wh window height
 * 
 */
void sparkOnWindowResize(GLFWwindow* window, int ww, int wh) {
    glViewport(0, 0, ww, wh);
}

/**
 * Creates renderer object groups from the renderer's scene.
 * 
 * @param renderer a pointer to a renderer
 * 
 */
void sparkCreateAllRendererObjectGroups(SparkRenderer* renderer) {
    sparkDeleteAllRendererObjectGroups(renderer);

    int numOfGameObjects = vector_size(renderer->scene->gameObjects);
    for(int i = 0; i < numOfGameObjects; i++) {
        SparkGameObject* gameObject = &renderer->scene->gameObjects[i];
        sparkCreateRendererObjectGroups(renderer, gameObject);
    }
}

/**
 * Creates renderer object groups from a game object.
 * 
 * @param renderer a pointer to a renderer
 * @param gameObject a pointer to a game object
 * 
 */
void sparkCreateRendererObjectGroups(SparkRenderer* renderer, SparkGameObject* gameObject) {
    int numOfComponents = vector_size(gameObject->components);
    for(int i = 0; i < numOfComponents; i++) {
        SparkComponent* component = &gameObject->components[i];

        switch(component->type) {
            case COMPONENT_TYPE_2D_RENDERER:
            case COMPONENT_TYPE_2D_TEXTURE_RENDERER:
            case COMPONENT_TYPE_3D_RENDERER:
            case COMPONENT_TYPE_3D_TEXTURE_RENDERER:
            case COMPONENT_TYPE_TEXT_RENDERER: {
                SparkRendererObjectGroup rendererObjectGroup = sparkCreateRendererObjectGroup(renderer, gameObject, component);
                vector_add(&renderer->rendererObjectGroups, rendererObjectGroup);
                break;
            }
        }
    }
}

/**
 * Creates renderer object group from a component.
 * 
 * @param renderer a pointer to a renderer
 * @param gameObject a pointer to a game object
 * @param component a pointer to a component
 * 
 */
SparkRendererObjectGroup sparkCreateRendererObjectGroup(SparkRenderer* renderer, SparkGameObject* gameObject, SparkComponent* component) {
    switch(component->type) {
        case COMPONENT_TYPE_2D_RENDERER:
        case COMPONENT_TYPE_2D_TEXTURE_RENDERER: {
            SparkRendererObjectGroup rendererObjectGroup = {
                .objects = vector_create()
            };

            SparkRendererObject rendererObject = sparkCreateRendererObject2D(renderer, gameObject, component);
            sparkInitializeRendererObject(&rendererObject);
            sparkUpdateRendererObject(renderer, &rendererObject, 0);
            vector_add(&rendererObjectGroup.objects, rendererObject);
            return rendererObjectGroup;
        }

        case COMPONENT_TYPE_3D_RENDERER:
        case COMPONENT_TYPE_3D_TEXTURE_RENDERER: {
            SparkRendererObjectGroup rendererObjectGroup = {
                .objects = vector_create()
            };

            SparkRendererObject rendererObject = sparkCreateRendererObject3D(renderer, gameObject, component);
            sparkInitializeRendererObject(&rendererObject);
            sparkUpdateRendererObject(renderer, &rendererObject, 0);
            vector_add(&rendererObjectGroup.objects, rendererObject);
            return rendererObjectGroup;
        }

        case COMPONENT_TYPE_TEXT_RENDERER: {
            SparkRendererObjectGroup rendererObjectGroup = {
                .objects = vector_create()
            };

            SparkComponentData* textData = hashmap_get(component->data, &(SparkComponentData){ .key = "text" });
            char* text = renderer->store.strings[(uintptr_t)textData->data];
            for(int i = 0; i < strlen(text); i++) {
                SparkRendererObject rendererObject = sparkCreateRendererObjectText(renderer, gameObject, component);
                sparkInitializeRendererObject(&rendererObject);
                sparkUpdateRendererObject(renderer, &rendererObject, 0);
                vector_add(&rendererObjectGroup.objects, rendererObject);
            }
            return rendererObjectGroup;
        }
    }
}

/**
 * Updates all renderer object groups.
 * 
 * @param renderer a pointer to a renderer
 * 
 */
void sparkUpdateAllRendererObjectGroups(SparkRenderer* renderer) {
    int numOfGroups = vector_size(renderer->rendererObjectGroups);
    for(int i = 0; i < numOfGroups; i++) {
        SparkRendererObjectGroup* rendererObjectGroup = &renderer->rendererObjectGroups[i];
        sparkUpdateRendererObjectGroup(renderer, rendererObjectGroup);
    }
}

/**
 * Updates a renderer object group.
 * 
 * @param renderer a pointer to a renderer
 * @param rendererObjectGroup a pointer to a renderer object group
 * 
 */
void sparkUpdateRendererObjectGroup(SparkRenderer* renderer, SparkRendererObjectGroup* rendererObjectGroup) {
    int numOfObjects = vector_size(rendererObjectGroup->objects);
    for(int i = 0; i < numOfObjects; i++) {
        SparkRendererObject* rendererObject = &rendererObjectGroup->objects[i];
        sparkUpdateRendererObject(renderer, rendererObject, i);
    }
}

/**
 * Updates a renderer object.
 * 
 * @param renderer a pointer to a renderer
 * @param rendererObject a pointer to a renderer object
 * @param i index in a renderer object group
 * 
 */
void sparkUpdateRendererObject(SparkRenderer* renderer, SparkRendererObject* rendererObject, int i) {
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

        /* TODO: best case scenario will be when text is rendered in a single draw call with a single texture */
        case COMPONENT_TYPE_TEXT_RENDERER: {
            sparkUpdateRendererObjectText(renderer, rendererObject, i);
            break;
        }
    }
    sparkBufferDataInRendererObject(rendererObject);
    sparkUnbindRendererObject(rendererObject);
}

/**
 * Deletes all renderer object groups.
 * 
 * @param renderer a pointer to a renderer
 * 
 */
void sparkDeleteAllRendererObjectGroups(SparkRenderer* renderer) {
    int numOfGroups = vector_size(renderer->rendererObjectGroups);
    for(int i = 0; i < numOfGroups; i++) {
        SparkRendererObjectGroup* rendererObjectGroup = &renderer->rendererObjectGroups[i];
        sparkDeleteRendererObjectGroup(renderer, rendererObjectGroup);
    }
    vector_free(renderer->rendererObjectGroups);
    renderer->rendererObjectGroups = vector_create();
}

/**
 * Deletes a renderer object group.
 * 
 * @param renderer a pointer to a renderer
 * @param rendererObjectGroup a pointer to a renderer object group
 * 
 */
void sparkDeleteRendererObjectGroup(SparkRenderer* renderer, SparkRendererObjectGroup* rendererObjectGroup) {
    int numOfObjects = vector_size(rendererObjectGroup->objects);
    for(int i = 0; i < numOfObjects; i++) {
        SparkRendererObject* rendererObject = &rendererObjectGroup->objects[i];
        sparkDeleteRendererObject(rendererObject);
    }
}

/**
 * Renders the current scene.
 * 
 * @param renderer a pointer to a renderer
 * 
 */
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

    /* Main render loop */
    glfwGetWindowSize(renderer->window, &renderer->ww, &renderer->wh);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Update all renderer object groups */
    sparkUpdateAllRendererObjectGroups(renderer);

    /* Draw all renderer objects groups*/
    /* TODO: move this somewhere else */
    for(int i = 0; i < vector_size(renderer->rendererObjectGroups); i++) {
        SparkRendererObjectGroup* rendererObjectGroup = &renderer->rendererObjectGroups[i];
        for(int j = 0; j < vector_size(rendererObjectGroup->objects); j++) {
            SparkRendererObject* rendererObject = &rendererObjectGroup->objects[j];

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

                case COMPONENT_TYPE_TEXT_RENDERER: {
                    SparkComponentData* textData = hashmap_get(rendererObject->component->data, &(SparkComponentData){ .key = "text" });
                    char* text = renderer->store.strings[(uintptr_t)textData->data];
                    SparkComponentData* fontData = hashmap_get(rendererObject->component->data, &(SparkComponentData){ .key = "font" });
                    SparkFont* font = fontData->data;
                    SparkCharacter* currentCharacter = hashmap_get(font->characters, &(SparkCharacter){ .c = text[j] });

                    GLuint uniTex1 = glGetUniformLocation(shader->id, "tex0");
                    glUniform1f(uniTex1, 0);
                    GLuint uniColor = glGetUniformLocation(shader->id, "color");
                    glUniform3f(uniColor, 1.0f, 1.0f, 1.0f);

                    glBindTexture(GL_TEXTURE_2D, currentCharacter->id);
                    break;
                }
            }
            sparkDrawRendererObject(rendererObject);
            sparkUnbindRendererObject(rendererObject);
        }
    }

    glfwSwapBuffers(renderer->window);
}

/**
 * Loads a new scene.
 * 
 * @param renderer a pointer to a renderer
 * @param scene scene to be loaded
 * 
 */
void sparkLoadScene(SparkRenderer* renderer, SparkScene* scene) {
    renderer->scene = scene;
    sparkCreateAllRendererObjectGroups(renderer);
}

/**
 * Deletes a renderer.
 * 
 * @param renderer a pointer to a renderer
 * 
 */
void sparkDeleteRenderer(SparkRenderer* renderer) {
    sparkDeleteAllRendererObjectGroups(renderer);
    hashmap_scan(renderer->shaders, sparkDeleteShaderIter, NULL);
    hashmap_scan(renderer->textures, sparkDeleteTextureIter, NULL);
    hashmap_scan(renderer->materials, sparkDeleteMaterialIter, NULL);
    hashmap_scan(renderer->fonts, sparkDeleteFontIter, NULL);
}