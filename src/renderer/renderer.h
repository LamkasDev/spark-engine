#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#define RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_0 15
#define RENDERER_BORDER_CIRCLE_TRIANGLE_AMMOUNT_1 60

#define RENDERER_SHAPE_UNKNOWN -1
#define RENDERER_SHAPE_QUAD 0
#define RENDERER_SHAPE_EMPTY_QUAD 1

#include "../gameobjects/gameobject.h"

#include "utils/renderer_object.h"
#include "shaders/shader.h"
#include "../structs/texture.h"

struct SparkRenderer {
    GLFWwindow* window;
    SparkScene* scene;
    FT_Library ft;

    SparkRendererObject* rendererObjects;
    hashmap shaders;
    hashmap textures;
    hashmap materials;
    hashmap fonts;

    int ww;
    int wh;
};
typedef struct SparkRenderer SparkRenderer;
void sparkSetupWindow(SparkRenderer* renderer);
SparkShader sparkCompileShader(SparkRenderer* renderer, char* name, char* vertexPath, char* fragmentPath);
void sparkOnWindowResize(GLFWwindow* window, int w, int h);

void sparkCreateRendererObjects(SparkRenderer* renderer);
void sparkCreateRendererObject(SparkRenderer* renderer, SparkGameObject* gameObject);

void sparkUpdateRendererObjects(SparkRenderer* renderer);
void sparkUpdateRendererObject(SparkRenderer* renderer, SparkRendererObject* rendererObject);

void sparkDeleteRendererObjects(SparkRenderer* renderer);
void sparkRender(SparkRenderer* renderer);
void sparkLoadScene(SparkRenderer* renderer, SparkScene* scene);

#endif