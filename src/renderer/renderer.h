#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#define RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_0 15
#define RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1 60

#define RENDERER_SHAPE_UNKNOWN -1
#define RENDERER_SHAPE_QUAD 0
#define RENDERER_SHAPE_EMPTY_QUAD 1

#include "utils/renderer_object_group.h"
#include "shaders/shader.h"

struct SparkRenderer {
    GLFWwindow* window;
    FT_Library ft;
    
    SparkScene* scene;
    SparkStore store;

    SparkRendererObjectGroup* rendererObjectGroups;
    hashmap shaders;
    hashmap textures;
    hashmap materials;
    hashmap fonts;

    int ww;
    int wh;
};
typedef struct SparkRenderer SparkRenderer;

void sparkSetupRenderer(SparkRenderer* renderer);
void sparkSetupWindow(SparkRenderer* renderer);
void sparkOnWindowResize(GLFWwindow* window, int w, int h);

SparkShader sparkCompileShader(SparkRenderer* renderer, char* name, char* vertexPath, char* fragmentPath);

void sparkCreateAllRendererObjectGroups(SparkRenderer* renderer);
void sparkCreateRendererObjectGroups(SparkRenderer* renderer, SparkGameObject* gameObject);
SparkRendererObjectGroup sparkCreateRendererObjectGroup(SparkRenderer* renderer, SparkGameObject* gameObject, SparkComponent* component);

void sparkUpdateAllRendererObjectGroups(SparkRenderer* renderer);
void sparkUpdateRendererObjectGroup(SparkRenderer* renderer, SparkRendererObjectGroup* rendererObjectGroup);
void sparkUpdateRendererObject(SparkRenderer* renderer, SparkRendererObject* rendererObject, int i);

void sparkDeleteAllRendererObjectGroups(SparkRenderer* renderer);
void sparkDeleteRendererObjectGroup(SparkRenderer* renderer, SparkRendererObjectGroup* rendererObjectGroup);

void sparkRender(SparkRenderer* renderer);
void sparkLoadScene(SparkRenderer* renderer, SparkScene* scene);
void sparkDeleteRenderer(SparkRenderer* renderer);

#endif