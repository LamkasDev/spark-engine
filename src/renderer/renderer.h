#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#define RENDERER_CIRCLE_TRIANGLE_AMMOUNT 60
#define RENDERER_SHAPE_UNKNOWN -1
#define RENDERER_SHAPE_QUAD 0
#define RENDERER_SHAPE_CIRCLE 1
#define RENDERER_SHAPE_EMPTY_QUAD 2
#define RENDERER_SHAPE_EMPTY_CIRCLE 3

#include "../gameobjects/gameobject.h"

#include "utils/renderer_object.h"
#include "shaders/shader.h"
#include "../structs/texture.h"

struct SparkRenderer {
    GLFWwindow* window;
    SparkScene* scene;

    SparkRendererObject* rendererObjects;
    hashmap shaders;
    hashmap textures;
    hashmap materials;

    int ww;
    int wh;
};
typedef struct SparkRenderer SparkRenderer;
void sparkSetupWindow(SparkRenderer* renderer);
void sparkCompileShaders(SparkRenderer* renderer);
void sparkOnWindowResize(GLFWwindow* window, int w, int h);
void sparkCreateRendererObjects(SparkRenderer* renderer);
void sparkRender(SparkRenderer* renderer);
void sparkLoadScene(SparkRenderer* renderer, SparkScene* scene);

#endif