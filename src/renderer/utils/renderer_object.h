#ifndef RENDERER_OBJECT_H_INCLUDED
#define RENDERER_OBJECT_H_INCLUDED

#define RENDERER_OBJECT_TYPE_UNKNOWN -1
#define RENDERER_OBJECT_TYPE_2D_COLOR 0
#define RENDERER_OBJECT_TYPE_2D_TEXTURE 1
#define RENDERER_OBJECT_TYPE_3D_COLOR 2
#define RENDERER_OBJECT_TYPE_3D_TEXTURE 3

#include "../../structs/material.h"

struct SparkRendererObject {
    SparkGameObject* gameObject;
    SparkComponent* component;

    GLfloat* vertices;
    GLuint* indices;
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    int drawType;
};
typedef struct SparkRendererObject SparkRendererObject;

void sparkGenerateBuffersInRendererObject(SparkRendererObject* rendererObject);
void sparkLinkAttributesInRendererObject(SparkRendererObject* rendererObject, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

void sparkBindRendererObject(SparkRendererObject* rendererObject);
void sparkUnbindRendererObject(SparkRendererObject* rendererObject);
void sparkBufferDataInRendererObject(SparkRendererObject* rendererObject);

void sparkInitializeRendererObject(SparkRendererObject* rendererObject);
void sparkDrawRendererObject(SparkRendererObject* rendererObject);
void sparkDeleteRendererObject(SparkRendererObject* rendererObject);

#endif