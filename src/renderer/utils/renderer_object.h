#ifndef RENDERER_OBJECT_H_INCLUDED
#define RENDERER_OBJECT_H_INCLUDED

#define RENDERER_OBJECT_TYPE_UNKNOWN -1
#define RENDERER_OBJECT_TYPE_COLOR 0
#define RENDERER_OBJECT_TYPE_TEXTURE 1

#include "../../utils/texture.h"

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