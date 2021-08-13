#ifndef RENDERER_OBJECT_H_INCLUDED
#define RENDERER_OBJECT_H_INCLUDED

#define RENDERER_OBJECT_TYPE_UNKNOWN -1
#define RENDERER_OBJECT_TYPE_2D_COLOR 0
#define RENDERER_OBJECT_TYPE_2D_TEXTURE 1
#define RENDERER_OBJECT_TYPE_3D_COLOR 2
#define RENDERER_OBJECT_TYPE_3D_TEXTURE 3

#include "../../structs/texture.h"

struct SparkRendererObject {
    int type;

    GLfloat* vertices;
    GLuint* indices;
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    int drawType;

    SparkTexture* texture;
};
typedef struct SparkRendererObject SparkRendererObject;

void sparkBindRendererObject(SparkRendererObject* rendererObject);
void sparkUnbindRendererObject();
void sparkDeleteRendererObject(SparkRendererObject* rendererObject);

void sparkGenerateBuffersInRendererObject(SparkRendererObject* rendererObject);
void sparkBufferDataInRendererObject(SparkRendererObject* rendererObject);
void sparkLinkAttributesInRendererObject(SparkRendererObject* rendererObject, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

void sparkDrawRendererObject(SparkRendererObject* rendererObject);

#endif